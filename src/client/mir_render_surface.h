/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
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
 *   Cemil Azizoglu <cemil.azizoglu@canonical.com>
 */

#ifndef MIR_CLIENT_MIR_RENDER_SURFACE_H
#define MIR_CLIENT_MIR_RENDER_SURFACE_H

#include "mir_toolkit/mir_render_surface.h"

namespace mir
{
namespace client
{
class ClientBufferStream;
}
}

class MirRenderSurface
{
public:
    virtual ~MirRenderSurface() = default;
    virtual MirConnection* connection() const = 0;
    virtual MirWaitHandle* create_client_buffer_stream(
        MirBufferUsage buffer_usage,
        bool autorelease,
        mir_buffer_stream_callback callback,
        void* context) = 0;
    virtual int stream_id() = 0;
    virtual bool autorelease_content() const = 0;

    virtual MirWaitHandle* release_buffer_stream(
        void* native_surface,
        mir_render_surface_callback callback,
        void* context) = 0;
protected:
    MirRenderSurface(MirRenderSurface const&) = delete;
    MirRenderSurface& operator=(MirRenderSurface const&) = delete;
    MirRenderSurface() = default;
};

#endif /* MIR_CLIENT_MIR_RENDER_SURFACE_H */
