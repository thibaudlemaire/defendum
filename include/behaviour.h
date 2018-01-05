//
// Created by Thibaud Lemaire on 23/11/2017.
//

#ifndef OS_ROBOT_BEHAVIOUR_H
#define OS_ROBOT_BEHAVIOUR_H

#include "head.h"

#define BEHAVIOUR_PERIOD 50
#define PICKUP_CROSS 350    // Travel, in mm, to pickup a movable obstacle
#define DROP_CROSS -400    // Travel, in mm, to drop a movable obstacle
#define WAIT_FOR_COLOR 500  // Time to wait for color measure in ms
#define AVOID_ANGLE     60  // in deg
#define GO_STRAIGHT_ANGLE 20    // Angle to put the robot in front of the movable object if it is on a side

//Enum
enum globalState {
        INITIALIZING,
        WAITING_FOR_START,
        CROSSING_ARENA,
        PICKING_UP_MOVABLE,
        RELEASING_MOVABLE,
        RELEASING_NON_MOVABLE,
        BUILDING_MAP,
        SENDING_MAP,
        KICKED,
};

enum obstacleState {
        NORMAL,
    OBSTACLE_ON_LEFT,
    OBSTACLE_ON_FRONT,
    OBSTACLE_ON_RIGHT,
    OBSTACLE_TOUCHED
};

extern enum globalState robot_state;            // Robot state
extern enum obstacleState obstacle_state;         // Secondary state

void *behaviour_main(void *arg);
int wait_for(enum globalState condition);
int manage_events();
void start_received();
void stop_received();
void kicked();
void obstacle_update(obstacle_t obstacle);
void obstacle_on_left();
void obstacle_on_front();
void obstacle_on_right();
void obstacle_touched();
void cross_arena(void);
void pickup_oject();
void drop_object();
void resume();

void search_wall(void);
void follow_wall(void);
void explore_arena(void);

#endif //OS_ROBOT_BEHAVIOUR_H
