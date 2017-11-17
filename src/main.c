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
    if ( tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )) {  /* any type of motor */
        max_speed = tacho_get_max_speed( MOTOR_LEFT, 0 );
        tacho_reset( MOTOR_BOTH );
    } else {
        printf( "Please, plug LEFT motor in B port,\n"
                        "RIGHT motor in C port and try again.\n"
        );
        /* Inoperative without motors */
        return ( 0 );
    }

    printf( "IR sensor is NOT found.\n"
                    "q : quitter\n"
                    "a : avancer\n"
                    "r : reculer\n"
                    "g : gauche\n"
                    "d : droite\n"
                    "s : stop\n"
    );

    return ( 1 );
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
