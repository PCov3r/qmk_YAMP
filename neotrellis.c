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

void Seesaw_readTrellis(bool polling) {
  uint8_t count = Seesaw_getKeypadCount();
  wait_us(500);
  if (count > 0) {
    if (polling)
      count = count + 2;
    keyEventRaw e[count];
    Seesaw_readKeypad(e, count);
    for (int i = 0; i < count; i++) {
      printf("%d: %d\n",e[i].bit.NUM, e[i].bit.EDGE);
    }
  }
}