#include <stdio.h>
#include "coroutine.h"
#include "brick.h"
#define SPEED_LINEAR    75  /* Motor speed for linear motion, in percents */
#define SPEED_CIRCULAR  10  /* ... for circular motion */
int max_speed;         /* Motor maximal speed (will be detected) */
#define MOTOR_LEFT     OUTC
#define MOTOR_RIGHT    OUTB
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )
enum {
    STOP,
    FORTH,
    BACK,
    LEFT,
    RIGHT,
};
int command = STOP;    /* Command for `drive` coroutine */
int alive;             /* Program is alive */
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
CORO_CONTEXT( handle_brick_control );
CORO_CONTEXT( drive );

/* Coroutine of the console key handling */
CORO_DEFINE( handle_brick_control )
        {
        CORO_LOCAL char pressed;
        CORO_BEGIN();
        for ( ; ; ) {
            /* Waiting any brick's key is pressed or released */
            CORO_WAIT(scanf("%c", &pressed));
            switch ( pressed ) {
                /* Quit */
                case 'q':
                    command = STOP;
                    alive = 0;
                    break;
                    /* Stop */
                case 's':
                    command = STOP;
                    break;
                    /* Forward */
                case 'a':
                    command = FORTH;
                    break;
                    /* Backward */
                case 'r':
                    command = BACK;
                    break;
                    /* Left */
                case 'g':
                    command = LEFT;
                    break;
                    /* Right */
                case 'd':
                    command = RIGHT;
                    break;
            }
            CORO_YIELD();
        }
        CORO_END();
        }

/* Coroutine of control the motors */
CORO_DEFINE( drive )
        {
                CORO_LOCAL int speed_linear, speed_circular;
        CORO_LOCAL int state = STOP;
        CORO_BEGIN();
        speed_linear = max_speed * SPEED_LINEAR / 100;
        speed_circular = max_speed * SPEED_CIRCULAR / 100;
        for ( ; ; ) {
            /* Waiting new command */
            CORO_WAIT( state != command );
            switch ( command ) {
                case STOP:
                    tacho_stop( MOTOR_BOTH );
                    /* Waiting the vehicle is stopped */
                    CORO_WAIT( !tacho_is_running( MOTOR_BOTH ));
                    break;
                case FORTH:
                    tacho_set_speed_sp( MOTOR_BOTH, speed_linear );
                    tacho_run_forever( MOTOR_BOTH );
                    break;
                case BACK:
                    tacho_set_speed_sp( MOTOR_BOTH, -speed_linear );
                    tacho_run_forever( MOTOR_BOTH );
                    break;
                case LEFT:
                    tacho_set_speed_sp( MOTOR_LEFT, speed_circular );
                    tacho_set_speed_sp( MOTOR_RIGHT, -speed_circular );
                    tacho_run_forever( MOTOR_BOTH );
                    break;
                case RIGHT:
                    tacho_set_speed_sp( MOTOR_LEFT, -speed_circular );
                    tacho_set_speed_sp( MOTOR_RIGHT, speed_circular );
                    tacho_run_forever( MOTOR_BOTH );
                    break;
            }
            state = command;
        }
        CORO_END();
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
