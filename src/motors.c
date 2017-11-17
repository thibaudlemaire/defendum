//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include "motors.h"
#include "coroutine.h"
#include "brick.h"
#include "main.h"

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
