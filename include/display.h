//
// Created by Thibaud Lemaire on 19/11/2017.
//

#ifndef OS_ROBOT_DISPLAY_H
#define OS_ROBOT_DISPLAY_H

#include <ncurses.h>

extern WINDOW *top_window, *bottom_window;

int init_display( void );
void uninit_display( void );
void print_console(char * message);
void print_error(char * message);
void *display_main(void *arg);

#endif //OS_ROBOT_DISPLAY_H
