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

bool Seesaw_readTrellis(bool polling, matrix_row_t current_matrix[], trellis_orientation_t orientation) {
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
        rotate_coords(&row, &col, orientation);
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