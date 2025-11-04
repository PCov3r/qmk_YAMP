#ifndef SEESAW_H
#define SEESAW_H

#include "i2c_master.h"
#include "wait.h"
#include "matrix.h"
#include <string.h>
#include <stdbool.h>

#define MY_I2C_ADDRESS (0x2E << 1)
#define STATUS_BASE_REG 0x00
#define STATUS_RESET_REG 0xff
#define STATUS_SWRST_REG 0x7f

enum KEYPAD_EDGE{
  SEESAW_KEYPAD_EDGE_HIGH = 0,
  SEESAW_KEYPAD_EDGE_LOW,
  SEESAW_KEYPAD_EDGE_FALLING,
  SEESAW_KEYPAD_EDGE_RISING,
};


void Seesaw_resetAllRegisters(void);
bool SeeSaw_Write(uint8_t moduleBase, uint8_t moduleFunction, const uint8_t *buf, uint8_t num);
bool SeeSaw_read(uint8_t moduleBase, uint8_t moduleFunction, uint8_t *buf, uint8_t num, uint16_t delay);

#endif