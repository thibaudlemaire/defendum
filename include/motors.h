//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_MOTORS_H
#define OS_ROBOT_MOTORS_H

// Speed
#define SPEED_LINEAR    100  /* Motor speed for linear motion, in percents */
#define SPEED_CIRCULAR  20  /* ... for circular motion */

// Motors config
#define MOTOR_LEFT     OUTC
#define MOTOR_RIGHT    OUTB
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )

// Refresh period
#define MOTORS_PERIOD   50  // Motors update period in ms

int init_motors( void );
void *motors_main(void *arg);

#endif //OS_ROBOT_MOTORS_H
