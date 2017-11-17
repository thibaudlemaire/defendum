//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include "console.h"
#include "coroutine.h"
#include "brick.h"
#include "main.h"

int init_console( void )
{
    printf( "Available commands :\n"
            "q : quitter\n"
            "a : avancer\n"
            "r : reculer\n"
            "g : gauche\n"
            "d : droite\n"
            "s : stop\n"
    );
    return ( 1 );
}

/* Coroutine of the console key handling */
CORO_DEFINE( handle_brick_control )
    {
        CORO_LOCAL char pressed;
        CORO_LOCAL struct pollfd pollEvent;
        CORO_LOCAL int result = -1;
        CORO_BEGIN();
        for ( ; ; ) {
            // Poll event init on stdin
            pollEvent.fd = STDIN_FILENO;
            pollEvent.events = POLLIN;

            // Polling : is there char in stdin ?
            result = poll(&pollEvent, 1, TIMEOUT);

            // Processing
            if(result < 0) {
                printf("Erreur poll() !");
            } else if(result == 0) { // Timeout
                CORO_YIELD();
            } else {
                (void) read(pollEvent.fd, &pressed, 1); // Clearing pollEvent and move data into 'pressed'
                switch (pressed) {
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
        }
        CORO_END();
    }
