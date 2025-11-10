#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

#include "rgb_driver.h"

void rgb_matrix_driver_init(void) {
    i2c_init();
    Seesaw_neopixPin();
    Seesaw_neopixType();
    Seesaw_neopixLength();
}

void rgb_matrix_driver_flush(void) {
    Seesaw_neopixShow(); // Push color data to hardware
}

void rgb_matrix_driver_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t brightness = 200;
    uint16_t n = index;
    Seesaw_neopixColor(n, red, green, blue, brightness);
}

void rgb_matrix_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t brightness = 200;
    Seesaw_neopixAllColor(red, green, blue, brightness);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = rgb_matrix_driver_init,
    .flush         = rgb_matrix_driver_flush,
    .set_color     = rgb_matrix_driver_set_color,
    .set_color_all = rgb_matrix_driver_set_color_all,
};

bool rgb_matrix_indicators_kb() {
    if (!rgb_matrix_indicators_user()) {
         return false;
    }
    for (int i = 0; i < 4; i++) {
        uint8_t h = layer_color_config.color[i].h;
        uint8_t s = layer_color_config.color[i].s;
        uint8_t v = rgb_matrix_get_val();
        HSV hsv = {h, s, v};
        RGB rgb = hsv_to_rgb(hsv);

        // Ttop row is row 0
        uint8_t row = 0;
        uint8_t col = i;
        uint8_t led_index = g_led_config.matrix_co[row][col];

        rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
    }
    return true;
}

#endif