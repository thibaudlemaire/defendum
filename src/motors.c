//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <math.h>
#include "motors.h"
#include "brick.h"
#include "main.h"
#include "display.h"
#include "position.h"

int max_speed;     /* Motor maximal speed (will be detected) */
enum linearSpeed speed_linear = SPEED_ONE;
int speed_circular = SPEED_CIRCULAR;
enum commandState motors_state;

/**
 * Function used to init motors module
 * @return
 */
int init_motors( void )
{
        if ( tacho_is_plugged( MOTOR_BOTH, TACHO_TYPE__NONE_ )) { // any type of motor
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
 * Function called to turn left
 * @param angle
 */
void motors_rotate_left(int angle)
{
    tacho_stop( MOTOR_BOTH );
    while(tacho_is_running( MOTOR_BOTH ))
        sleep_ms(100);
    update_position(motors_state);
    motors_state = LEFT;
    int distance = angle * 2.35; // 90° on robot = 180° on wheel
    int position_motor_left = tacho_get_position(MOTOR_LEFT, 0) + distance;
    int position_motor_right = tacho_get_position(MOTOR_RIGHT, 0) - distance;
    tacho_set_speed_sp( MOTOR_BOTH, SPEED_TWO );
    tacho_set_position_sp( MOTOR_LEFT, position_motor_left);
    tacho_set_position_sp( MOTOR_RIGHT, position_motor_right);
    tacho_run_to_abs_pos( MOTOR_BOTH );
    while (tacho_is_running(MOTOR_BOTH) && alive)
        sleep_ms(100);
    motors_state = STOP;
}

/**
 * Function called to turn right
 * @param angle
 */
void motors_rotate_right(int angle)
{
    tacho_stop( MOTOR_BOTH );
    while(tacho_is_running( MOTOR_BOTH ))
        sleep_ms(100);
    update_position(motors_state);
    motors_state = RIGHT;
    int distance = angle * 2.35; // 90° on robot = 180° on wheel
    int position_motor_left = tacho_get_position(MOTOR_LEFT, 0) - distance;
    int position_motor_right = tacho_get_position(MOTOR_RIGHT, 0) + distance;
    tacho_set_speed_sp( MOTOR_BOTH, SPEED_TWO );
    tacho_set_position_sp( MOTOR_LEFT, position_motor_left);
    tacho_set_position_sp( MOTOR_RIGHT, position_motor_right);
    tacho_run_to_abs_pos( MOTOR_BOTH );
    while (tacho_is_running(MOTOR_BOTH) && alive)
        sleep_ms(100);
    motors_state = STOP;
}

/**
 * Function called to go forward
 * @param speed
 */
void motors_forward(enum linearSpeed speed)
{
    tacho_stop( MOTOR_BOTH );
    while(tacho_is_running( MOTOR_BOTH ))
        sleep_ms(100);
    update_position(motors_state);
    motors_state = FORTH;
    tacho_set_speed_sp( MOTOR_BOTH, speed );
    tacho_run_forever( MOTOR_BOTH );
}

/**
 * Function called to go backward
 * @param speed
 */
void motors_backward(enum linearSpeed speed)
{
    tacho_stop( MOTOR_BOTH );
    while(tacho_is_running( MOTOR_BOTH ))
        sleep_ms(100);
    update_position(motors_state);
    motors_state = BACK;
    tacho_set_speed_sp( MOTOR_BOTH, -speed );
    tacho_run_forever( MOTOR_BOTH );
}

/**
 * Function called to stop the robot
 */
void motors_stop(void)
{
    tacho_stop( MOTOR_BOTH );
    while(tacho_is_running( MOTOR_BOTH ))
        sleep_ms(100);
    update_position(motors_state);
    motors_state = STOP;
}

/**
 * Function called to go forward to a specific position
 * @param distance
 */
void motors_cross(int distance, enum linearSpeed speed)
{
    tacho_stop( MOTOR_BOTH );
    while(tacho_is_running( MOTOR_BOTH ))
        sleep_ms(100);
    update_position(motors_state);
    motors_state = FORTH;
    int position_motor_left = tacho_get_position(MOTOR_LEFT, 0) + distance;
    int position_motor_right = tacho_get_position(MOTOR_RIGHT, 0) + distance;
    tacho_set_speed_sp( MOTOR_BOTH, speed );
    tacho_set_position_sp( MOTOR_LEFT, position_motor_left);
    tacho_set_position_sp( MOTOR_RIGHT, position_motor_right);
    tacho_run_to_abs_pos( MOTOR_BOTH );
    while (tacho_is_running(MOTOR_BOTH) && alive)
        sleep_ms(100);
    update_position(motors_state);
    motors_state = STOP;
}
