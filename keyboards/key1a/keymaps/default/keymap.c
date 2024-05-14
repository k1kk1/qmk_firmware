// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "color.h"
#include "rgblight.h"

#define _BASE 0
#define _LOWER 1
#define _RAISE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
      MO(1), MO(2), 
      KC_C, KC_D,
      KC_E,   KC_F,   KC_G,  KC_H
    ),
    [_LOWER] = LAYOUT(
      MO(1), MO(2), 
      KC_C, KC_D,
      KC_E,   KC_F,   KC_G,  KC_H
    ),
    [_RAISE] = LAYOUT(
      MO(1), MO(2), 
      KC_C, KC_D,
      KC_E,   KC_F,   KC_G,  KC_H
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return false;
};

void oled_write_layer_state(void) {
    oled_write_P(PSTR(" "), false);

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 0:
            oled_write_P(PSTR("Base "), false);
            break;
        case 1:
            oled_write_P(PSTR("Lower"), false);
            break;
        case 2:
            oled_write_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_P(PSTR("Mouse"), false);
            break;
        case 4:
            oled_write_P(PSTR("L4   "), false);
            break;
        case 5:
            oled_write_P(PSTR("L5   "), false);
            break;
        case 6:
            oled_write_P(PSTR("L6   "), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
            break;
    }
}


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        rgblight_sethsv_range(HSV_BLUE, 0, 2);
        break;
    case _RAISE:
        rgblight_sethsv_range(HSV_RED, 0, 2);
        break;
    default:
        rgblight_sethsv_range( 0, 0, 0, 0, 2);
        break;
    }
    rgblight_set_effect_range( 2, 10);
      return state;
};;


bool oled_task_user(void) {
    oled_write_P(PSTR("Hello World!"), false);
    oled_write_layer_state();
    return false;
};
