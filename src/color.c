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
        color_set_mode_col_ambient( color_sensor );
        printf("Color sensor found and configured as Raw RGB\n");
        return ( 1 );
    }
    printf( "Color sensor not found, exit\n" );
    return ( 0 );
}

/* Coroutine of color sensor */
void *color_main(void *arg)
    {
        int old_red, red;
        if ( color_sensor == SOCKET__NONE_ ) pthread_exit(NULL);
        while (alive)
        {
            /* Waiting any IR RC button is pressed or released */
            if (( red = sensor_get_value(COLOR_RED, color_sensor, 0)) == old_red ) {
                sleep_ms( 50 );
                continue;
            }
            old_red = red;
            printf("Red value : %u \n", red);
        }
        printf("Exit color\n");
        pthread_exit(NULL);
    }
