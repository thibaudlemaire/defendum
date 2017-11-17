//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <stdio.h>
#include "console.h"
#include "coroutine.h"
#include "brick.h"
#include "main.h"

/* Coroutine of the console key handling */
CORO_DEFINE( handle_brick_control )
    {
        CORO_LOCAL char pressed;
        CORO_BEGIN();
        for ( ; ; ) {
            /* Waiting any brick's key is pressed or released */
            CORO_WAIT(scanf("%c", &pressed));
            switch ( pressed ) {
                /* Quit */
                case 'q':
                    command = STOP;
                    alive = 0;
                    break;
                    /* Stop */
                case 's':
                    command = STOP;
                    break;
                    /* Forward */
                case 'a':
                    command = FORTH;
                    break;
                    /* Backward */
                case 'r':
                    command = BACK;
                    break;
                    /* Left */
                case 'g':
                    command = LEFT;
                    break;
                    /* Right */
                case 'd':
                    command = RIGHT;
                    break;
            }
            CORO_YIELD();
        }
        CORO_END();
    }
