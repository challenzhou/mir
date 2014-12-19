/*
 * Copyright © 2013 Canonical Ltd.
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
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#include "mir/graphics/android/sync_fence.h"
#include "src/platforms/android/hwc_fb_device.h"
#include "src/platforms/android/hwc_device.h"
#include "src/platforms/android/hwc_wrapper.h"
#include "src/platforms/android/hwc_layerlist.h"
#include "src/platforms/android/hwc_configuration.h"
#include "mir_test_doubles/mock_hwc_composer_device_1.h"
#include "mir_test_doubles/mock_hwc_device_wrapper.h"
#include "mir_test_doubles/mock_buffer.h"
#include "mir_test_doubles/mock_egl.h"
#include "mir_test_doubles/mock_display_device.h"
#include "mir_test_doubles/mock_fb_hal_device.h"

#include <thread>
#include <chrono>
#include <stdexcept>
#include <memory>
#include <gtest/gtest.h>

namespace mga=mir::graphics::android;
namespace mtd=mir::test::doubles;
namespace geom=mir::geometry;

namespace
{
struct MockDisplayConfiguration : mga::HwcConfiguration
{
    MOCK_METHOD2(power_mode, void(mga::DisplayName, MirPowerMode));
    MOCK_METHOD1(active_attribs_for, mga::DisplayAttribs(mga::DisplayName));
};
}

template<typename T>
class HWCCommon : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        mock_fbdev = std::make_shared<mtd::MockFBHalDevice>();
        mock_device = std::make_shared<testing::NiceMock<mtd::MockHWCDeviceWrapper>>();
        mock_config = std::make_shared<testing::NiceMock<MockDisplayConfiguration>>();
    }

    std::shared_ptr<mga::DisplayDevice> make_display_device();

    testing::NiceMock<mtd::MockEGL> mock_egl;
    std::shared_ptr<mtd::MockHWCDeviceWrapper> mock_device;
    std::shared_ptr<mtd::MockFBHalDevice> mock_fbdev;
    std::shared_ptr<MockDisplayConfiguration> mock_config;
};

template <>
std::shared_ptr<mga::DisplayDevice> HWCCommon<mga::HwcFbDevice>::make_display_device()
{
    return std::make_shared<mga::HwcFbDevice>(mock_device, mock_fbdev, mock_config);
}

template <>
std::shared_ptr<mga::DisplayDevice> HWCCommon<mga::HwcDevice>::make_display_device()
{
    return std::make_shared<mga::HwcDevice>(mock_device, mock_config, std::make_shared<mga::IntegerSourceCrop>());
}

typedef ::testing::Types<mga::HwcFbDevice, mga::HwcDevice> HWCDeviceTestTypes;
TYPED_TEST_CASE(HWCCommon, HWCDeviceTestTypes);

TYPED_TEST(HWCCommon, test_hwc_display_is_deactivated_on_destroy)
{
    auto device = this->make_display_device();
    EXPECT_CALL(*this->mock_config, power_mode(mga::DisplayName::primary, mir_power_mode_off));
    device.reset();
}

TYPED_TEST(HWCCommon, catches_exception_during_destruction)
{
    auto device = this->make_display_device();
    EXPECT_CALL(*this->mock_config, power_mode(mga::DisplayName::primary, mir_power_mode_off))
        .WillOnce(testing::Throw(std::runtime_error("")));
    device.reset();
}

TYPED_TEST(HWCCommon, first_power_on_is_not_fatal) //lp:1345533
{
    ON_CALL(*this->mock_config, power_mode(testing::_, mir_power_mode_on))
        .WillByDefault(testing::Throw(std::runtime_error("error")));
    EXPECT_NO_THROW({
        auto device = this->make_display_device();
    });
}
