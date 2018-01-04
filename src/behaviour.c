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
enum specificState specif_state = NORMAL;               // Secondary state
int obstacle_picked_up = 0;

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
        //if (!wait_for(START_RECEIVED)) break;

        robot_state = CROSSING_ARENA;
        //cross_arena();

        pickup_obstacle();
        sleep_ms(2000);
        drop_object();

        //specif_state = RELEASING_OBSTACLE;
        //if (!manage_events()) break;

        robot_state = BUILDING_MAP;
        // TODO Call build_map()

        robot_state = SENDING_MAP;
        //send_map();
    }
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
    while(alive && robot_state != STOP_RECEIVED)
    {
        switch (specif_state)
        {
            case MOVABLE_OBSTACLE_DETECTED:
                print_console("Movable obstacle detected, picking up");
                pickup_obstacle();
                specif_state = NORMAL;
                resume();
                break;
            case NON_MOVABLE_OBSTACLE_DETECTED_LEFT:
            case NON_MOVABLE_OBSTACLE_DETECTED_FRONT:
            case NON_MOVABLE_OBSTACLE_DETECTED_RIGHT:
                print_console("Non movable obstacle detected, avoiding");
                // TODO Add the obstacle on the map
                while (alive && distance_value < 200)
                    motors_rotate_left(AVOID_ANGLE);
                specif_state = NORMAL;
                resume();
                break;
            case RELEASING_OBSTACLE:
                print_console("Dropping object");
                drop_object();
                motors_rotate_left(90);
                specif_state = NORMAL;
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
    robot_state = START_RECEIVED;
}

/**
 * Function called by bluetooth module when server stop the game
 */
void stop_received() {
    robot_state = STOP_RECEIVED;
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
    switch(obstacle)
    {
        case NO_OBS:
            //resume();
            break;
        case NEAR_OBS:
            //motors_forward(SPEED_TWO);
            break;
        case REALLY_NEAR_OBS:
            //motors_forward(SPEED_ONE);
            break;
        case LEFT_OBS:
            //obstacle_on_left();
            break;
        case FRONT_OBS:
            //obstacle_on_front();
            break;
        case RIGHT_OBS:
            //obstacle_on_right();
            break;
    }
}

/**
 * Function used to manage an obstacle on the left
 */
void obstacle_on_left()
{
    print_console("Obstacle on left");
    head_stop();
    look_left();
    sleep_ms(WAIT_FOR_COLOR);
    color_update();
    if (color_red > RED_THRESHOLD && color_blue < BLUE_THRESHOLD && color_green < GREEN_THRESHOLD)
    {
        motors_rotate_left(GO_STRAIGHT_ANGLE);
        look_front();
        specif_state = MOVABLE_OBSTACLE_DETECTED;
    }
    else
        specif_state = NON_MOVABLE_OBSTACLE_DETECTED_LEFT;
}

/**
 * Function used to manage an obstacle on the front
 */
void obstacle_on_front()
{
    print_console("Obstacle on front");
    head_stop();
    look_front();
    sleep_ms(WAIT_FOR_COLOR);
    color_update();
    if (color_red > RED_THRESHOLD && color_blue < BLUE_THRESHOLD && color_green < GREEN_THRESHOLD)
    {
        motors_stop();
        specif_state = MOVABLE_OBSTACLE_DETECTED;
    }
    else
        specif_state = NON_MOVABLE_OBSTACLE_DETECTED_FRONT;
}

/**
 * Function used to manage an obstacle on the right
 */
void obstacle_on_right()
{
    print_console("Obstacle on right");
    head_stop();
    look_right();
    sleep_ms(WAIT_FOR_COLOR);
    color_update();
    if (color_red > RED_THRESHOLD && color_blue < BLUE_THRESHOLD && color_green < GREEN_THRESHOLD)
    {
        motors_rotate_right(GO_STRAIGHT_ANGLE);
        look_front();
        specif_state = MOVABLE_OBSTACLE_DETECTED;
    }
    else
        specif_state = NON_MOVABLE_OBSTACLE_DETECTED_RIGHT;
}

/**
 * Function used to pickup a movable obstacle
 */
void pickup_obstacle()
{
    print_console("Picking up object...");
    specif_state = PICKING_UP_OBSTACLE;
    head_up();
    motors_cross(PICKUP_CROSS);
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
    specif_state = RELEASING_OBSTACLE;
    head_up();
    motors_cross(DROP_CROSS);
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
}

/**
 * This function start crossing arena
 */
void cross_arena() {
    //head_move();                    // Move the head to find obstacles
    //motors_forward(SPEED_THREE);           // Go forward
}



