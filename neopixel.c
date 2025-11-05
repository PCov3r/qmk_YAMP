#include "neopixel.h"

void Seesaw_neopixPin() {
    uint8_t pin = TRELLIS_NEOPIX_PIN;
    SeeSaw_Write(NEOPIXEL_BASE, NEOPIXEL_PIN, &pin, 1);
}

void Seesaw_neopixLength() {
    uint16_t numBytes = TRELLIS_NEOPIX_NUMBER * 3;
    uint8_t buf[] = {(uint8_t)(numBytes >> 8), (uint8_t)(numBytes & 0xFF)};
    SeeSaw_Write(NEOPIXEL_BASE, NEOPIXEL_BUF_LENGTH, buf, 2);
}

void Seesaw_neopixType() {
  uint8_t is800KHz = true;
  SeeSaw_Write(NEOPIXEL_BASE, NEOPIXEL_SPEED, &is800KHz, 1);
}

void Seesaw_neopixShow() {
  SeeSaw_Write(NEOPIXEL_BASE, NEOPIXEL_SHOW, NULL, 0);
}

void Seesaw_neopixColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {

  if (n < TRELLIS_NEOPIX_NUMBER) {

    uint8_t p[3];
    p[0] = g; // Store R,G,B
    p[1] = r;
    p[2] = b;

    uint8_t len = 3;
    uint16_t offset = n * len;

    uint8_t writeBuf[5];
    writeBuf[0] = (offset >> 8);
    writeBuf[1] = offset;
    memcpy(&writeBuf[2], p, len);

    SeeSaw_Write(NEOPIXEL_BASE, NEOPIXEL_BUF, writeBuf, len + 2);
  }
}