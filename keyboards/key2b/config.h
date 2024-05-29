// Copyright 2023 Leon Anavi <leon@anavi.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Double tap reset button to enter bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
// Pro micro rp2040 LED
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
// Raspberry Pi Pico LED
// #define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define I2C_DRIVER I2CD1

#define I2C1_SCL_PIN GP2
#define I2C1_SDA_PIN GP3

