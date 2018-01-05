//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include <pthread.h>
#include "behaviour.h"
#include "motors.h"
#include "main.h"
#include "brick.h"
#include "display.h"
#include "touch.h"
#include "head.h"
#include "map.h"
#include "bluetooth.h"
#include "position.h"
#include "color.h"

enum globalState robot_state = INITIALIZING;            // Robot state
enum obstacleState obstacle_state = NORMAL;               // Secondary state
int obstacle_picked_up = 0;
int stop_received = 0;

/**
 * Main function of the behaviour thread
 * @param arg
 * @return pointer to the thread
 */
void *behaviour_main(void *arg)
{
    while(alive)
    {
        robot_state = INITIALIZING;
        //init_map_small_arena();

        robot_state = WAITING_FOR_START;
        //if (!wait_for(CROSSING_ARENA)) break;

        cross_arena();

        if (!manage_events()) break;

        robot_state = BUILDING_MAP;
        // TODO Call build_map()

        robot_state = SENDING_MAP;
        // send_map(); // TODO Uncomment to test it
    }
        head_reset();
        pthread_exit(NULL);
}

/**
 * Function used to wait for a particular global state
 * @param condition
 * @return 0 if program stop, 1 when condition is satisfied
 */
int wait_for(enum globalState condition) {
    while(alive && robot_state != condition)
        sleep_ms(BEHAVIOUR_PERIOD);
    if(alive) return 0;
    else return 1;
}

/**
 * Function called during crossing arena to manage events such as obstacle detection,
 * picking up, avoidance, etc.
 * @return
 */
int manage_events()
{
    while(alive && !stop_received)
    {
        switch (obstacle_state)
        {
            case OBSTACLE_TOUCHED:
                // TODO : Motors are still stopped, avoid obstacle and resume
                resume();
                break;
            case OBSTACLE_ON_LEFT:
            case OBSTACLE_ON_FRONT:
            case OBSTACLE_ON_RIGHT:
                print_console("Obstacle detected");
                // TODO Determine if it is movable or not
                resume();
                break;
            default:
                break;
        }
        sleep_ms(BEHAVIOUR_PERIOD);
    }
    if(alive) return 0;
    else return 1;
}

/**
 * Function called by bluetooth module when server start the game
 */
void start_received() {
    if(robot_state == WAITING_FOR_START)
        robot_state = CROSSING_ARENA;
}

/**
 * Function called by bluetooth module when server stop the game
 */
void stop_received() {
    stop_received = 1;
}

/**
 * Function called by the bluetooth module when robot get kicked
 */
void kicked() {
    motors_stop();
    alive = 0;
    robot_state = KICKED;
}

/**
 * Function called by head when a change occurs in front of the robot
 */
void obstacle_update(obstacle_t obstacle) {
    if(robot_state == CROSSING_ARENA)
        switch(obstacle)
        {
            case NO_OBS:
                resume();
                break;
            case NEAR_OBS:
                motors_forward(SPEED_TWO);
                break;
            case REALLY_NEAR_OBS:
                motors_forward(SPEED_ONE);
                break;
            case LEFT_OBS:
                obstacle_state = OBSTACLE_ON_LEFT;
                break;
            case FRONT_OBS:
                obstacle_state = OBSTACLE_ON_FRONT;
                break;
            case RIGHT_OBS:
                obstacle_state = OBSTACLE_ON_RIGHT;
            break;
        }
}

/**
 * Function used to manage an obstacle on the left
 */
void obstacle_on_left()
{
    print_console("Obstacle on left");
   // TODO Manage obstacle on left
}

/**
 * Function used to manage an obstacle on the front
 */
void obstacle_on_front()
{
    print_console("Obstacle on front");
    // TODO manage obstacle on front
}

/**
 * Function used to manage an obstacle on the right
 */
void obstacle_on_right()
{
    print_console("Obstacle on right");
    // TODO manage obstacle on right
}

void obstacle_touched()
{
    print_console("Obstacle touched...");
    motors_stop();
    obstacle_state = OBSTACLE_TOUCHED;
}

/**
 * Function used to pickup a movable obstacle
 */
void pickup_object()
{
    print_console("Picking up object...");
    head_up();
    motors_cross(PICKUP_CROSS, SPEED_TWO);
    head_down();
    bt_pick_up_obstacle(position_to_coordinates(current_position));
    obstacle_picked_up = 1;
}

/**
 * This function is used to drop an obstacle
 */
void drop_object()
{
    print_console("Droping object...");
    head_up();
    motors_cross(DROP_CROSS, SPEED_TWO);
    head_down();
    bt_pick_up_obstacle(position_to_coordinates(current_position));
    obstacle_picked_up = 1;
}

/**
 * This function is called at the end of an interrupt to resume robot state
 */
void resume()
{
    print_console("Resuming to normal state...");
    switch (robot_state)
    {
        case CROSSING_ARENA:
            cross_arena();
            break;
        default:
            break;
        // Other cases will come... searching wall, following wall
    }
    specif_state = NORMAL;
}

/**
 * This function start crossing arena
 */
void cross_arena() {
    head_move();                    // Move the head to find obstacles
    motors_forward(SPEED_THREE);           // Go forward
}



