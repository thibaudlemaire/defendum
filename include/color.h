//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_COLOR_H
#define OS_ROBOT_COLOR_H

#include "coroutine.h"

enum {
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE,
};

CORO_CONTEXT( color );
CORO_DEFINE( color );

int init_color( void );

#endif //OS_ROBOT_COLOR_H
