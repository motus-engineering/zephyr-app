/*
 * (c) 2023 Motus Design Group.
 *
 * SPDX-License-Identifier: Motus Design Group
 */
/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/usb/usbd.h>
#include <zephyr/usb/usbh.h>

// #include "usbh_ch9.h"
// #include "usbh_device.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(usb_test, LOG_LEVEL_INF);

USBH_CONTROLLER_DEFINE(uhs_ctx, DEVICE_DT_GET(DT_NODELABEL(zephyr_uhc0)));

static int usb_host_enable(void)
{
	// struct usb_device *udev;
	int err;

    do
    {
        err = usbh_init(&uhs_ctx);
        __ASSERT(err == 0, "Failed to initialize USB host");

        err = usbh_enable(&uhs_ctx);
        __ASSERT(err == 0, "Failed to enable USB host");

        err = uhc_bus_reset(uhs_ctx.dev);
        __ASSERT(err == 0, "Failed to signal bus reset");

        err = uhc_bus_resume(uhs_ctx.dev);
        __ASSERT(err == 0, "Failed to signal bus resume");

        err = uhc_sof_enable(uhs_ctx.dev);
        __ASSERT(err == 0, "Failed to enable SoF generator");
    } while (0);

    // if (!err)
    // {
    //     LOG_INF("Host controller enabled");

    //     udev = usbh_device_get_any(&uhs_ctx);
    //     udev->state = USB_STATE_DEFAULT;
    // }

    return err;	
}

static int usb_host_shutdown(void)
{
	int err;

	err = usbh_disable(&uhs_ctx);
	__ASSERT(err == 0, "Failed to disable USB host");

	LOG_INF("Host controller disabled");

    return err;
}


int main(void)
{
    usb_host_enable();

    while (1)
    {
        // Log firmware version
        // LOG_INF("Motus Zephyr App Firmware %s", APP_VERSION_STRING);

        k_sleep(K_MSEC(1000));
    }

    usb_host_shutdown();

    // Let main complete, Zephyr will handle task switching from here
    return 0;
}