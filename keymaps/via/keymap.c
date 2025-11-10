#include QMK_KEYBOARD_H

#include "sendstring_french.h"
#include "via_custom.h"


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

uint8_t current_tile = 0;

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

led_config_t g_led_config = {
    {
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11},
        {12,13,14,15}
    }, {
        { 0,  0 }, { 75,  0 }, { 149,  0 }, { 224,  0 },
        { 0, 21 }, { 75, 21 }, { 149, 21 }, { 224, 21 },
        { 0, 43 }, { 75, 43 }, { 149, 43 }, { 224, 43 },
        { 0, 64 }, { 75, 64 }, { 149, 64 }, { 224, 64 }
    }, {
      1,1,1,1,
      1,1,1,1,
      1,1,1,1,
      1,1,1,1
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed)
        return true;

    switch (keycode) {
        case KC_TILE_JUMP0:
            current_tile = 0;
            layer_move(current_tile);
            apply_layer_color(current_tile);
            return false;

        case KC_TILE_JUMP1:
            current_tile = 1;
            layer_move(current_tile);
            apply_layer_color(current_tile);
            return false;

        case KC_TILE_JUMP2:
            current_tile = 2;
            layer_move(current_tile);
            apply_layer_color(current_tile);
            return false;

        case KC_TILE_JUMP3:
            current_tile = 3;
            layer_move(current_tile);
            apply_layer_color(current_tile);
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

  color_config_load();
  apply_layer_color(current_tile);
}
