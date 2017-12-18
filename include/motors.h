//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_MOTORS_H
#define OS_ROBOT_MOTORS_H

// Enum
enum linearSpeed {
      SPEED_ONE = 50,
      SPEED_TWO = 100,
      SPEED_THREE = 200,
};

// Speed
#define SPEED_CIRCULAR 50

// Motors config
#define MOTOR_LEFT     OUTC
#define MOTOR_RIGHT    OUTB
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )

// Refresh period
#define MOTORS_PERIOD   50  // Motors update period in ms

int init_motors( void );
void motors_rotate_left(int angle);
void motors_rotate_right(int angle);
void motors_forward(enum linearSpeed);
void motors_backward(enum linearSpeed);
void motors_stop(void);
void motors_cross(int distance);

#endif //OS_ROBOT_MOTORS_H
