//
// Created by Thibaud Lemaire on 23/11/2017.
//

#ifndef OS_ROBOT_BEHAVIOUR_H
#define OS_ROBOT_BEHAVIOUR_H


void *behaviour_main(void *arg);
void cross_arena(void);
void search_wall(void);
void follow_wall(void);
void explore_arena(void);
void dodge_obstacle(void);
void random_dodge_obstacle(void);
void catch_movable_obj(void);

#endif //OS_ROBOT_BEHAVIOUR_H
