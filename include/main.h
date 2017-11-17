//
// Created by Thibaud Lemaire on 16/11/2017.
//

#ifndef OS_ROBOT_MAIN_H
#define OS_ROBOT_MAIN_H

// Defines
#define SPEED_LINEAR    75  /* Motor speed for linear motion, in percents */
#define SPEED_CIRCULAR  15  /* ... for circular motion */
#define MOTOR_LEFT     OUTC
#define MOTOR_RIGHT    OUTB
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )

// Enum
enum {
    STOP,
    FORTH,
    BACK,
    LEFT,
    RIGHT,
};

// Globals
extern int command;    /* Command for `drive` coroutine */
extern int alive;             /* Program is alive */
extern int max_speed;         /* Motor maximal speed (will be detected) */

// Proto
int init( void );

#endif //OS_ROBOT_MAIN_H
