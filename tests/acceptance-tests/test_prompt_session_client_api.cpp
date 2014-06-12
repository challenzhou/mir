/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Nick Dedekind <nick.dedekind@canonical.com>
 */

#include "mir_toolkit/mir_prompt_session.h"
#include "mir/scene/prompt_session_listener.h"
#include "mir/scene/prompt_session.h"
#include "mir/scene/prompt_session_manager.h"
#include "mir/scene/session.h"
#include "mir/frontend/shell.h"

#include "mir_test_framework/stubbed_server_configuration.h"
#include "mir_test_framework/basic_client_server_fixture.h"
#include "mir_test/popen.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <condition_variable>
#include <mutex>

namespace mtf = mir_test_framework;
namespace ms = mir::scene;
namespace mf = mir::frontend;

using namespace testing;

namespace
{
struct MockPromptSessionListener : ms::PromptSessionListener
{
    MockPromptSessionListener(std::shared_ptr<ms::PromptSessionListener> const& wrapped) :
        wrapped(wrapped)
    {
        ON_CALL(*this, starting(_)).WillByDefault(Invoke(wrapped.get(), &ms::PromptSessionListener::starting));
        ON_CALL(*this, stopping(_)).WillByDefault(Invoke(wrapped.get(), &ms::PromptSessionListener::stopping));
        ON_CALL(*this, prompt_provider_added(_, _)).WillByDefault(Invoke(wrapped.get(), &ms::PromptSessionListener::prompt_provider_added));
        ON_CALL(*this, prompt_provider_removed(_, _)).WillByDefault(Invoke(wrapped.get(), &ms::PromptSessionListener::prompt_provider_removed));
    }

    MOCK_METHOD1(starting, void(std::shared_ptr<ms::PromptSession> const& prompt_session));
    MOCK_METHOD1(stopping, void(std::shared_ptr<ms::PromptSession> const& prompt_session));

    MOCK_METHOD2(prompt_provider_added, void(ms::PromptSession const& prompt_session, std::shared_ptr<ms::Session> const& prompt_provider));
    MOCK_METHOD2(prompt_provider_removed, void(ms::PromptSession const& prompt_session, std::shared_ptr<ms::Session> const& prompt_provider));

    std::shared_ptr<ms::PromptSessionListener> const wrapped;
};

struct PromptSessionListenerConfiguration : mtf::StubbedServerConfiguration
{
    std::shared_ptr<ms::PromptSessionListener> the_prompt_session_listener()
    {
        return prompt_session_listener([this]()
           ->std::shared_ptr<ms::PromptSessionListener>
           {
               return the_mock_prompt_session_listener();
           });
    }

    std::shared_ptr<MockPromptSessionListener> the_mock_prompt_session_listener()
    {
        return mock_prompt_session_listener([this]
            {
                return std::make_shared<NiceMock<MockPromptSessionListener>>(
                    mtf::StubbedServerConfiguration::the_prompt_session_listener());
            });
    }

    mir::CachedPtr<MockPromptSessionListener> mock_prompt_session_listener;
};

struct PromptSessionClientAPI : mtf::BasicClientServerFixture<PromptSessionListenerConfiguration>
{
    static constexpr int arbitrary_base_session_id = __LINE__;
    static constexpr mir_prompt_session_event_callback null_event_callback = nullptr;

    MockPromptSessionListener* the_mock_prompt_session_listener()
    {
        return server_configuration.the_mock_prompt_session_listener().get();
    }

    MOCK_METHOD2(prompt_session_event, void(MirPromptSession* prompt_provider, MirPromptSessionState state));

    static std::size_t const arbritary_fd_request_count = 3;
    std::mutex mutex;
    std::size_t actual_fd_count = 0;
    int actual_fds[arbritary_fd_request_count] = {};
    std::condition_variable cv;
    bool called_back = false;

    bool wait_for_callback(std::chrono::milliseconds timeout)
    {
        std::unique_lock<decltype(mutex)> lock(mutex);
        return cv.wait_for(lock, timeout, [this]{ return called_back; });
    }

    char const* fd_connect_string(int fd)
    {
        static char client_connect_string[32] = {0};

        sprintf(client_connect_string, "fd://%d", fd);
        return client_connect_string;
    }

