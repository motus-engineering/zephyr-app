/*
 * (c) 2023 Motus Design Group.
 *
 * SPDX-License-Identifier: Motus Design Group
 */
#include "supervisor.h"

#include <app_version.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    while (1)
    {
        // Log firmware version
        LOG_INF("Motus Zephyr App Firmware %s", APP_VERSION_STRING);

        k_sleep(K_MSEC(1000));
    }

    // Let main complete, Zephyr will handle task switching from here
    return 0;
}
