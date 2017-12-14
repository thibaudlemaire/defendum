//
// Created by Thibaud Lemaire on 23/11/2017.
//

#ifndef OS_ROBOT_BEHAVIOUR_H
#define OS_ROBOT_BEHAVIOUR_H

//Enum
/*enum globalState {
        INITIALIZING,
        WAITING_FOR_START,
        CROSSING_ARENA,
        BUILDING_MAP,
        SENDING_MAP,
        FINISH,
        KICKED,
};*/

/*enum crossingArenaState {
        SEARCHING_WALL,
        FOLLOWING_WALL,
        EXPLORING_ARENA
};

extern enum crossingArenaState crossing_state;
*/

void *behaviour_main(void *arg);
void cross_arena(void);
void search_wall(void);
void follow_wall(void);
void explore_arena(void);
void dodge_obstacle(void);
void random_dodge_obstacle(void);

#endif //OS_ROBOT_BEHAVIOUR_H
