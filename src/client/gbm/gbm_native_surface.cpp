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
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#include <cstring>
#include "../client_buffer.h"
#include "gbm_native_surface.h"

namespace mclg=mir::client::gbm;

namespace
{
static void advance_buffer_static(MirMesaEGLNativeSurface* surface,
                                  MirBufferPackage* buffer_package)
{
    auto s = static_cast<mclg::GBMNativeSurface*>(surface);
    s->advance_buffer(buffer_package);
}

static void get_parameters_static(MirMesaEGLNativeSurface* surface,
                                  MirSurfaceParameters* surface_parameters)
{
    auto s = static_cast<mclg::GBMNativeSurface*>(surface);
    s->get_parameters(surface_parameters);
}

static void buffer_advanced_callback(MirSurface*  /* surface */,
                                     void*  /* context */)
{
}
}

mclg::GBMNativeSurface::GBMNativeSurface(ClientSurface& surface)
    : surface(surface)
{
    surface_advance_buffer = advance_buffer_static; 
    surface_get_parameters = get_parameters_static; 
}

void mclg::GBMNativeSurface::advance_buffer(MirBufferPackage* buffer_package)
{
    mir_wait_for(surface.next_buffer(buffer_advanced_callback, NULL));
    auto buffer = surface.get_current_buffer();

    auto buffer_to_driver = buffer->native_buffer_handle();
    memcpy(buffer_package, buffer_to_driver.get(), sizeof(MirBufferPackage));
}

void mclg::GBMNativeSurface::get_parameters(MirSurfaceParameters* surface_parameters)
{
    auto params = surface.get_parameters();
    memcpy(surface_parameters, &params, sizeof(MirSurfaceParameters));
}
