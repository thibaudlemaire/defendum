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

// Globals
int command = STOP;    /* Command for `drive` coroutine */
int alive;             /* Program is alive */
int max_speed;         /* Motor maximal speed (will be detected) */

int init( void )
{
    alive = 1;
    return (
        init_color() &
        init_motors() &
        init_console()
    );
}

int main( void )
{
    pthread_t console_thread;
    pthread_t motors_thread;
    pthread_t color_thread;

    printf( "Waiting the EV3 brick online...\n" );
    if ( !brick_init()) return ( 1 );
    printf( "*** ( Denfendum ) Hello! ***\n" );

    if (!init())
        return ( 1 );

    if(pthread_create(&motors_thread, NULL, motors_main, NULL) == -1) {
        perror("Error while creating motors_thread");
        return ( 1 );
    }
    if(pthread_create(&color_thread, NULL, color_main, NULL) == -1) {
        perror("Error while creating color_thread");
        return ( 1 );
    }
    if(pthread_create(&console_thread, NULL, console_main, NULL) == -1) {
        perror("Error while creating console_thread");
        return ( 1 );
    }
    if (pthread_join(console_thread, NULL)) {
        perror("Error during console_thread join");
        return ( 1 );
    }
    if (pthread_join(motors_thread, NULL)) {
        perror("Error during motors_thread join");
        return ( 1 );
    }
    if (pthread_join(color_thread, NULL)) {
        perror("Error during color_thread join");
        return ( 1 );
    }

    printf( "*** ( Defendum ) Bye! ***\n" );
    return ( 0 );
}
