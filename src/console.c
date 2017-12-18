//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <pthread.h>
#include <ncurses.h>
#include <curses.h>
#include "console.h"
#include "brick.h"
#include "main.h"
#include "display.h"
#include "bluetooth.h"
#include "motors.h"

/**
 * Function used to init the console module
 * @return
 */
int init_console( void )
{
        print_console( "Use directional keys to move, space to stop or q to quit");
        return ( 1 );
}

/**
 * Main function of the console thread, decode what the user is typing
 * @param arg
 * @return
 */
void *console_main(void *arg)
{
        int pressed;
        while (alive)
        {
                pressed = getch();
                move(LINES - 1, COLS - 1);
                switch (pressed) {
                /* Quit */
                case 'q':
                        motors_stop();
                        bluetooth_close();
                        alive = 0;
                        break;
                /* Stop */
                case ' ':
                        motors_stop();
                        break;
                /* Forward */
                case KEY_UP:
                        motors_forward(SPEED_TWO);
                        break;
                /* Backward */
                case KEY_DOWN:
                        motors_backward(SPEED_TWO);
                        break;
                /* Left */
                case KEY_LEFT:
                        motors_rotate_left(90);
                        break;
                /* Right */
                case KEY_RIGHT:
                        motors_rotate_right(90);
                        break;
                }
        }
        pthread_exit(NULL);
}
