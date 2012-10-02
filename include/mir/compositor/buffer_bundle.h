/*
 * Copyright © 2012 Canonical Ltd.
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
 * Authored by:
 * Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_COMPOSITOR_BUFFER_BUNDLE_H_
#define MIR_COMPOSITOR_BUFFER_BUNDLE_H_

#include "mir/geometry/size.h"
#include "mir/geometry/pixel_format.h"

#include <memory>

namespace mir
{
namespace compositor
{
class BufferSwapper;
class BufferIPCPackage;
class Buffer;
class GraphicRegion;

struct GraphicBufferClientResource
{
    GraphicBufferClientResource() {}
    GraphicBufferClientResource(
        std::shared_ptr<BufferIPCPackage> const& ipc_package,
        std::shared_ptr<Buffer> const& buffer) :
            ipc_package(ipc_package), buffer(buffer)
    {
    }

    std::shared_ptr<BufferIPCPackage> const ipc_package;
    std::shared_ptr<Buffer> const buffer;
};

class BufferBundle
{
public:
    virtual std::shared_ptr<GraphicBufferClientResource> secure_client_buffer() = 0;
    virtual std::shared_ptr<GraphicRegion> lock_and_bind_back_buffer() = 0;
    virtual geometry::PixelFormat get_bundle_pixel_format() = 0;
    virtual geometry::Size bundle_size() = 0;
};

}
}

#endif /* MIR_COMPOSITOR_BUFFER_BUNDLE_H_ */
