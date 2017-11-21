//
// Created by Thibaud Lemaire on 16/11/2017.
//

#ifndef OS_ROBOT_MAIN_H
#define OS_ROBOT_MAIN_H

// Enum
enum commandState {
    STOP,
    FORTH,
    BACK,
    LEFT,
    RIGHT,
};
enum globalState {
    INITIALIZING,
    WAITING_FOR_START,
    CROSSING_ARENA,
    BUILDING_MAP,
    SENDING_MAP,
    FINISH,
    KICKED,
};

// Types
typedef struct {
    int16_t x;
    int16_t y;
} position_t;

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} color_t;

// Globals
extern enum commandState command;               // Command for `motor` module
extern int alive;                               // Program is alive
extern enum globalState robot_state;            // Robot state
extern int color_red,
        color_green,
        color_blue,
        compass_heading,
        distance_value,
        rotation_angle,
        rotation_rspeed;

// Proto
int init( void );

#endif //OS_ROBOT_MAIN_H
