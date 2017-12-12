#include <pthread.h>
#include "brick.h"
#include "main.h"
#include "display.h"
#include "head.h"
#include "motors.h"

POOL_T distance_sensor;
POOL_T color_sensor;
int rotate_max_left=100000;
int rotate_max_right=100000;
int node_max_up=100000;
int node_max_down=100000;



/**
 * Function used to init head module
 * @return 1 is ok, 0 otherwise
 */
int init_head( void )
{
        distance_sensor = sensor_search( LEGO_EV3_US );
        if ( !distance_sensor ) {
                print_error( "Distance sensor not found, exit" );
                return 0;
        }
        color_sensor = sensor_search( LEGO_EV3_COLOR );
        if ( !color_sensor ) {
                print_error( "Color sensor not found, exit" );
                return 0;
        }
        if ( !tacho_is_plugged( MOTOR_ROTATE, TACHO_TYPE__NONE_ )) {
                print_error("Head rotation motor not found, exit");
                return 0;
        }
        if ( !tacho_is_plugged( MOTOR_NODE, TACHO_TYPE__NONE_ )) {
                print_error("Head node motor not found, exit");
                return 0;
        }
        us_set_mode_us_dc_cm( distance_sensor );
        print_console("Distance sensor found and configured");
        distance_update();
        color_set_mode_rgb_raw( color_sensor );
        print_console("Color sensor found and configured as Raw RGB");
        color_update();
        tacho_reset( MOTOR_ROTATE );
        tacho_set_stop_action_brake( MOTOR_ROTATE );
        tacho_reset( MOTOR_NODE );
        tacho_set_stop_action_brake( MOTOR_NODE );

        tacho_set_speed_sp(MOTOR_ROTATE,500);
        tacho_run_forever( MOTOR_ROTATE );
        while(rotate_max_left != (int) tacho_get_position(MOTOR_ROTATE,0)) {
                rotate_max_left = (int) tacho_get_position(MOTOR_ROTATE,0);
                sleep_ms(MOTORS_PERIOD);
        }
        tacho_set_speed_sp(MOTOR_ROTATE,-500);
        tacho_run_forever( MOTOR_ROTATE );
        while(rotate_max_right != (int) tacho_get_position(MOTOR_ROTATE,0)) {
                rotate_max_right = (int) tacho_get_position(MOTOR_ROTATE,0);
                sleep_ms(MOTORS_PERIOD);
        }
        tacho_stop(MOTOR_ROTATE);
        tacho_set_speed_sp(MOTOR_NODE,-210);
        tacho_run_forever(MOTOR_NODE);
        while(node_max_up != (int) tacho_get_position(MOTOR_NODE,0)) {
                node_max_up = (int) tacho_get_position(MOTOR_NODE,0);
                sleep_ms(MOTORS_PERIOD);
        }
        tacho_set_speed_sp(MOTOR_NODE,210);
        tacho_run_forever(MOTOR_NODE);
        while(node_max_down != (int) tacho_get_position(MOTOR_NODE,0)) {
                node_max_down = (int) tacho_get_position(MOTOR_NODE,0);
                sleep_ms(MOTORS_PERIOD);
        }
        tacho_stop(MOTOR_NODE);
        tacho_set_speed_sp(MOTOR_ROTATE,210);
        tacho_set_speed_sp(MOTOR_ROTATE,210);

        return 1;
}

void *head_main(void *arg)
{
        while(alive)
        {
                color_update();
                distance_update();
                look_left();
                look_right();
                head_up();
                head_down();
                sleep_ms(DISTANCE_PERIOD);
        }
        pthread_exit(NULL);
}

void rotate_head(void)
{

}

void look_left(void)
{
        print_console("Looking left");
        tacho_set_speed_sp(MOTOR_ROTATE,210);
        tacho_set_position_sp(MOTOR_ROTATE,rotate_max_left);
        tacho_run_to_abs_pos(MOTOR_ROTATE);
        while(rotate_max_left != (int) tacho_get_position(MOTOR_ROTATE,0)){
                print_console("Left : reaching to position")
                sleep_ms(MOTORS_PERIOD);
        }

        tacho_stop(MOTOR_ROTATE);
}

void look_right(void)
{
        print_console("Looking right");
        tacho_set_speed_sp(MOTOR_ROTATE,-210);
        tacho_set_position_sp(MOTOR_ROTATE,rotate_max_right);
        tacho_run_to_abs_pos(MOTOR_ROTATE);
        while(rotate_max_right != (int) tacho_get_position(MOTOR_ROTATE,0))
                sleep_ms(MOTORS_PERIOD);
        tacho_stop(MOTOR_ROTATE);
}

void head_up(void)
{
        tacho_set_speed_sp(MOTOR_ROTATE,-210);
        tacho_set_position_sp(MOTOR_NODE,node_max_up);
        tacho_run_to_abs_pos(MOTOR_NODE);
        while(node_max_up != (int) tacho_get_position(MOTOR_NODE,0))
                sleep_ms(MOTORS_PERIOD);
        tacho_stop(MOTOR_NODE);
}

void head_down(void)
{
        tacho_set_speed_sp(MOTOR_ROTATE,210);
        tacho_set_position_sp(MOTOR_NODE,node_max_down);
        tacho_run_to_abs_pos(MOTOR_NODE);
        while(node_max_down != (int) tacho_get_position(MOTOR_NODE,0))
                sleep_ms(MOTORS_PERIOD);
        tacho_stop(MOTOR_NODE);
}

void color_update(void)
{
        color_red = sensor_get_value(RED_COLOR, color_sensor, 0);
        color_green = sensor_get_value(GREEN_COLOR, color_sensor, 0);
        color_blue = sensor_get_value(BLUE_COLOR, color_sensor, 0);
}


void distance_update(void)
{
        distance_value = sensor_get_value(DISTANCE_CM_MODE, distance_sensor, 0);
}
