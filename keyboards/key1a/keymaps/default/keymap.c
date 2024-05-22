// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "color.h"
#include "rgblight.h"
#include "encoder.h"
#include "lib/layer_status/layer_status.h"

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _MOUSE 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
      KC_A, KC_B, KC_C, KC_D,
      KC_1, KC_2, TO(_LOWER), TO(_MOUSE)
    ),
    [_LOWER] = LAYOUT(
      KC_A, KC_B, KC_C, KC_D,
      KC_1, KC_2, TO(_RAISE), TO(_BASE)
    ),
    [_RAISE] = LAYOUT(
      KC_A, KC_B, KC_C, KC_D,
      KC_1, KC_2, TO(_MOUSE), TO(_LOWER)
    ),
    [_MOUSE] = LAYOUT(
      KC_A, KC_B, KC_C, KC_D,
      KC_1, KC_2, TO(_BASE), TO(_RAISE)
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

char keylog_str[24]  = {};
char keylogs_str[21] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // update keylogs
    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;
        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;
    keylogs_str_idx++;
}

const char *read_keylog(void) { return keylog_str; }
const char *read_keylogs(void) { return keylogs_str; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}


bool oled_task_user(void) {
    render_layer_status();
    // oled_write_ln(read_keylog(), false);
    // oled_write_ln(read_keylogs(), false);
    return false;
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(KC_PGDN, KC_PGUP), ENCODER_CCW_CW(TO(_LOWER), TO(_MOUSE)) },
    [_LOWER]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI), ENCODER_CCW_CW(TO(_RAISE), TO(_BASE)) },
    [_RAISE]  = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(RGB_SPD, RGB_SPI), ENCODER_CCW_CW(TO(_MOUSE), TO(_LOWER)) },
    [_MOUSE]  = { ENCODER_CCW_CW(RGB_TOG, RGB_TOG), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(TO(_BASE), TO(_RAISE)) },
};
