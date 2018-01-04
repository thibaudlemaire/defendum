//
// Created by Thibaud Lemaire on 16/11/2017.
//

#include <pthread.h>
#include "brick.h"
#include "main.h"
#include "motors.h"
#include "console.h"
#include "head.h"
#include "rotation.h"
#include "display.h"
#include "bluetooth.h"
#include "position.h"
#include "behaviour.h"
#include "touch.h"
#include <ncurses.h>

// Globals
enum commandState command = STOP;       // Command for `motor' module

int alive;                              // Program is alive
int color_detected = 0,
    touched = 0,
    compass_heading = 0,
    distance_value = 0,
    rotation_angle = 0,
    rotation_rspeed = 0;
pthread_mutex_t stdout_mutex;           // Mutex used to lock stdout

/**
 * Function used to init the robot
 * Inits every modules
 * @return 1 if all work, 0 otherwise
 */
int init( void )
{
        alive = 1;
        pthread_mutex_init(&stdout_mutex, NULL);
        return (
                       init_display() &
                       init_motors() &
                       init_head() &
                       init_rotation() &
                       init_bluetooth() &
                       init_console() &
                       init_touch() &
                       init_position()
        );
}

/**
 * Main function of the program, called first
 * @return exit code
 */
int main( void )
{
        // Declaration of threads
        pthread_t display_thread;
        pthread_t console_thread;
        pthread_t head_thread;
        pthread_t rotation_thread;
        //pthread_t bluetooth_thread;
        pthread_t position_thread;
        pthread_t behaviour_thread;
        pthread_t touch_thread;

        // Init brick library, to interface lego sensors and motors
        if ( !brick_init()) return ( 1 );

        // Init modules, quit on error
        if (!init()) {
                uninit_display();
                return ( 1 );
        }

        // Launch threads
        pthread_create(&head_thread, NULL, head_main, NULL);
        pthread_create(&rotation_thread, NULL, rotation_main, NULL);
        pthread_create(&display_thread, NULL, display_main, NULL);
        //pthread_create(&bluetooth_thread, NULL, bluetooth_main, NULL);
        pthread_create(&position_thread, NULL, position_main, NULL);
        pthread_create(&console_thread, NULL, console_main, NULL);
        pthread_create(&touch_thread, NULL, touch_main, NULL);
        pthread_create(&behaviour_thread, NULL, behaviour_main, NULL);

        // Wait for every thread to end
        pthread_join(display_thread, NULL);
        pthread_join(behaviour_thread, NULL);
        pthread_join(console_thread, NULL);
        pthread_join(head_thread, NULL);
        pthread_join(rotation_thread, NULL);
        //pthread_join(bluetooth_thread, NULL);
        pthread_join(touch_thread, NULL);
        pthread_join(position_thread, NULL);

        pthread_mutex_destroy(&stdout_mutex);

        motors_stop();
        // Release display
        uninit_display();

        return ( 0 );
}
