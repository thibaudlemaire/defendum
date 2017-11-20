//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_DISTANCE_H
#define OS_ROBOT_DISTANCE_H

#define DISTANCE_CM_MODE 0 // Don't change this

#define DISTANCE_PERIOD 50  // Distance measure period in ms

int init_distance( void );
void *distance_main(void *arg);

#endif //OS_ROBOT_DISTANCE_H
