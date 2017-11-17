//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "motors.h"
#include "brick.h"
#include "main.h"

int max_speed;     /* Motor maximal speed (will be detected) */

int init_motors( void )
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
    return ( 1 );
}

/* Thread managing motors */
void *motors_main(void *arg)
    {
        int speed_linear, speed_circular;
        int state = STOP;
        speed_linear = max_speed * SPEED_LINEAR / 100;
        speed_circular = max_speed * SPEED_CIRCULAR / 100;
        while (alive)
        {
            /* Waiting new command */
            if ( state == command ) {
                sleep_ms( MOTORS_PERIOD );
                continue;
            }
            switch ( command ) {
                case STOP:
                    tacho_stop( MOTOR_BOTH );
                    /* Waiting the vehicle is stopped */
                    while(tacho_is_running( MOTOR_BOTH ));
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
        printf("Exit motors\n");
        pthread_exit(NULL);
    }
