//
// Created by Thibaud Lemaire on 16/11/2017.
//

#include <stdio.h>
#include <pthread.h>
#include "brick.h"
#include "main.h"
#include "motors.h"
#include "console.h"
#include "color.h"
#include "distance.h"

// Globals
int command = STOP;    /* Command for `drive` thread */
int alive;             /* Program is alive */
int max_speed;         /* Motor maximal speed (will be detected) */

int init( void )
{
    alive = 1;
    return (
        init_color() &
        init_motors() &
        init_distance() &
        init_console()

    );
}

int main( void )
{
    pthread_t console_thread;
    pthread_t motors_thread;
    pthread_t color_thread;
    pthread_t distance_thread;

    if ( !brick_init()) return ( 1 );
    printf( "*** ( Denfendum ) Hello! ***\n" );

    if (!init()) return ( 1 );

    pthread_create(&motors_thread, NULL, motors_main, NULL);
    pthread_create(&color_thread, NULL, color_main, NULL);
    pthread_create(&console_thread, NULL, console_main, NULL);
    pthread_create(&distance_thread, NULL, distance_main, NULL);

    pthread_join(console_thread, NULL);
    pthread_join(motors_thread, NULL);
    pthread_join(color_thread, NULL);
    pthread_join(distance_thread, NULL);

    printf( "*** ( Defendum ) Bye! ***\n" );
    return ( 0 );
}
