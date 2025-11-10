#include "neotrellis.h"

void Seesaw_enableKeypadInterrupt() {
    uint8_t val = 0x01;
    SeeSaw_Write(KEYPAD_BASE, KEYPAD_INTENSET, &val, 1);
}

void Seesaw_setKeypadEvent(uint8_t key, uint8_t edge, bool enable) {
    keyState ks;
    ks.bit.STATE = enable;
    ks.bit.ACTIVE = (1 << edge);
    uint8_t cmd[2] = {key, ks.reg};
    SeeSaw_Write(KEYPAD_BASE, KEYPAD_EVENT, cmd, 2);
}

void Seesaw_activateKey(uint8_t key, uint8_t edge, bool enable) {
    Seesaw_setKeypadEvent(NEO_TRELLIS_KEY(key), edge, enable);
}

uint8_t Seesaw_getKeypadCount() {
    uint8_t ret;
    SeeSaw_read(KEYPAD_BASE, KEYPAD_COUNT, &ret, 1, 500);
    return ret;
}

bool Seesaw_readKeypad(keyEventRaw *buf, uint8_t count) {
  return SeeSaw_read(KEYPAD_BASE,KEYPAD_FIFO, (uint8_t *)buf, count, 1000);
}

void rotate_coords(uint8_t *row, uint8_t *col, trellis_orientation_t orientation) {
  uint8_t r = *row;
  uint8_t c = *col;

  switch (orientation) {
    case ORIENT_0:
      break;
    case ORIENT_90:
      *row = c;
      *col = (MATRIX_ROWS - 1) - r;
      break;
    case ORIENT_180:
      *row = (MATRIX_ROWS - 1) - r;
      *col = (MATRIX_COLS - 1) - c;
      break;
    case ORIENT_270:
      *row = (MATRIX_COLS - 1) - c;
      *col = r;
      break;
  }
}

bool Seesaw_readTrellis(bool polling, matrix_row_t current_matrix[]) {
  bool changed = false;
  uint8_t count = Seesaw_getKeypadCount();
  wait_us(500);
  if (count > 0) {
    if (polling)
      count = count + 2;
    keyEventRaw e[count];
    Seesaw_readKeypad(e, count);
    for (int i = 0; i < count; i++) {
      e[i].bit.NUM = NEO_TRELLIS_SEESAW_KEY(e[i].bit.NUM);
      if (e[i].bit.NUM < NEO_TRELLIS_NUM_KEYS) {
        uint8_t row = e[i].bit.NUM / MATRIX_COLS;
        uint8_t col = e[i].bit.NUM % MATRIX_COLS;
        rotate_coords(&row, &col, ORIENTATION);
        uint8_t edge = e[i].bit.EDGE;
        #ifdef CONSOLE_ENABLE
          printf("%d, %d: %d\n",row, col, edge);
        #endif
        if (edge == SEESAW_KEYPAD_EDGE_RISING) {
          current_matrix[row] |= (1 << col);   // key pressed
          changed = true;
        } else if (edge == SEESAW_KEYPAD_EDGE_FALLING) {
          current_matrix[row] &= ~(1 << col);  // key released
          changed = true;
        }
      }
    }
  }
  return changed;
}

void exchange_led_index(led_config_t *config, trellis_orientation_t orientation){
    uint8_t rotated[MATRIX_ROWS][MATRIX_COLS];

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            uint8_t new_r = r;
            uint8_t new_c = c;
            rotate_coords(&new_r, &new_c, orientation);
            rotated[new_r][new_c] = config->matrix_co[r][c];
        }
    }

    memcpy(config->matrix_co, rotated, sizeof(rotated));
}

void exchange_led_positions(led_config_t *config, trellis_orientation_t orientation) {
    const float x_max = 224.0f;
    const float y_max = 64.0f;
    const uint8_t cols = MATRIX_COLS;
    const uint8_t rows = MATRIX_ROWS;

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        // Infer the current grid position from LED index
        uint8_t row = i / cols;
        uint8_t col = i % cols;

        // Rotate that grid coordinate
        rotate_coords(&row, &col, orientation);

        // Compute new X/Y from formula
        config->point[i].x = (uint8_t)((x_max / (cols - 1)) * col + 0.5f);
        config->point[i].y = (uint8_t)((y_max / (rows - 1)) * row + 0.5f);
    }
}
