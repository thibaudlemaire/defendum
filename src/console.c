//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <stdio.h>
#include <pthread.h>
#include "console.h"
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

/* Console handling thread */
void *console_main(void *arg)
    {
        char pressed;
        while (alive)
        {
            scanf("%c", &pressed);
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
        printf("Exit console\n");
        pthread_exit(NULL);
    }
