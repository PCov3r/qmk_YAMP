#pragma once

// Matrix size (1 NeoTrellis = 4x4)
#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define NEO_TRELLIS_NUM_KEYS MATRIX_ROWS*MATRIX_COLS

/* Number of RGBs */
#define RGB_MATRIX_LED_COUNT MATRIX_ROWS*MATRIX_COLS

#define I2C_DRIVER        I2CD1 
#define I2C1_SCL_PIN      GP7
#define I2C1_SDA_PIN      GP6

#define EECONFIG_USER_DATA_SIZE 8

#define ORIENTATION  ORIENT_180
