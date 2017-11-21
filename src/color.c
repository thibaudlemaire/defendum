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
 * Main function of the color thread
 * @param arg
 * @return a generic pointer used by pthread
 */
void *color_main(void *arg)
    {
        int old_red, red, old_green, green, old_blue, blue; // Values [0 ; 1020]
        if ( color_sensor == SOCKET__NONE_ ) pthread_exit(NULL);
        while (alive)
        {
            // Waiting for color change
            if (( red = sensor_get_value(RED_COLOR, color_sensor, 0)) != old_red ) {
                old_red = red;
                color_red = red;
            }
            if (( green = sensor_get_value(GREEN_COLOR, color_sensor, 0)) != old_green ) {
                old_green = green;
                color_green = green;
            }
            if (( blue = sensor_get_value(BLUE_COLOR, color_sensor, 0)) != old_blue ) {
                old_blue = blue;
                color_blue = blue;
            }
            sleep_ms(COLOR_PERIOD);
        }
        pthread_exit(NULL);
    }
