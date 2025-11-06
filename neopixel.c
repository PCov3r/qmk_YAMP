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

void Seesaw_neopixColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {

  if (n < TRELLIS_NEOPIX_NUMBER) {

    if (brightness) { // See notes in setBrightness()
      r = (r * brightness) >> 8;
      g = (g * brightness) >> 8;
      b = (b * brightness) >> 8;
    }

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

void Seesaw_neopixIndicesColor(uint16_t n[], uint8_t r, uint8_t g, uint8_t b, uint8_t brightness, uint8_t len) {
  for (int i = 0; i < len; i++){
    Seesaw_neopixColor(n[i], r, g, b, brightness);
  }
}

void Seesaw_neopixArrayColor(uint16_t n[], uint8_t r[], uint8_t g[], uint8_t b[], uint8_t brightness, uint8_t len) {
  for (int i = 0; i < len; i++){
    Seesaw_neopixColor(n[i], r[i], g[i], b[i], brightness);
  }
}

void Seesaw_neopixAllColor(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {
  for (int i = 0; i < TRELLIS_NEOPIX_NUMBER; i++){
    Seesaw_neopixColor(i, r, g, b, brightness);
  }
}

void Seesaw_neopixIndexOff(uint16_t n) {
  Seesaw_neopixColor(n, 0, 0, 0, 0);
  Seesaw_neopixShow();
}

void Seesaw_neopixAllOff() {
  for (int i = 0; i < TRELLIS_NEOPIX_NUMBER; i++){
    Seesaw_neopixColor(i, 0, 0, 0, 0);
  }
  Seesaw_neopixShow();
}