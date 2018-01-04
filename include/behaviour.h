//
// Created by Thibaud Lemaire on 23/11/2017.
//

#ifndef OS_ROBOT_BEHAVIOUR_H
#define OS_ROBOT_BEHAVIOUR_H

#include "head.h"

#define BEHAVIOUR_PERIOD 50
#define RED_THRESHOLD 15
#define BLUE_THRESHOLD 5
#define GREEN_THRESHOLD 5
#define PICKUP_CROSS 350    // Travel, in mm, to pickup a movable obstacle
#define DROP_CROSS -400    // Travel, in mm, to drop a movable obstacle
#define WAIT_FOR_COLOR 500  // Time to wait for color measure in ms
#define AVOID_ANGLE     60  // in deg
#define GO_STRAIGHT_ANGLE 20    // Angle to put the robot in front of the movable object if it is on a side

//Enum
enum globalState {
        INITIALIZING,
        WAITING_FOR_START,
        START_RECEIVED,
        CROSSING_ARENA,
        STOP_RECEIVED,
        BUILDING_MAP,
        SENDING_MAP,
        KICKED,
};

enum specificState {
        NORMAL,
        NON_MOVABLE_OBSTACLE_DETECTED_LEFT,
        NON_MOVABLE_OBSTACLE_DETECTED_FRONT,
        NON_MOVABLE_OBSTACLE_DETECTED_RIGHT,
        MOVABLE_OBSTACLE_DETECTED,
        PICKING_UP_OBSTACLE,
        RELEASING_OBSTACLE,
};

extern enum globalState robot_state;            // Robot state
extern enum specificState specif_state;         // Secondary state

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
void cross_arena(void);
void pickup_obstacle();
void drop_object();
void resume();

void search_wall(void);
void follow_wall(void);
void explore_arena(void);

#endif //OS_ROBOT_BEHAVIOUR_H
