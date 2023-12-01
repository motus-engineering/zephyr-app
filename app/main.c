/*
 * (c) 2023 Motus Design Group.
 *
 * SPDX-License-Identifier: Motus Design Group
 */
#include "supervisor.h"

#include <app_version.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    // Log firmware version
    LOG_INF("Motus Zephyr App Firmware %s", APP_VERSION_STRING);

    // Let main complete, Zephyr will handle task switching from here
    return 0;
}
