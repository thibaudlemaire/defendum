#include <pthread.h>
#include "brick.h"
#include "main.h"
#include "display.h"
#include "head.h"
#include "motors.h"
#include "color.h"
#include "distance.h"
#include "rotate.h"
#include "node.h"
#include "behaviour.h"

int up = 0;
enum headState head_state = HEAD_HOLD;
enum enumobstacle obstacle_flag = NO_OBS;
enum headMoveState head_move_state = HEAD_FRONT_TO_LEFT;

int obstacle_counter = 0;
int obstacle_free_counter = 0;
enum crosstate crossing_state = EXPLORING_ARENA;
int following_wall_state = 0;
int exploring_arena_state = 0;

/**
 * Function used to init head module
 * @return 1 is ok, 0 otherwise
 */
int init_head( void )
{
        if (!init_distance()) return 0;
        if (!init_color_sensor()) return 0;
        if (!init_rotate()) return 0;
        if (!init_node()) return 0;

        distance_update();
        color_update();

        return 1;
}

/**
 * Main function of the head thread
 * @param arg
 * @return pointer on the thread
 */
void *head_main(void *arg)
{
        while(alive)
        {
                switch (head_state) {
                        case HEAD_MOVING:
                                head_move_and_measure();
                                break;
                        case HEAD_HOLD:
                                head_measure();
                                break;
                }
                sleep_ms(HEAD_PERIOD);
        }
        reset_rotate();
        reset_node();
        pthread_exit(NULL);
}

/**
 * This function moves the head and operates a measure
 */
void head_move_and_measure()
{
        switch (head_move_state) {
                case HEAD_LEFT:
                        look_front();
                        head_move_state = HEAD_FRONT_TO_RIGHT;
                        break;
                case HEAD_FRONT_TO_RIGHT:
                        look_right();
                        head_move_state = HEAD_RIGHT;
                        break;
                case HEAD_RIGHT:
                        look_front();
                        head_move_state = HEAD_FRONT_TO_LEFT;
                        break;
                case HEAD_FRONT_TO_LEFT:
                        look_left();
                        head_move_state = HEAD_LEFT;
                        break;
        }
        head_measure();
}

/**
 * Function used to get the obstacle in front of the head
 * @return
 */
obstacle_t get_obstacle()
{
        enum enumobstacle detected_obstacle;

        distance_update();
        color_update();

        if (distance_value > CLEAR_THRESHOLD)
                detected_obstacle = NO_OBS;
        else if (distance_value > NEAR_THRESHOLD)
                detected_obstacle = NEAR_OBS;
        else if (distance_value > STOP_THRESHOLD)
                detected_obstacle = REALLY_NEAR_OBS;
        else
                switch (get_current_rotate_position())
                {
                        case ROTATE_LEFT_POSITION:
                                detected_obstacle = LEFT_OBS;
                        break;
                        case ROTATE_FRONT_POSITION:
                                detected_obstacle = FRONT_OBS;
                        break;
                        case ROTATE_RIGHT_POSITION:
                                detected_obstacle = RIGHT_OBS;
                        break;
                }
        return detected_obstacle;
}

/**
 * This function operates a measure and determine if an obstacle is in front of the robot
 */
void head_measure()
{
        obstacle_t detected_obstacle = get_obstacle();
        if (detected_obstacle != obstacle_flag){
                obstacle_flag = detected_obstacle;
                obstacle_update(detected_obstacle);
        }
}

/**
 * Function used to move the head left
 */
void look_left(void)
{
        if (up) return;
        rotate_left();
}

/**
 * Function used to move the head front
 */
void look_front(void)
{
        if (up) return;
        rotate_front();
}

/**
 * Function used to move the head right
 */
void look_right(void)
{
        if (up) return;
        rotate_right();
}

/**
 * Function used to move the head up
 */
void head_up(void)
{
        up = 1;
        node_up();
}

/**
 * Function used to move the head down
 */
void head_down(void)
{
        up = 0;
        node_down();
}

/**
 * Function used to start moving head
 */
void head_move()
{
        head_state = HEAD_MOVING;
}

/**
 * Function called to stop head movement
 */
void head_stop()
{
        head_state = HEAD_HOLD;
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

// Unused
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

// Unused
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

// Unused
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
                        exploring_arena_state=(exploring_arena_state+1)%4;
                }
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


