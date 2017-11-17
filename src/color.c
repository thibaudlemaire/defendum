//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <stdio.h>
#include <pthread.h>
#include "color.h"
#include "brick.h"
#include "main.h"

POOL_T color_sensor;             /* Color sensor port (will be detected) */

int init_color( void )
{
    color_sensor = sensor_search( LEGO_EV3_COLOR );
    if ( color_sensor ) {
        color_set_mode_rgb_raw( color_sensor );
        printf("Color sensor found and configured as Raw RGB\n");
        return ( 1 );
    }
    printf( "Color sensor not found, exit\n" );
    return ( 0 );
}

/* Thread of color sensor */
void *color_main(void *arg)
    {
        int old_red, red, old_green, green, old_blue, blue;
        if ( color_sensor == SOCKET__NONE_ ) pthread_exit(NULL);
        while (alive)
        {
            /* Waiting color change */
            if (( red = sensor_get_value(COLOR_RED, color_sensor, 0)) != old_red ) {
                old_red = red;
                printf("Red value : %u \n", red);
            }
            if (( green = sensor_get_value(COLOR_GREEN, color_sensor, 0)) != old_green ) {
                old_green = green;
                printf("Green value : %u \n", green);
            }
            if (( blue = sensor_get_value(COLOR_BLUE, color_sensor, 0)) != old_blue ) {
                old_blue = blue;
                printf("Blue value : %u \n", blue);
            }
            sleep_ms(COLOR_PERIOD);

        }
        printf("Exit color\n");
        pthread_exit(NULL);
    }
