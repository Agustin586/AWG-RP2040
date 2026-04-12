# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(BOARD nucleo_h755zi_q/stm32h755xx/m7)

set(ZEPHYR_BASE "D:/aguat/Documents/GitHub/STM32/zephyrProject/deps/zephyr" CACHE PATH "Zephyr base directory")

set(DTC_OVERLAY_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/overlays/app.overlay
    ${CMAKE_CURRENT_SOURCE_DIR}/overlays/spi_ipc.overlay
    ${CMAKE_CURRENT_SOURCE_DIR}/overlays/btn.overlay
)

find_package(Zephyr REQUIRED HINTS ${ZEPHYR_BASE})
project(firmware_panel)

target_include_directories(app PRIVATE commons src)

add_subdirectory(commons)
add_subdirectory(src)
add_subdirectory(ztest)

