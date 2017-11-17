//
// Created by Thibaud Lemaire on 16/11/2017.
//

#include <stdio.h>
#include "coroutine.h"
#include "brick.h"
#include "main.h"
#include "motors.h"
#include "console.h"

// Globals
int command = STOP;    /* Command for `drive` coroutine */
int alive;             /* Program is alive */
int max_speed;         /* Motor maximal speed (will be detected) */

int init( void )
{
    return (
        init_console() &
        init_motors()
    );
}

int main( void )
{
    printf( "Waiting the EV3 brick online...\n" );
    if ( !brick_init()) return ( 1 );
    printf( "*** ( EV3 ) Hello! ***\n" );
    alive = init();
    while ( alive ) {
        CORO_CALL( handle_brick_control );
        CORO_CALL( drive );
        sleep_ms( 10 );
    }
    brick_uninit();
    printf( "*** ( EV3 ) Bye! ***\n" );
    return ( 0 );
}
