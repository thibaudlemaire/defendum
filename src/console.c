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
                        command = STOP;
                        sleep_ms(100);
                        alive = 0;
                        break;
                /* Stop */
                case ' ':
                        command = STOP;
                        break;
                /* Forward */
                case KEY_UP:
                        command = FORTH;
                        break;
                /* Backward */
                case KEY_DOWN:
                        command = BACK;
                        break;
                /* Left */
                case KEY_LEFT:
                        command = LEFT;
                        break;
                /* Right */
                case KEY_RIGHT:
                        command = RIGHT;
                        break;
                }
        }
        pthread_exit(NULL);
}
