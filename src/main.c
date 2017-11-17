//
// Created by Thibaud Lemaire on 16/11/2017.
//

#include <stdio.h>
#include "coroutine.h"
#include "brick.h"
#include "main.h"
#include "motors.h"
#include "console.h"
#include "color.h"

// Globals
int command = STOP;    /* Command for `drive` coroutine */
int alive;             /* Program is alive */
int max_speed;         /* Motor maximal speed (will be detected) */

int init( void )
{
    return (
        init_color() &
        init_motors() &
        init_console()
    );
}

int main( void )
{
    printf( "Waiting the EV3 brick online...\n" );
    if ( !brick_init()) return ( 1 );
    printf( "*** ( Denfendum ) Hello! ***\n" );
    alive = init();
    while ( alive ) {
        CORO_CALL( handle_brick_control );
        CORO_CALL( drive );
        CORO_CALL( color );
        sleep_ms( 10 );
    }
    brick_uninit();
    printf( "*** ( Defendum ) Bye! ***\n" );
    return ( 0 );
}
