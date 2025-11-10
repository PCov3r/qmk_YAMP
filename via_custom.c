#include "via_custom.h"

layer_color_config_t layer_color_config;
extern uint8_t current_tile;

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_color_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                color_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                color_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                color_config_save();
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}

void color_config_set_value( uint8_t *data )
{
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_color_select:
        {
            uint8_t index = value_data[0]; // == 0,1,2,3
            if ( index >= 0 && index < 4 )
            {
                layer_color_config.color[index].h = value_data[1];
                layer_color_config.color[index].s = value_data[2];
                if (current_tile == index) {
                    apply_layer_color(current_tile);
                }
            }
            break;
        }
    }
}

void color_config_get_value( uint8_t *data )
{
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch ( *value_id )
    {
        case id_color_select:
        {
            uint8_t index = value_data[0]; 
            if ( index >= 0 && index < 4 ) {
                value_data[1] = layer_color_config.color[index].h;
                value_data[2] = layer_color_config.color[index].s;
            }
            break;
        }
    }
}

void color_config_save(void) {
    eeconfig_update_user_datablock(&layer_color_config.raw, 0, sizeof(layer_color_config.raw));
}

void color_config_load(void) {
    eeconfig_read_user_datablock(&layer_color_config.raw, 0, sizeof(layer_color_config.raw));
}

void apply_layer_color(uint8_t layer) {
    if (layer >= 4) return; 

    uint8_t h = layer_color_config.color[layer].h;
    uint8_t s = layer_color_config.color[layer].s;
    uint8_t v = rgb_matrix_get_val();

    rgb_matrix_sethsv_noeeprom(h, s, v);
}