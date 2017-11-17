//
// Created by Thibaud Lemaire on 16/11/2017.
//

#ifndef OS_ROBOT_MAIN_H
#define OS_ROBOT_MAIN_H

// Parameters
#define SPEED_LINEAR    75  /* Motor speed for linear motion, in percents */
#define SPEED_CIRCULAR  15  /* ... for circular motion */

#define COLOR_PERIOD    50  // Color measure period in ms
#define DISTANCE_PERIOD 50  // Distance measure period in ms
#define MOTORS_PERIOD   50  // Motors update period in ms
#define ROTATION_PERIOD 50  // Rotation measure period in ms
#define COMPASS_PERIOD  50  // Compass measure period in ms

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
extern int max_speed;           /* Motor maximal speed (will be detected) */

// Proto
int init( void );

#endif //OS_ROBOT_MAIN_H
