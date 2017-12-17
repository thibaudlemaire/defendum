//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <pthread.h>
#include "color.h"
#include "brick.h"
#include "main.h"
#include "display.h"

POOL_T color_sensor;             // Color sensor port

/**
 * Function used to init color sensor module
 * @return 1 if ok, 0 otherwise
 */
int init_color_sensor( void )
{
        color_sensor = sensor_search( LEGO_EV3_COLOR );
        if ( color_sensor ) {
                color_set_mode_rgb_raw( color_sensor );
                print_console("Color sensor found and configured as Raw RGB");
                return ( 1 );
        }
        print_error( "Color sensor not found, exit" );
        return ( 0 );
}

/**
 * Function called to update colors
 */
void color_update(void)
{
        color_red = sensor_get_value(RED_COLOR, color_sensor, 0);
        color_green = sensor_get_value(GREEN_COLOR, color_sensor, 0);
        color_blue = sensor_get_value(BLUE_COLOR, color_sensor, 0);
}

