//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <pthread.h>
#include "motors.h"
#include "brick.h"
#include "main.h"
#include "display.h"
#include "position.h"

int max_speed;     /* Motor maximal speed (will be detected) */

/**
 * Function used to init motors module
 * @return
 */
int init_motors( void )
{
        if ( tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )) { // any type of motor
                max_speed = tacho_get_max_speed( MOTOR_LEFT, 0 );
                tacho_reset( MOTOR_BOTH );
                tacho_set_stop_action_brake( MOTOR_BOTH );
                print_console("Motors found and configured");
        } else {
                print_error( "Please, plug LEFT motor in B port,");
                print_error( "RIGHT motor in C port and try again.");
                // Inoperative without motors
                return ( 0 );
        }
        return ( 1 );
}

/**
 * Main function of motor thread
 * @param arg
 * @return a generic pointer used by pthread
 */
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
                        while(tacho_is_running( MOTOR_BOTH )) ;
                        update_postion(state);
                        break;
                case FORTH:
                        tacho_stop( MOTOR_BOTH );
                        /* Waiting the vehicle is stopped */
                        while(tacho_is_running( MOTOR_BOTH )) ;
                        update_postion(state);
                        tacho_set_speed_sp( MOTOR_BOTH, speed_linear );
                        tacho_run_forever( MOTOR_BOTH );
                        break;
                case BACK:
                        tacho_stop( MOTOR_BOTH );
                        /* Waiting the vehicle is stopped */
                        while(tacho_is_running( MOTOR_BOTH )) ;
                        update_postion(state);
                        tacho_set_speed_sp( MOTOR_BOTH, -speed_linear );
                        tacho_run_forever( MOTOR_BOTH );
                        break;
                case LEFT:
                        tacho_stop( MOTOR_BOTH );
                        /* Waiting the vehicle is stopped */
                        while(tacho_is_running( MOTOR_BOTH )) ;
                        update_postion(state);
                        tacho_set_speed_sp( MOTOR_LEFT, speed_circular );
                        tacho_set_speed_sp( MOTOR_RIGHT, -speed_circular );
                        tacho_run_forever( MOTOR_BOTH );
                        break;
                case RIGHT:
                        tacho_stop( MOTOR_BOTH );
                        /* Waiting the vehicle is stopped */
                        while(tacho_is_running( MOTOR_BOTH )) ;
                        update_postion(state);
                        tacho_set_speed_sp( MOTOR_LEFT, -speed_circular );
                        tacho_set_speed_sp( MOTOR_RIGHT, speed_circular );
                        tacho_run_forever( MOTOR_BOTH );
                        break;
                }
                state = command;
        }
        pthread_exit(NULL);
}
