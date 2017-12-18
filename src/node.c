//
// Created by Thibaud Lemaire on 17/12/2017.
//

#include "brick.h"
#include "node.h"
#include "main.h"
#include "display.h"

int node_max_down;
int node_max_up;

/**
 * Function used to init node module
 * @return 1 is ok, 0 otherwise
 */
int init_node( void )
{
    if ( !tacho_is_plugged( MOTOR_NODE, TACHO_TYPE__NONE_ )) {
        print_error("Head node motor not found, exit");
        return 0;
    }
    tacho_reset( MOTOR_NODE );
    tacho_set_stop_action_hold( MOTOR_NODE );
    tacho_set_speed_sp(MOTOR_NODE, NODE_SPEED);
    node_max_down = tacho_get_position(MOTOR_NODE, 0) - NODE_FLOOR_OFFSET;
    node_max_up = node_max_down - NODE_RANGE;
    node_down();
    return  1;
}

/**
 * Function used to reset the node motor
 */
void reset_node()
{
    tacho_reset(MOTOR_NODE);
}

/**
 * Function used to put the head up
 */
void node_up()
{
    tacho_set_stop_action_coast( MOTOR_NODE );
    sleep_ms(300);
    tacho_set_stop_action_hold( MOTOR_NODE );
    tacho_set_position_sp(MOTOR_NODE, node_max_up);
    tacho_set_speed_sp(MOTOR_NODE, NODE_SPEED);
    tacho_run_to_abs_pos(MOTOR_NODE);
    sleep_ms(300);
    while( !(tacho_get_state(MOTOR_NODE) && TACHO_HOLDING))
        sleep_ms(NODE_PERIOD);
}

/**
 * Function used to put the head down
 */
void node_down()
{
    tacho_set_stop_action_hold( MOTOR_NODE );
    tacho_set_position_sp(MOTOR_NODE, node_max_down);
    tacho_set_speed_sp(MOTOR_NODE, NODE_SPEED);
    tacho_run_to_abs_pos(MOTOR_NODE);
    sleep_ms(300);
    while( !(tacho_get_state(MOTOR_NODE) && TACHO_HOLDING))
        sleep_ms(NODE_PERIOD);
}