    MOCK_METHOD1(process_line, void(std::string const&));
};

extern "C" void prompt_session_event_callback(MirPromptSession* prompt_provider, MirPromptSessionState state, void* context)
{
    PromptSessionClientAPI* self = static_cast<PromptSessionClientAPI*>(context);
    self->prompt_session_event(prompt_provider, state);
}

void client_fd_callback(MirPromptSession*, size_t count, int const* fds, void* context)
{
    auto const self = static_cast<PromptSessionClientAPI*>(context);

    std::unique_lock<decltype(self->mutex)> lock(self->mutex);
    self->actual_fd_count = count;

    std::copy(fds, fds+count, self->actual_fds);
    self->called_back = true;
    self->cv.notify_one();
}

MATCHER_P(SessionWithPid, pid, "")
{
    return arg->process_id() == pid;
}
}

TEST_F(PromptSessionClientAPI, can_start_and_stop_a_prompt_session)
{
    {
        InSequence server_seq;
        EXPECT_CALL(*the_mock_prompt_session_listener(), starting(_));
        EXPECT_CALL(*the_mock_prompt_session_listener(), stopping(_));
    }

    MirPromptSession* prompt_session = mir_connection_start_prompt_session_sync(
        connection, arbitrary_base_session_id, null_event_callback, this);
    ASSERT_THAT(prompt_session, Ne(nullptr));
    EXPECT_THAT(mir_prompt_session_get_state(prompt_session), Eq(mir_prompt_session_state_started));

    mir_prompt_session_release_sync(prompt_session);
}

TEST_F(PromptSessionClientAPI, notifies_start_and_stop)
{
    InSequence seq;
    EXPECT_CALL(*this, prompt_session_event(_, mir_prompt_session_state_started));
    EXPECT_CALL(*this, prompt_session_event(_, mir_prompt_session_state_stopped));

    MirPromptSession* prompt_session = mir_connection_start_prompt_session_sync(
        connection, arbitrary_base_session_id, prompt_session_event_callback, this);

    mir_prompt_session_release_sync(prompt_session);
}

TEST_F(PromptSessionClientAPI, can_add_prompt_provider)
{
    pid_t prompt_provider_pid = __LINE__;
    auto const prompt_provider_session = server_config().the_frontend_shell()->open_session(prompt_provider_pid, __PRETTY_FUNCTION__,  std::shared_ptr<mf::EventSink>());

    {
        auto const prompt_provider = std::dynamic_pointer_cast<ms::Session>(prompt_provider_session);
        InSequence server_seq;
        EXPECT_CALL(*the_mock_prompt_session_listener(), prompt_provider_added(_, Eq(prompt_provider)));
        EXPECT_CALL(*the_mock_prompt_session_listener(), prompt_provider_removed(_, Eq(prompt_provider)));
    }

    MirPromptSession* prompt_session = mir_connection_start_prompt_session_sync(
        connection, arbitrary_base_session_id, null_event_callback, this);

    EXPECT_TRUE(mir_prompt_session_add_prompt_provider_sync(prompt_session, prompt_provider_pid));

    mir_prompt_session_release_sync(prompt_session);

    // TODO It really shouldn't be necessary to close the prompt provider session.
    // TODO But the MediatingDisplayChanger id destroyed without deregistering
    // TODO callbacks from the BroadcastingSessionEventSink which gets called in
    // TODO SessionManager::~SessionManager() in code that the comments claim
    // TODO works around broken ownership.
    server_config().the_frontend_shell()->close_session(prompt_provider_session);
}

TEST_F(PromptSessionClientAPI, can_get_fds_for_prompt_providers)
{
    MirPromptSession* prompt_session = mir_connection_start_prompt_session_sync(
        connection, arbitrary_base_session_id, null_event_callback, this);

    mir_prompt_session_new_fds_for_prompt_providers(prompt_session, arbritary_fd_request_count, &client_fd_callback, this);
    EXPECT_TRUE(wait_for_callback(std::chrono::milliseconds(500)));

    EXPECT_THAT(actual_fd_count, Eq(arbritary_fd_request_count));

    mir_prompt_session_release_sync(prompt_session);
}

