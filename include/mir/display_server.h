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
 *   Alan Griffiths <alan@octopull.co.uk>
 *   Thomas Voss <thomas.voss@canonical.com>
 */

#ifndef MIR_DISPLAY_SERVER_H_
#define MIR_DISPLAY_SERVER_H_

#include <memory>

namespace mir
{
namespace compositor
{

class BufferAllocationStrategy;
class BufferBundleFactory;

}
namespace graphics
{

class Display;
class Renderer;

}

class DisplayServer
{
public:
    // TODO: Come up with a better way to resolve dependency on
    // the BufferAllocationStrategy.
    DisplayServer(
        const std::shared_ptr<compositor::BufferAllocationStrategy>& strategy,
        const std::shared_ptr<graphics::Renderer>& renderer);

    ~DisplayServer();

    void render(graphics::Display* display);
private:
    struct Private;
    std::unique_ptr<Private> p;

    DisplayServer() = delete;
    DisplayServer(const DisplayServer&) = delete;
    DisplayServer& operator=(const DisplayServer&) = delete;
    
};

}

#endif /* MIR_DISPLAY_SERVER_H_ */
