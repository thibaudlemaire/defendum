//
// Created by Thibaud Lemaire on 23/11/2017.
//

#ifndef OS_ROBOT_BEHAVIOUR_H
#define OS_ROBOT_BEHAVIOUR_H

#define BEHAVIOUR_PERIOD 50

#define CLEAR_THRESHOLD 1000
#define NEAR_THRESHOLD 300
#define STOP_THRESHOLD 150

//Enum
enum globalState {
        INITIALIZING,
        WAITING_FOR_START,
        START_RECEIVED,
        CROSSING_ARENA,
        BUILDING_MAP,
        SENDING_MAP,
        FINISH,
        KICKED,
};

enum specificState {
        NON_MOVABLE_OBSTACLE_FOUND,
        MOVABLE_OBSTACLE_FOUND,
        OBSTACLE_PICKED_UP,
};

extern enum globalState robot_state;            // Robot state
extern enum specificState specif_state;         // Secondary state

void *behaviour_main(void *arg);
int wait_for(enum globalState condition);
void start_received();
void stop_received();
void kicked();
void obstacle_found();
void cross_arena(void);
void search_wall(void);
void follow_wall(void);
void explore_arena(void);

#endif //OS_ROBOT_BEHAVIOUR_H
