#include QMK_KEYBOARD_H

#include "sendstring_french.h"

enum layer_names {
    TILE_0,
    TILE_1,
    TILE_2,
    TILE_3,
    _NUM_TILES
};

enum custom_keycodes {
  KC_TILE_JUMP0 = SAFE_RANGE,
  KC_TILE_JUMP1,
  KC_TILE_JUMP2,
  KC_TILE_JUMP3,
};

static uint8_t current_tile = 0;

const uint16_t PROGMEM keymaps[_NUM_TILES][MATRIX_ROWS][MATRIX_COLS] = {
  [TILE_0] = LAYOUT_4x4(
    KC_TILE_JUMP0, KC_TILE_JUMP1, KC_TILE_JUMP2, KC_TILE_JUMP3,
    FR_A, FR_B, FR_C, FR_D,
    FR_E, FR_F, FR_G, FR_H,
    FR_I, FR_J, FR_K, FR_L
  ),
  [TILE_1] = LAYOUT_4x4(
    KC_TILE_JUMP0, KC_TILE_JUMP1, KC_TILE_JUMP2, KC_TILE_JUMP3,
    FR_E, FR_F, FR_G, FR_H,
    FR_E, FR_F, FR_G, FR_H,
    FR_I, FR_J, FR_K, FR_L
  ),
  [TILE_2] = LAYOUT_4x4(
    KC_TILE_JUMP0, KC_TILE_JUMP1, KC_TILE_JUMP2, KC_TILE_JUMP3,
    FR_I, FR_J, FR_K, FR_L,
    FR_E, FR_F, FR_G, FR_H,
    FR_I, FR_J, FR_K, FR_L
  ),
  [TILE_3] = LAYOUT_4x4(
    KC_TILE_JUMP0, KC_TILE_JUMP1, KC_TILE_JUMP2, KC_TILE_JUMP3,
    FR_0, FR_1, FR_2, FR_3,
    FR_E, FR_F, FR_G, FR_H,
    FR_I, FR_J, FR_K, FR_L
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed)
        return true;

    switch (keycode) {
        case KC_TILE_JUMP0:
            current_tile = 0;
            layer_move(current_tile);
            return false;

        case KC_TILE_JUMP1:
            current_tile = 1;
            layer_move(current_tile);
            return false;

        case KC_TILE_JUMP2:
            current_tile = 2;
            layer_move(current_tile);
            return false;

        case KC_TILE_JUMP3:
            current_tile = 3;
            layer_move(current_tile);
            return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}
