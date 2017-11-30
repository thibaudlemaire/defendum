//
// Created by Thibaud Lemaire on 18/11/2017.
//

#include <pthread.h>
#include <stdlib.h>
#include <ncurses.h>
#include "brick.h"
#include "display.h"
#include "main.h"
#include "position.h"

WINDOW *top_window, *bottom_window; // ncurses windows

/**
 * Function called to init display module
 * Init screen and draw it
 * @return
 */
int init_display( void )
{
    pthread_mutex_lock(&stdout_mutex); // Lock shared resources

    initscr();

    keypad(stdscr, TRUE);   // Activate keypad to listen for directional commands

    top_window = subwin(stdscr, 6, COLS, 0, 0);
    bottom_window = subwin(stdscr, LINES - 7, COLS, 6, 0);

    box(top_window, ACS_VLINE, ACS_HLINE);          // Draw boxes
    box(bottom_window, ACS_VLINE, ACS_HLINE);

    mvwprintw(top_window, 1, 2, "Color red : ");
    mvwprintw(top_window, 2, 2, "Color green : ");
    mvwprintw(top_window, 3, 2, "Color blue : ");
    mvwprintw(top_window, 4, 2, "Heading : ");

    mvwprintw(top_window, 1, COLS / 2, "Angle : ");
    mvwprintw(top_window, 2, COLS / 2, "Rot speed : ");
    mvwprintw(top_window, 3, COLS / 2, "Distance : ");
    mvwprintw(top_window, 4, COLS / 2, "Position : ");

    wattron(bottom_window, A_REVERSE);
    mvwprintw(bottom_window, 1, 2, "Console :");
    wattroff(bottom_window, A_REVERSE);

    start_color();                                  // Activate colors
    init_pair(1, COLOR_RED, COLOR_BLACK);           // Define an attribute for errors

    wrefresh(top_window);
    wrefresh(bottom_window);

    move(LINES - 1, COLS - 1);                      // Put the cursor on the right-bottom corner

    pthread_mutex_unlock(&stdout_mutex); // Unlock shared resources

    return ( 1 );
}

/**
 * Function called to release screen
 */
void uninit_display( void )
{
    pthread_mutex_lock(&stdout_mutex); // Lock shared resources
    print_console("Quitting... press a key to exit");
    getch();
    endwin();
    pthread_mutex_unlock(&stdout_mutex); // Unlock shared resources
}

/**
 * Function to write in the bottom window
 */
void print_console(char * message)
{
    pthread_mutex_lock(&stdout_mutex); // Lock shared resources
    int current_y = getcury(bottom_window) + 1;
    if (current_y >= LINES - 8)
        current_y = 2;
    mvwprintw(bottom_window, current_y, 2, message);
    wrefresh(bottom_window);
    wrefresh(top_window);
    pthread_mutex_unlock(&stdout_mutex); // Unlock shared resources
}

/**
 * Function to write errors in red in the bottom window
 */
void print_error(char * message)
{
    pthread_mutex_lock(&stdout_mutex); // Lock shared resources
    int current_y = getcury(bottom_window) + 1;
    if (current_y >= LINES - 8)
        current_y = 2;
    wattron(bottom_window, COLOR_PAIR(1));
    mvwprintw(bottom_window, current_y, 2, message);
    wrefresh(bottom_window);
    wrefresh(top_window);
    wattroff(bottom_window, COLOR_PAIR(1));
    pthread_mutex_unlock(&stdout_mutex); // Unlock shared resources
}

/**
 * Main function of the thread
 * @param arg
 * @return a generic pointer used by pthread
 */
void *display_main(void *arg)
{
    sleep_ms(1000);  // Waiting for screen to be ready !!
    while (alive)
    {
        pthread_mutex_lock(&stdout_mutex); // Lock shared resources
        mvwprintw(top_window, 1, 16, "%u    ", color_red);
        mvwprintw(top_window, 2, 16, "%u    ", color_green);
        mvwprintw(top_window, 3, 16, "%u    ", color_blue);
        mvwprintw(top_window, 4, 16, "%u deg   ", compass_heading);

        mvwprintw(top_window, 1, COLS / 2 + 13, "%d deg     ", rotation_angle );
        mvwprintw(top_window, 2, COLS / 2 + 13, "%d deg/s    ", rotation_rspeed);
        mvwprintw(top_window, 3, COLS / 2 + 13, "%u mm    ", distance_value);
        mvwprintw(top_window, 4, COLS / 2 + 13, "%d;%d    ", current_position.x,current_position.y);

        wrefresh(top_window);
        wrefresh(bottom_window);
        pthread_mutex_unlock(&stdout_mutex); // Unlock shared resources

        sleep_ms(DISPLAY_PERIOD);
    }

    pthread_exit(NULL);
}
