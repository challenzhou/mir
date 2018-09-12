/*
 * AUTOGENERATED - DO NOT EDIT
 *
 * This file is generated from xdg-shell.xml
 * To regenerate, run the “refresh-wayland-wrapper” target.
 */

#include "xdg-shell_wrapper.h"

#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <wayland-server-core.h>

#include "mir/log.h"

namespace mir
{
namespace frontend
{
namespace wayland
{
extern struct wl_interface const wl_output_interface_data;
extern struct wl_interface const wl_seat_interface_data;
extern struct wl_interface const wl_surface_interface_data;
extern struct wl_interface const xdg_popup_interface_data;
extern struct wl_interface const xdg_positioner_interface_data;
extern struct wl_interface const xdg_surface_interface_data;
extern struct wl_interface const xdg_toplevel_interface_data;
extern struct wl_interface const xdg_wm_base_interface_data;
}
}
}

namespace mfw = mir::frontend::wayland;

namespace
{
struct wl_interface const* all_null_types [] {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr};
}

// XdgWmBase

mfw::XdgWmBase* mfw::XdgWmBase::from(struct wl_resource* resource)
{
    return static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
}

struct mfw::XdgWmBase::Thunks
{
    static void destroy_thunk(struct wl_client* client, struct wl_resource* resource)
    {
        auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy(client, resource);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::destroy() request");
        }
    }

    static void create_positioner_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id)
    {
        auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
        try
        {
            me->create_positioner(client, resource, id);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::create_positioner() request");
        }
    }

    static void get_xdg_surface_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* surface)
    {
        auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
        try
        {
            me->get_xdg_surface(client, resource, id, surface);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::get_xdg_surface() request");
        }
    }

    static void pong_thunk(struct wl_client* client, struct wl_resource* resource, uint32_t serial)
    {
        auto me = static_cast<XdgWmBase*>(wl_resource_get_user_data(resource));
        try
        {
            me->pong(client, resource, serial);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::pong() request");
        }
    }

    static void bind_thunk(struct wl_client* client, void* data, uint32_t version, uint32_t id)
    {
        auto me = static_cast<XdgWmBase*>(data);
        auto resource = wl_resource_create(client, &xdg_wm_base_interface_data,
                                           std::min(version, me->max_version), id);
        if (resource == nullptr)
        {
            wl_client_post_no_memory(client);
            BOOST_THROW_EXCEPTION((std::bad_alloc{}));
        }
        wl_resource_set_implementation(resource, Thunks::request_vtable, me, nullptr);
        try
        {
            me->bind(client, resource);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgWmBase::bind() request");
        }
    }

    static struct wl_interface const* create_positioner_types[];
    static struct wl_interface const* get_xdg_surface_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mfw::XdgWmBase::XdgWmBase(struct wl_display* display, uint32_t max_version)
    : global{wl_global_create(display, &xdg_wm_base_interface_data, max_version, this, &Thunks::bind_thunk)},
      max_version{max_version}
{
    if (global == nullptr)
    {
        BOOST_THROW_EXCEPTION((std::runtime_error{"Failed to export xdg_wm_base interface"}));
    }
}

mfw::XdgWmBase::~XdgWmBase()
{
    wl_global_destroy(global);
}

void mfw::XdgWmBase::send_ping_event(struct wl_resource* resource, uint32_t serial) const
{
    wl_resource_post_event(resource, Opcode::ping, serial);
}

void mfw::XdgWmBase::destroy_wayland_object(struct wl_resource* resource) const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mfw::XdgWmBase::Thunks::create_positioner_types[] {
    &xdg_positioner_interface_data};

struct wl_interface const* mfw::XdgWmBase::Thunks::get_xdg_surface_types[] {
    &xdg_surface_interface_data,
    &wl_surface_interface_data};

struct wl_message const mfw::XdgWmBase::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"create_positioner", "n", create_positioner_types},
    {"get_xdg_surface", "no", get_xdg_surface_types},
    {"pong", "u", all_null_types}};

struct wl_message const mfw::XdgWmBase::Thunks::event_messages[] {
    {"ping", "u", all_null_types}};

void const* mfw::XdgWmBase::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::create_positioner_thunk,
    (void*)Thunks::get_xdg_surface_thunk,
    (void*)Thunks::pong_thunk};

// XdgPositioner

mfw::XdgPositioner* mfw::XdgPositioner::from(struct wl_resource* resource)
{
    return static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
}

