//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <stdio.h>
#include "color.h"
#include "coroutine.h"
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
CORO_DEFINE( color )
    {
        CORO_LOCAL int old_red, red;
        CORO_BEGIN();
        if ( color_sensor == SOCKET__NONE_ ) CORO_QUIT();
        for ( ; ; ) {
            /* Waiting any IR RC button is pressed or released */
            CORO_WAIT(( red = sensor_get_value(COLOR_RED, color_sensor, 0)) != old_red );
            old_red = red;
            printf("Red value : %u \n", red);
            CORO_YIELD();
        }
        CORO_END();
    }
