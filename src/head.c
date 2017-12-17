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

int up = 0;
enum enumobstacle obstacle_flag = NO_OBS;
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
        if (!init_node()) return 0;
        if (!init_rotate()) return 0;

        distance_update();
        color_update();

        return 1;
}

void *head_main(void *arg)
{
        while(alive)
        {
                switch (crossing_state) {
                case SEARCHING_WALL:
                        searching_wall_head();
                        sleep_ms(HEAD_PERIOD);
                        break;
                case FOLLOWING_WALL:
                        following_wall_head();
                        sleep_ms(HEAD_PERIOD);
                        break;
                case EXPLORING_ARENA:
                        exploring_arena_head();
                        sleep_ms(HEAD_PERIOD);
                        break;
                }
                sleep_ms(50);
        }
        tacho_reset( MOTOR_ROTATE );
        tacho_reset( MOTOR_NODE );
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

void rotate_head(void)
{
        look_left();
        look_right();
}

void look_left(void)
{
        if (up) return;
        rotate_left();
}

void look_front(void)
{
        if (up) return;
        rotate_front();
}

void look_right(void)
{
        if (up) return;
        rotate_right();
}

void head_up(void)
{
        up = 1;
        node_up();
}

void head_down(void)
{
        up = 0;
        node_down();
}

int obstacle(void)
{
        color_update();
        distance_update();
        return 0;
}