struct mfw::XdgPositioner::Thunks
{
    static void destroy_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::destroy() request");
        }
    }

    static void set_size_thunk(struct wl_client*, struct wl_resource* resource, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_size(width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_size() request");
        }
    }

    static void set_anchor_rect_thunk(struct wl_client*, struct wl_resource* resource, int32_t x, int32_t y, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_anchor_rect(x, y, width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_anchor_rect() request");
        }
    }

    static void set_anchor_thunk(struct wl_client*, struct wl_resource* resource, uint32_t anchor)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_anchor(anchor);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_anchor() request");
        }
    }

    static void set_gravity_thunk(struct wl_client*, struct wl_resource* resource, uint32_t gravity)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_gravity(gravity);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_gravity() request");
        }
    }

    static void set_constraint_adjustment_thunk(struct wl_client*, struct wl_resource* resource, uint32_t constraint_adjustment)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_constraint_adjustment(constraint_adjustment);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_constraint_adjustment() request");
        }
    }

    static void set_offset_thunk(struct wl_client*, struct wl_resource* resource, int32_t x, int32_t y)
    {
        auto me = static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_offset(x, y);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPositioner::set_offset() request");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgPositioner*>(wl_resource_get_user_data(resource));
    }

    static struct wl_message const request_messages[];
    static void const* request_vtable[];
};

mfw::XdgPositioner::XdgPositioner(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &xdg_positioner_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

void mfw::XdgPositioner::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_message const mfw::XdgPositioner::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"set_size", "ii", all_null_types},
    {"set_anchor_rect", "iiii", all_null_types},
    {"set_anchor", "u", all_null_types},
    {"set_gravity", "u", all_null_types},
    {"set_constraint_adjustment", "u", all_null_types},
    {"set_offset", "ii", all_null_types}};

void const* mfw::XdgPositioner::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::set_size_thunk,
    (void*)Thunks::set_anchor_rect_thunk,
    (void*)Thunks::set_anchor_thunk,
    (void*)Thunks::set_gravity_thunk,
    (void*)Thunks::set_constraint_adjustment_thunk,
    (void*)Thunks::set_offset_thunk};

// XdgSurface

mfw::XdgSurface* mfw::XdgSurface::from(struct wl_resource* resource)
{
    return static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
}

struct mfw::XdgSurface::Thunks
{
    static void destroy_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::destroy() request");
        }
    }

    static void get_toplevel_thunk(struct wl_client*, struct wl_resource* resource, uint32_t id)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        try
        {
            me->get_toplevel(id);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::get_toplevel() request");
        }
    }

    static void get_popup_thunk(struct wl_client*, struct wl_resource* resource, uint32_t id, struct wl_resource* parent, struct wl_resource* positioner)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        std::experimental::optional<struct wl_resource*> parent_resolved;
        if (parent != nullptr)
        {
            parent_resolved = {parent};
        }
        try
        {
            me->get_popup(id, parent_resolved, positioner);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::get_popup() request");
        }
    }

    static void set_window_geometry_thunk(struct wl_client*, struct wl_resource* resource, int32_t x, int32_t y, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_window_geometry(x, y, width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::set_window_geometry() request");
        }
    }

    static void ack_configure_thunk(struct wl_client*, struct wl_resource* resource, uint32_t serial)
    {
        auto me = static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
        try
        {
            me->ack_configure(serial);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgSurface::ack_configure() request");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgSurface*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* get_toplevel_types[];
    static struct wl_interface const* get_popup_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mfw::XdgSurface::XdgSurface(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &xdg_surface_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

void mfw::XdgSurface::send_configure_event(uint32_t serial) const
{
    wl_resource_post_event(resource, Opcode::configure, serial);
}

void mfw::XdgSurface::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mfw::XdgSurface::Thunks::get_toplevel_types[] {
    &xdg_toplevel_interface_data};

struct wl_interface const* mfw::XdgSurface::Thunks::get_popup_types[] {
    &xdg_popup_interface_data,
    &xdg_surface_interface_data,
    &xdg_positioner_interface_data};

struct wl_message const mfw::XdgSurface::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"get_toplevel", "n", get_toplevel_types},
    {"get_popup", "n?oo", get_popup_types},
    {"set_window_geometry", "iiii", all_null_types},
    {"ack_configure", "u", all_null_types}};

struct wl_message const mfw::XdgSurface::Thunks::event_messages[] {
    {"configure", "u", all_null_types}};

void const* mfw::XdgSurface::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::get_toplevel_thunk,
    (void*)Thunks::get_popup_thunk,
    (void*)Thunks::set_window_geometry_thunk,
    (void*)Thunks::ack_configure_thunk};

