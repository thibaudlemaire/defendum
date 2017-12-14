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
int rotate_front;
int rotation_speed = 150;
int up = 0;
enum enumobstacle obstacle_flag = NO_OBS;
int obstacle_counter = 0;
int obstacle_free_counter = 0;
int following_wall_state = 0;
int exploring_arena_state = 0;


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

        tacho_stop(MOTOR_NODE);
        tacho_stop(MOTOR_ROTATE);
        rotate_front = ( rotate_max_left + rotate_max_right ) / 2;

        return 1;
}

void *head_main(void *arg)
{
        while(alive)
        {
                if (robot_state==INITIALIZING || robot_state==WAITING_FOR_START) {
                        sleep_ms(50);
                        continue;
                }
                if (robot_state==BUILDING_MAP || robot_state==SENDING_MAP || robot_state==FINISH || robot_state==KICKED)
                        break;
                switch (crossing_state) {
                case SEARCHING_WALL:
                        searching_wall_head();
                        sleep_ms(MOTORS_PERIOD);
                        break;
                case FOLLOWING_WALL:
                        following_wall_head();
                        sleep_ms(MOTORS_PERIOD);
                        break;
                case EXPLORING_ARENA:
                        exploring_arena_head();
                        sleep_ms(MOTORS_PERIOD);
                        break;
                }
                sleep_ms(50);
        }
        pthread_exit(NULL);
}

void examine(void)
{
        do {
                look_left();
        } while (obstacle() && alive && !up);
        if(!alive || up)
                return;
        do {
                look_front();
        } while (obstacle() && alive && !up);
        if(!alive || up)
                return;
        do {
                look_right();
        } while (obstacle() && alive && !up);
        if(!alive || up)
                return;
        do {
                look_front();
        } while (obstacle() && alive && !up);
        return;
}

void searching_wall_head(void)
{
        //Only looking forward and update color and distance
        look_front();
        color_update();
        distance_update();
        if (distance_value<WALL_DISTANCE) {
                obstacle_counter++;
                obstacle_free_counter=0;
        } else {
                obstacle_free_counter++;
                obstacle_counter=0;
        }
        if (obstacle_counter>=3)
                obstacle_flag = FRONT_OBS;
        if (obstacle_free_counter>=3) {
                obstacle_flag = NO_OBS;
                obstacle_free_counter=0;
                obstacle_counter=0;
        }
}

void following_wall_head(void)
{
        if(following_wall_state==0) {
                look_front();
                color_update();
                distance_update();
                if (distance_value<WALL_DISTANCE) {
                        obstacle_counter++;
                        obstacle_free_counter=0;
                } else {
                        obstacle_free_counter++;
                        obstacle_counter=0;
                }
                if (obstacle_counter>=3)
                        obstacle_flag = FRONT_OBS;
                if (obstacle_free_counter>=3) {
                        obstacle_flag = NO_OBS;
                        obstacle_free_counter=0;
                        obstacle_counter=0;
                        following_wall_state=1;
                }
        } else {
                look_left();
                color_update();
                distance_update();
                if (distance_value<WALL_DISTANCE) {
                        obstacle_counter++;
                        obstacle_free_counter=0;
                } else {
                        obstacle_free_counter++;
                        obstacle_counter=0;
                }
                if (obstacle_counter>=3)
                        obstacle_flag = LEFT_OBS;
                if (obstacle_free_counter>=3) {
                        obstacle_flag = NO_OBS;
                        obstacle_free_counter=0;
                        obstacle_counter=0;
                        following_wall_state=1;
                }
        }
}

