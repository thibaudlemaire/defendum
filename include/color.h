//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_COLOR_H
#define OS_ROBOT_COLOR_H

enum {
    RED_COLOR,
    GREEN_COLOR,
    BLUE_COLOR,
};

int init_color_sensor( void );
void *color_main(void *arg);

#endif //OS_ROBOT_COLOR_H
