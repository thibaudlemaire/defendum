//
// Created by Thibaud Lemaire on 18/11/2017.
//

#include <pthread.h>
#include <stdlib.h>
#include <ncurses.h>
#include "brick.h"
#include "display.h"
#include "main.h"

WINDOW *top_window, *bottom_window;

int init_display( void )
{
    initscr();

    top_window = subwin(stdscr, 6, COLS, 0, 0);
    bottom_window = subwin(stdscr, LINES - 7, COLS, 6, 0);

    box(top_window, ACS_VLINE, ACS_HLINE);
    box(bottom_window, ACS_VLINE, ACS_HLINE);

    mvwprintw(top_window, 1, 2, "Color red : ");
    mvwprintw(top_window, 2, 2, "Color green : ");
    mvwprintw(top_window, 3, 2, "Color blue : ");
    mvwprintw(top_window, 4, 2, "Heading : ");

    mvwprintw(top_window, 1, COLS / 2, "Angle : ");
    mvwprintw(top_window, 2, COLS / 2, "Rot speed : ");
    mvwprintw(top_window, 3, COLS / 2, "Distance : ");

    wattron(bottom_window, A_REVERSE);
    mvwprintw(bottom_window, 1, 2, "Console :");
    wattroff(bottom_window, A_REVERSE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    wrefresh(top_window);
    wrefresh(bottom_window);

    move(LINES - 1, COLS - 1);

    return ( 1 );
}

void uninit_display( void )
{
    getch();
    endwin();
}

/*
 * Function to write in the bottom window
 */
void print_console(char * message)
{
    mvwprintw(bottom_window, getcury(bottom_window)+1, 2, message);
    wrefresh(bottom_window);
    wrefresh(top_window);
}

/*
 * Function to write in the bottom window
 */
void print_error(char * message)
{
    wattron(bottom_window, COLOR_PAIR(1));
    mvwprintw(bottom_window, getcury(bottom_window)+1, 2, message);
    wrefresh(bottom_window);
    wrefresh(top_window);
    wattroff(bottom_window, COLOR_PAIR(1));
}

/*
 * Display handling thread
 */
void *display_main(void *arg)
{
    sleep_ms(1000);  // Waiting for screen to be ready
    while (alive)
    {
        mvwprintw(top_window, 1, 16, "%u    ", color_red);
        mvwprintw(top_window, 2, 16, "%u    ", color_green);
        mvwprintw(top_window, 3, 16, "%u    ", color_blue);
        mvwprintw(top_window, 4, 16, "%u deg   ", compass_heading);

        mvwprintw(top_window, 1, COLS / 2 + 13, "%d deg     ", rotation_angle );
        mvwprintw(top_window, 2, COLS / 2 + 13, "%d deg/s    ", rotation_rspeed);
        mvwprintw(top_window, 3, COLS / 2 + 13, "%u mm    ", distance_value);

        wrefresh(top_window);
        wrefresh(bottom_window);

        sleep_ms(DISPLAY_PERIOD);
    }

    pthread_exit(NULL);
}