// XdgToplevel

mfw::XdgToplevel* mfw::XdgToplevel::from(struct wl_resource* resource)
{
    return static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
}

struct mfw::XdgToplevel::Thunks
{
    static void destroy_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::destroy() request");
        }
    }

    static void set_parent_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* parent)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        std::experimental::optional<struct wl_resource*> parent_resolved;
        if (parent != nullptr)
        {
            parent_resolved = {parent};
        }
        try
        {
            me->set_parent(parent_resolved);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_parent() request");
        }
    }

    static void set_title_thunk(struct wl_client*, struct wl_resource* resource, char const* title)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_title(title);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_title() request");
        }
    }

    static void set_app_id_thunk(struct wl_client*, struct wl_resource* resource, char const* app_id)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_app_id(app_id);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_app_id() request");
        }
    }

    static void show_window_menu_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial, int32_t x, int32_t y)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->show_window_menu(seat, serial, x, y);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::show_window_menu() request");
        }
    }

    static void move_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->move(seat, serial);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::move() request");
        }
    }

    static void resize_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial, uint32_t edges)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->resize(seat, serial, edges);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::resize() request");
        }
    }

    static void set_max_size_thunk(struct wl_client*, struct wl_resource* resource, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_max_size(width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_max_size() request");
        }
    }

    static void set_min_size_thunk(struct wl_client*, struct wl_resource* resource, int32_t width, int32_t height)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_min_size(width, height);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_min_size() request");
        }
    }

    static void set_maximized_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_maximized();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_maximized() request");
        }
    }

    static void unset_maximized_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->unset_maximized();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::unset_maximized() request");
        }
    }

    static void set_fullscreen_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* output)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        std::experimental::optional<struct wl_resource*> output_resolved;
        if (output != nullptr)
        {
            output_resolved = {output};
        }
        try
        {
            me->set_fullscreen(output_resolved);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_fullscreen() request");
        }
    }

    static void unset_fullscreen_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->unset_fullscreen();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::unset_fullscreen() request");
        }
    }

    static void set_minimized_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
        try
        {
            me->set_minimized();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgToplevel::set_minimized() request");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgToplevel*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* set_parent_types[];
    static struct wl_interface const* show_window_menu_types[];
    static struct wl_interface const* move_types[];
    static struct wl_interface const* resize_types[];
    static struct wl_interface const* set_fullscreen_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mfw::XdgToplevel::XdgToplevel(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &xdg_toplevel_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

void mfw::XdgToplevel::send_configure_event(int32_t width, int32_t height, struct wl_array* states) const
{
    wl_resource_post_event(resource, Opcode::configure, width, height, states);
}

void mfw::XdgToplevel::send_close_event() const
{
    wl_resource_post_event(resource, Opcode::close);
}

void mfw::XdgToplevel::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mfw::XdgToplevel::Thunks::set_parent_types[] {
    &xdg_toplevel_interface_data};

struct wl_interface const* mfw::XdgToplevel::Thunks::show_window_menu_types[] {
    &wl_seat_interface_data,
    nullptr,
    nullptr,
    nullptr};

struct wl_interface const* mfw::XdgToplevel::Thunks::move_types[] {
    &wl_seat_interface_data,
    nullptr};

struct wl_interface const* mfw::XdgToplevel::Thunks::resize_types[] {
    &wl_seat_interface_data,
    nullptr,
    nullptr};

struct wl_interface const* mfw::XdgToplevel::Thunks::set_fullscreen_types[] {
    &wl_output_interface_data};

struct wl_message const mfw::XdgToplevel::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"set_parent", "?o", set_parent_types},
    {"set_title", "s", all_null_types},
    {"set_app_id", "s", all_null_types},
    {"show_window_menu", "ouii", show_window_menu_types},
    {"move", "ou", move_types},
    {"resize", "ouu", resize_types},
    {"set_max_size", "ii", all_null_types},
    {"set_min_size", "ii", all_null_types},
    {"set_maximized", "", all_null_types},
    {"unset_maximized", "", all_null_types},
    {"set_fullscreen", "?o", set_fullscreen_types},
    {"unset_fullscreen", "", all_null_types},
    {"set_minimized", "", all_null_types}};

struct wl_message const mfw::XdgToplevel::Thunks::event_messages[] {
    {"configure", "iia", all_null_types},
    {"close", "", all_null_types}};

