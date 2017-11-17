//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_ROTATION_H
#define OS_ROBOT_ROTATION_H

enum {
    ROTATION_ANGLE,
    ROTATION_SPEED,
};

int init_rotation( void );
void *rotation_main(void *arg);

#endif //OS_ROBOT_ROTATION_H
