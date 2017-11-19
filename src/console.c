//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <pthread.h>
#include <ncurses.h>
#include "console.h"
#include "main.h"
#include "display.h"

int init_console( void )
{
    print_console( "Available commands :");
    print_console( "q : quitter");
    print_console( "a : avancer");
    print_console( "r : reculer");
    print_console( "g : gauche");
    print_console( "d : droite");
    print_console( "s : stop");
    return ( 1 );
}

/* Console handling thread */
void *console_main(void *arg)
    {
        char pressed;
        while (alive)
        {
            pressed = getch();
            move(LINES - 1, COLS - 1);
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
        }
        pthread_exit(NULL);
    }