void const* mfw::XdgToplevel::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::set_parent_thunk,
    (void*)Thunks::set_title_thunk,
    (void*)Thunks::set_app_id_thunk,
    (void*)Thunks::show_window_menu_thunk,
    (void*)Thunks::move_thunk,
    (void*)Thunks::resize_thunk,
    (void*)Thunks::set_max_size_thunk,
    (void*)Thunks::set_min_size_thunk,
    (void*)Thunks::set_maximized_thunk,
    (void*)Thunks::unset_maximized_thunk,
    (void*)Thunks::set_fullscreen_thunk,
    (void*)Thunks::unset_fullscreen_thunk,
    (void*)Thunks::set_minimized_thunk};

// XdgPopup

mfw::XdgPopup* mfw::XdgPopup::from(struct wl_resource* resource)
{
    return static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
}

struct mfw::XdgPopup::Thunks
{
    static void destroy_thunk(struct wl_client*, struct wl_resource* resource)
    {
        auto me = static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
        try
        {
            me->destroy();
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPopup::destroy() request");
        }
    }

    static void grab_thunk(struct wl_client*, struct wl_resource* resource, struct wl_resource* seat, uint32_t serial)
    {
        auto me = static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
        try
        {
            me->grab(seat, serial);
        }
        catch(...)
        {
            ::mir::log(::mir::logging::Severity::critical,
                       "frontend:Wayland",
                       std::current_exception(),
                       "Exception processing XdgPopup::grab() request");
        }
    }

    static void resource_destroyed_thunk(wl_resource* resource)
    {
        delete static_cast<XdgPopup*>(wl_resource_get_user_data(resource));
    }

    static struct wl_interface const* grab_types[];
    static struct wl_message const request_messages[];
    static struct wl_message const event_messages[];
    static void const* request_vtable[];
};

mfw::XdgPopup::XdgPopup(struct wl_client* client, struct wl_resource* parent, uint32_t id)
    : client{client},
      resource{wl_resource_create(client, &xdg_popup_interface_data, wl_resource_get_version(parent), id)}
{
    if (resource == nullptr)
    {
        wl_resource_post_no_memory(parent);
        BOOST_THROW_EXCEPTION((std::bad_alloc{}));
    }
    wl_resource_set_implementation(resource, Thunks::request_vtable, this, &Thunks::resource_destroyed_thunk);
}

void mfw::XdgPopup::send_configure_event(int32_t x, int32_t y, int32_t width, int32_t height) const
{
    wl_resource_post_event(resource, Opcode::configure, x, y, width, height);
}

void mfw::XdgPopup::send_popup_done_event() const
{
    wl_resource_post_event(resource, Opcode::popup_done);
}

void mfw::XdgPopup::destroy_wayland_object() const
{
    wl_resource_destroy(resource);
}

struct wl_interface const* mfw::XdgPopup::Thunks::grab_types[] {
    &wl_seat_interface_data,
    nullptr};

struct wl_message const mfw::XdgPopup::Thunks::request_messages[] {
    {"destroy", "", all_null_types},
    {"grab", "ou", grab_types}};

struct wl_message const mfw::XdgPopup::Thunks::event_messages[] {
    {"configure", "iiii", all_null_types},
    {"popup_done", "", all_null_types}};

void const* mfw::XdgPopup::Thunks::request_vtable[] {
    (void*)Thunks::destroy_thunk,
    (void*)Thunks::grab_thunk};

namespace mir
{
namespace frontend
{
namespace wayland
{

struct wl_interface const xdg_wm_base_interface_data {
    "xdg_wm_base", 1,
    4, mfw::XdgWmBase::Thunks::request_messages,
    1, mfw::XdgWmBase::Thunks::event_messages};

struct wl_interface const xdg_positioner_interface_data {
    "xdg_positioner", 1,
    7, mfw::XdgPositioner::Thunks::request_messages,
    0, nullptr};

struct wl_interface const xdg_surface_interface_data {
    "xdg_surface", 1,
    5, mfw::XdgSurface::Thunks::request_messages,
    1, mfw::XdgSurface::Thunks::event_messages};

struct wl_interface const xdg_toplevel_interface_data {
    "xdg_toplevel", 1,
    14, mfw::XdgToplevel::Thunks::request_messages,
    2, mfw::XdgToplevel::Thunks::event_messages};

struct wl_interface const xdg_popup_interface_data {
    "xdg_popup", 1,
    2, mfw::XdgPopup::Thunks::request_messages,
    2, mfw::XdgPopup::Thunks::event_messages};

}
}
}