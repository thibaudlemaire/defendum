//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_CONSOLE_H
#define OS_ROBOT_CONSOLE_H

#include "coroutine.h"

#define TIMEOUT 10

CORO_CONTEXT( handle_brick_control );
CORO_DEFINE( handle_brick_control );

int init_console( void );

#endif //OS_ROBOT_CONSOLE_H