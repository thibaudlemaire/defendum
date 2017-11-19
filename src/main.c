//
// Created by Thibaud Lemaire on 16/11/2017.
//

#include <pthread.h>
#include "brick.h"
#include "main.h"
#include "motors.h"
#include "console.h"
#include "color.h"
#include "distance.h"
#include "rotation.h"
#include "compass.h"
#include "display.h"

// Globals
int command = STOP;    /* Command for `drive` thread */
int alive;             /* Program is alive */
int color_red,
    color_green,
    color_blue,
    compass_heading,
    distance_value,
    rotation_angle,
    rotation_rspeed;

int init( void )
{
    alive = 1;
    return (
        init_display() &
        init_color() &
        init_motors() &
        init_distance() &
        init_rotation() &
        init_compass() &
        init_console()

    );
}

int main( void )
{
    pthread_t display_thread;
    pthread_t console_thread;
    pthread_t motors_thread;
    pthread_t color_thread;
    pthread_t distance_thread;
    pthread_t rotation_thread;
    pthread_t compass_thread;

    if ( !brick_init()) return ( 1 );

    if (!init()) {
        uninit_display();
        return ( 1 );
    }

    pthread_create(&display_thread, NULL, display_main, NULL);
    pthread_create(&motors_thread, NULL, motors_main, NULL);
    pthread_create(&color_thread, NULL, color_main, NULL);
    pthread_create(&console_thread, NULL, console_main, NULL);
    pthread_create(&distance_thread, NULL, distance_main, NULL);
    pthread_create(&rotation_thread, NULL, rotation_main, NULL);
    pthread_create(&compass_thread, NULL, compass_main, NULL);

    pthread_join(console_thread, NULL);
    pthread_join(motors_thread, NULL);
    pthread_join(color_thread, NULL);
    pthread_join(distance_thread, NULL);
    pthread_join(rotation_thread, NULL);
    pthread_join(compass_thread, NULL);
    pthread_join(display_thread, NULL);

    uninit_display();

    return ( 0 );
}
