//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_CONSOLE_H
#define OS_ROBOT_CONSOLE_H

#include "coroutine.h"

CORO_CONTEXT( handle_brick_control );
CORO_DEFINE( handle_brick_control );

#endif //OS_ROBOT_CONSOLE_H