void exploring_arena_head(void)
{
        if(exploring_arena_state==0) {
                look_left();
                color_update();
                distance_update();
                if (distance_value<WALL_DISTANCE) {
                        obstacle_counter++;
                        obstacle_free_counter=0;
                } else {
                        obstacle_free_counter++;
                        obstacle_counter=0;
                }
                if (obstacle_counter>=3)
                        obstacle_flag = LEFT_OBS;
                if (obstacle_free_counter>=3) {
                        obstacle_flag = NO_OBS;
                        obstacle_free_counter=0;
                        obstacle_counter=0;
                        exploring_arena_state=1;
                }
        } else if (exploring_arena_state==1 || exploring_arena_state==3){
                look_front();
                color_update();
                distance_update();
                if (distance_value<WALL_DISTANCE) {
                        obstacle_counter++;
                        obstacle_free_counter=0;
                } else {
                        obstacle_free_counter++;
                        obstacle_counter=0;
                }
                if (obstacle_counter>=3)
                        obstacle_flag = FRONT_OBS;
                if (obstacle_free_counter>=3) {
                        obstacle_flag = NO_OBS;
                        obstacle_free_counter=0;
                        obstacle_counter=0;
                }
                if (obstacle_counter==0)
                        exploring_arena_state=(exploring_arena_state+1)%4;
        } else {
                look_right();
                color_update();
                distance_update();
                if (distance_value<WALL_DISTANCE) {
                        obstacle_counter++;
                        obstacle_free_counter=0;
                } else {
                        obstacle_free_counter++;
                        obstacle_counter=0;
                }
                if (obstacle_counter>=3)
                        obstacle_flag = RIGHT_OBS;
                if (obstacle_free_counter>=3) {
                        obstacle_flag = NO_OBS;
                        obstacle_free_counter=0;
                        obstacle_counter=0;
                        exploring_arena_state=3;
                }
        }
}

void rotate_head(void)
{
        look_left();
        look_right();
}

void look_left(void)
{
        int temp,temp2;
        if (up)
                return;
        tacho_set_speed_sp(MOTOR_ROTATE,rotation_speed);
        tacho_run_forever( MOTOR_ROTATE );
        while(temp2 != (int) tacho_get_position(MOTOR_ROTATE,0)) {
                temp2 = temp;
                temp = (int) tacho_get_position(MOTOR_ROTATE,0);
                sleep_ms(MOTORS_PERIOD);
        }
        tacho_stop(MOTOR_ROTATE);
        while(tacho_is_running( MOTOR_ROTATE )) ;
}

void look_front(void)
{
        if (up)
                return;
        tacho_set_speed_sp(MOTOR_ROTATE,rotation_speed);
        tacho_set_position_sp(MOTOR_ROTATE,rotate_front);
        tacho_run_to_abs_pos(MOTOR_ROTATE);
        while(tacho_is_running(MOTOR_ROTATE)) ;
}

void look_right(void)
{
        int temp,temp2;
        if (up)
                return;
        tacho_set_speed_sp(MOTOR_ROTATE,-rotation_speed);
        tacho_run_forever( MOTOR_ROTATE );
        while(temp2 != (int) tacho_get_position(MOTOR_ROTATE,0)) {
                temp2 = temp;
                temp = (int) tacho_get_position(MOTOR_ROTATE,0);
                sleep_ms(MOTORS_PERIOD);
        }
        tacho_stop(MOTOR_ROTATE);
        while(tacho_is_running( MOTOR_ROTATE )) ;
}

void head_up(void)
{
        int temp,temp2;
        up = 1;
        tacho_set_speed_sp(MOTOR_NODE,-300);
        tacho_run_forever( MOTOR_NODE );
        while(temp2 != (int) tacho_get_position(MOTOR_NODE,0)) {
                temp2 = temp;
                temp = (int) tacho_get_position(MOTOR_NODE,0);
                sleep_ms(MOTORS_PERIOD);
        }
        //tacho_stop(MOTOR_NODE);
        //while(tacho_is_running( MOTOR_NODE )) ;
}

void head_down(void)
{
        int temp, temp2;
        up = 0;
        tacho_set_speed_sp(MOTOR_NODE,210);
        tacho_run_forever( MOTOR_NODE );
        while(temp2 != (int) tacho_get_position(MOTOR_NODE,0)) {
                temp2 = temp;
                temp = (int) tacho_get_position(MOTOR_NODE,0);
                sleep_ms(MOTORS_PERIOD);
        }
        tacho_stop(MOTOR_NODE);
        while(tacho_is_running( MOTOR_NODE )) ;
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

int obstacle(void)
{
        color_update();
        distance_update();
        return 0;
}
