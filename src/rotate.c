//
// Created by Thibaud Lemaire on 17/12/2017.
//

#include "brick.h"
#include "rotate.h"
#include "main.h"
#include "display.h"

int rotate_left_position = POSITION_INIT;
int rotate_right_position = POSITION_INIT;
int rotate_front_position = POSITION_INIT;

rotate_pos_t rotate_current_position;

/**
 * Function used to init rotate module
 * @return 1 is ok, 0 otherwise
 */
int init_rotate( void )
{
    if ( !tacho_is_plugged( MOTOR_ROTATE, TACHO_TYPE__NONE_ )) {
        print_error("Head rotation motor not found, exit");
        return 0;
    }

    tacho_reset( MOTOR_ROTATE );
    tacho_set_stop_action_hold( MOTOR_ROTATE );

    tacho_set_speed_sp(MOTOR_ROTATE, ROTATE_SPEED);
    tacho_run_forever( MOTOR_ROTATE );
    while(rotate_left_position != (int) tacho_get_position(MOTOR_ROTATE,0)) {
        rotate_left_position = (int) tacho_get_position(MOTOR_ROTATE,0);
        sleep_ms(ROTATE_PERIOD);
    }

    tacho_set_speed_sp(MOTOR_ROTATE, -ROTATE_SPEED);
    tacho_run_forever( MOTOR_ROTATE );
    while(rotate_right_position != (int) tacho_get_position(MOTOR_ROTATE,0)) {
        rotate_right_position = (int) tacho_get_position(MOTOR_ROTATE,0);
        sleep_ms(ROTATE_PERIOD);
    }

    rotate_front_position = ( rotate_left_position + rotate_right_position ) / 2;
    rotate_front();

    return 1;
}

/**
 * Function used to reset the motor
 */
void reset_rotate() {
    tacho_reset(MOTOR_ROTATE);
}

/**
 * Turn the head on the left
 */
void rotate_left() {
    tacho_set_position_sp(MOTOR_ROTATE, rotate_left_position);
    tacho_run_to_abs_pos(MOTOR_ROTATE);
    sleep_ms(300);
    while( !(tacho_get_state(MOTOR_ROTATE) && TACHO_HOLDING))
        sleep_ms(ROTATE_PERIOD);
    rotate_current_position = ROTATE_LEFT_POSITION;
}

/**
 * Turn the head on the front
 */
void rotate_front() {
    tacho_set_position_sp(MOTOR_ROTATE, rotate_front_position);
    tacho_run_to_abs_pos(MOTOR_ROTATE);
    sleep_ms(300);
    while( !(tacho_get_state(MOTOR_ROTATE) && TACHO_HOLDING))
        sleep_ms(ROTATE_PERIOD);
    rotate_current_position = ROTATE_FRONT_POSITION;
}

/**
 * Turn the head on the right
 */
void rotate_right() {
    tacho_set_position_sp(MOTOR_ROTATE, rotate_right_position);
    tacho_run_to_abs_pos(MOTOR_ROTATE);
    sleep_ms(300);
    while( !(tacho_get_state(MOTOR_ROTATE) && TACHO_HOLDING))
        sleep_ms(ROTATE_PERIOD);
    rotate_current_position = ROTATE_RIGHT_POSITION;
}

rotate_pos_t get_current_rotate_position() {
    return rotate_current_position;
}
