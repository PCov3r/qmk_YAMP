#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_4x4(
        KC_Q, KC_W, KC_E, KC_R,
        KC_A, KC_S, KC_D, KC_F,
        KC_Z, KC_X, KC_C, KC_V,
        KC_1, KC_2, KC_3, KC_4
    )
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}