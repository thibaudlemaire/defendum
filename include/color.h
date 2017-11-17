//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_COLOR_H
#define OS_ROBOT_COLOR_H

enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
};

int init_color( void );
void *color_main(void *arg);

#endif //OS_ROBOT_COLOR_H
