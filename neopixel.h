#ifndef NEOPIX_H
#define NEOPIX_H

#include "seesaw.h"
#include "print.h"
#include "wait.h"

#define NEOPIXEL_BASE 0x0E

#define NEOPIXEL_STATUS 0x00
#define NEOPIXEL_PIN 0x01
#define NEOPIXEL_SPEED 0x02
#define NEOPIXEL_BUF_LENGTH 0x03
#define NEOPIXEL_BUF 0x04
#define NEOPIXEL_SHOW 0x05

#define TRELLIS_NEOPIX_PIN 3
#define TRELLIS_NEOPIX_NUMBER MATRIX_ROWS*MATRIX_COLS
#define NEO_GRB ((1 << 6) | (1 << 4) | (0 << 2) | (2))
#define NEO_KHZ800 0x0000

typedef struct color
{
    unsigned char red;
    unsigned char blue;
    unsigned char green;
}color;

void Seesaw_neopixPin(void);
void Seesaw_neopixLength(void);
void Seesaw_neopixType(void);
void Seesaw_neopixShow(void);
void Seesaw_neopixColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);
void Seesaw_neopixIndicesColor(uint16_t n[], uint8_t r, uint8_t g, uint8_t b, uint8_t brightness, uint8_t len);
void Seesaw_neopixArrayColor(uint16_t n[], uint8_t r[], uint8_t g[], uint8_t b[], uint8_t brightness, uint8_t len);
void Seesaw_neopixAllColor(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);
void Seesaw_neopixIndexOff(uint16_t n);
void Seesaw_neopixAllOff(void);

#endif