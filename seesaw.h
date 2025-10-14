#include "i2c_master.h"

#define MY_I2C_ADDRESS (0x2E << 1)
#define STATUS_BASE_REG 0x00
#define STATUS_RESET_REG 0xff
#define STATUS_SWRST_REG 0x7f