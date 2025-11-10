#ifndef VIA_DRIVER_H
#define VIA_DRIVER_H

#include "matrix.h"
#include "color.h"
#include "print.h"
#include "via.h"
#include "rgb_matrix.h"
#include "eeconfig.h"

enum via_custom_channel {
    id_color_channel = 0,
};

enum via_buttglow_value {
    id_color_select = 4,
};

typedef struct {
    uint8_t h;
    uint8_t s;
} layer_hs_t;

typedef union {
    uint8_t raw[8];   // raw access for EEPROM or VIA
    struct {
        struct {
            uint8_t h;
            uint8_t s;
        } color[4];    // 4 layers × 2 bytes each = 8 bytes total
    };
} layer_color_config_t;

void color_config_save(void);
void color_config_load(void);
void color_config_set_value( uint8_t *data );
void color_config_get_value( uint8_t *data );
void apply_layer_color(uint8_t layer);

#endif