//
// Created by Thibaud Lemaire on 16/11/2017.
//

#ifndef OS_ROBOT_MAIN_H
#define OS_ROBOT_MAIN_H

// Enum
enum {
    STOP,
    FORTH,
    BACK,
    LEFT,
    RIGHT,
};

// Globals
extern int command;             /* Command for `drive` coroutine */
extern int alive;               /* Program is alive */
extern int color_red,
        color_green,
        color_blue,
        compass_heading,
        distance_value,
        rotation_angle,
        rotation_rspeed;

// Proto
int init( void );

#endif //OS_ROBOT_MAIN_H
