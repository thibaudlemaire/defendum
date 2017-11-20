//
// Created by Thibaud Lemaire on 16/11/2017.
//

#ifndef OS_ROBOT_MAIN_H
#define OS_ROBOT_MAIN_H

// Parameters
#define SPEED_LINEAR    100  /* Motor speed for linear motion, in percents */
#define SPEED_CIRCULAR  100  /* ... for circular motion */

#define DISPLAY_PERIOD  100 // Display refresh period
#define COLOR_PERIOD    50  // Color measure period in ms
#define DISTANCE_PERIOD 50  // Distance measure period in ms
#define MOTORS_PERIOD   50  // Motors update period in ms
#define ROTATION_PERIOD 50  // Rotation measure period in ms
#define COMPASS_PERIOD  50  // Compass measure period in ms

#define TEAM_ID         1   // Team ID for bluetooth communication with server

// Enum
enum {
    STOP,
    FORTH,
    BACK,
    LEFT,
    RIGHT,
};

// Globals
extern int command;             /* Command for `drive` coroutine */
extern int alive;               /* Program is alive */
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
