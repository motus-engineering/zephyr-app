# SPDX-License-Identifier: Apache-2.0

board_runner_args(jlink "--device=STM32L476RG" "--speed=4000")

set(SUPPORTED_EMU_PLATFORMS renode)
set(RENODE_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/support/app_nucleo_l476rg.resc)
set(RENODE_UART sysbus.usart2)

include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
