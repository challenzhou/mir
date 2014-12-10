/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by:
 * Eleni Maria Stea <elenimaria.stea@canonical.com>
 * Alan Griffiths <alan@octopull.co.uk>
 */

#include "native_platform.h"

#include "buffer_allocator.h"
#include "mir/graphics/buffer_ipc_message.h"
#include "mir/graphics/platform_ipc_package.h"
#include "mir/graphics/nested_context.h"

#include "nested_authentication.h"

#include "ipc_operations.h"

#include <boost/exception/errinfo_errno.hpp>
#include <boost/throw_exception.hpp>

#include <mutex>
#include <stdexcept>

namespace mg = mir::graphics;
namespace mgm = mg::mesa;

mgm::NativePlatform::NativePlatform(std::shared_ptr<NestedContext> const& nested_context_arg)
{
    //TODO: a bit of round-about initialization to clean up here
    nested_context = nested_context_arg;
    auto fds = nested_context->platform_fd_items();
    gbm.setup(fds.at(0));
    nested_context->drm_set_gbm_device(gbm.device);
    ipc_ops = std::make_shared<mgm::IpcOperations>(
        std::make_shared<mgm::NestedAuthentication>(nested_context)); 
}

std::shared_ptr<mg::GraphicBufferAllocator> mgm::NativePlatform::create_buffer_allocator()
{
    return std::make_shared<mgm::BufferAllocator>(gbm.device, mgm::BypassOption::prohibited);
}

extern "C" std::shared_ptr<mg::NativePlatform> create_native_platform(
    std::shared_ptr<mg::DisplayReport> const&,
    std::shared_ptr<mg::NestedContext> const& nested_context)
{
    return std::make_shared<mgm::NativePlatform>(nested_context);
}

namespace
{
std::shared_ptr<mgm::InternalNativeDisplay> native_display = nullptr;
std::mutex native_display_guard;
}

std::shared_ptr<mg::PlatformIpcOperations> mgm::NativePlatform::make_ipc_operations() const
{
    return ipc_ops;
}