TEST_F(PromptSessionClientAPI, when_prompt_provider_connects_over_fd_prompt_provider_added_with_right_pid)
{
    MirPromptSession* prompt_session = mir_connection_start_prompt_session_sync(
        connection, arbitrary_base_session_id, null_event_callback, this);

    mir_prompt_session_new_fds_for_prompt_providers(prompt_session, 1, &client_fd_callback, this);
    ASSERT_TRUE(wait_for_callback(std::chrono::milliseconds(500)));

    auto const expected_pid = getpid();

    EXPECT_CALL(*the_mock_prompt_session_listener(), prompt_provider_added(_, SessionWithPid(expected_pid)));

    auto client_connection = mir_connect_sync(fd_connect_string(actual_fds[0]), __PRETTY_FUNCTION__);

    mir_connection_release(client_connection);
    mir_prompt_session_release_sync(prompt_session);
}

// TODO we need a nice way to run this (and similar tests that require a separate client process) in CI
// Disabled as we can't be sure the mir_demo_client_basic is about
TEST_F(PromptSessionClientAPI, DISABLED_client_pid_is_associated_with_session)
{
    auto const server_pid = getpid();

    MirPromptSession* prompt_session = mir_connection_start_prompt_session_sync(
        connection, arbitrary_base_session_id, null_event_callback, this);

    mir_prompt_session_new_fds_for_prompt_providers(prompt_session, 1, &client_fd_callback, this);
    wait_for_callback(std::chrono::milliseconds(500));

    EXPECT_CALL(*the_mock_prompt_session_listener(), prompt_provider_added(_, Not(SessionWithPid(server_pid))));

    InSequence seq;
    EXPECT_CALL(*this, process_line(StrEq("Starting")));
    EXPECT_CALL(*this, process_line(StrEq("Connected")));
    EXPECT_CALL(*this, process_line(StrEq("Surface created")));
    EXPECT_CALL(*this, process_line(StrEq("Surface released")));
    EXPECT_CALL(*this, process_line(StrEq("Connection released")));

    mir::test::Popen output(std::string("bin/mir_demo_client_basic -m ") + fd_connect_string(actual_fds[0]));

    std::string line;
    while (output.get_line(line)) process_line(line);

    mir_prompt_session_release_sync(prompt_session);
}

TEST_F(PromptSessionClientAPI, notifies_when_server_closes_prompt_session)
{
    std::shared_ptr<ms::PromptSession> server_prompt_session;

    EXPECT_CALL(*the_mock_prompt_session_listener(), starting(_)).
        WillOnce(DoAll(
            Invoke(the_mock_prompt_session_listener()->wrapped.get(), &ms::PromptSessionListener::starting),
            SaveArg<0>(&server_prompt_session)));
    EXPECT_CALL(*this, prompt_session_event(_, mir_prompt_session_state_started));

    MirPromptSession* prompt_session = mir_connection_start_prompt_session_sync(
        connection, arbitrary_base_session_id, prompt_session_event_callback, this);

    EXPECT_CALL(*this, prompt_session_event(_, mir_prompt_session_state_stopped));

    server_configuration.the_prompt_session_manager()->stop_prompt_session(server_prompt_session);

    // Verify we have got the "stopped" notification before we go on and release the session
    Mock::VerifyAndClearExpectations(the_mock_prompt_session_listener());

    mir_prompt_session_release_sync(prompt_session);
}

TEST_F(PromptSessionClientAPI, after_server_closes_prompt_session_api_isnt_broken)
{
    std::shared_ptr<ms::PromptSession> server_prompt_session;

    EXPECT_CALL(*the_mock_prompt_session_listener(), starting(_)).
        WillOnce(DoAll(
            Invoke(the_mock_prompt_session_listener()->wrapped.get(), &ms::PromptSessionListener::starting),
            SaveArg<0>(&server_prompt_session)));

    MirPromptSession* prompt_session = mir_connection_start_prompt_session_sync(
        connection, arbitrary_base_session_id, null_event_callback, this);

    server_configuration.the_prompt_session_manager()->stop_prompt_session(server_prompt_session);

    pid_t prompt_provider_pid = __LINE__;
    EXPECT_FALSE(mir_prompt_session_add_prompt_provider_sync(prompt_session, prompt_provider_pid));
    EXPECT_THAT(mir_prompt_session_get_state(prompt_session), Eq(mir_prompt_session_state_stopped));

    mir_prompt_session_release_sync(prompt_session);
}
