//
// Created by Thibaud Lemaire on 16/11/2017.
//

#ifndef OS_ROBOT_MAIN_H
#define OS_ROBOT_MAIN_H

#include <pthread.h>

// Enum
enum commandState {
        STOP,
        FORTH,
        BACK,
        LEFT,
        RIGHT,
};

// Types
typedef struct {
        int x;
        int y;
} position_t;

typedef struct {
        int x;
        int y;
} coordinates_t;

typedef struct {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
} color_t;

// Globals
extern enum commandState command;               // Command for `motor` module
extern int alive;                               // Program is alive

extern int color_red,
           color_green,
           color_blue,
           compass_heading,
           distance_value,
           rotation_angle,
           rotation_rspeed;
extern pthread_mutex_t stdout_mutex;

// Proto
int init( void );

#endif //OS_ROBOT_MAIN_H
