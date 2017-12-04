//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_MOTORS_H
#define OS_ROBOT_MOTORS_H

//Enum
enum linearSpeed {
      ONE = 20/100 * 1050,
      TWO = 40/100 * 1050,
      THREE = 60/100 * 1050,
      FOR = 80/100 * 1050,
      FIVE = 1050,
};

// Speed
#define SPEED_CIRCULAR  20  /* ... for circular motion */

// Motors config
#define MOTOR_LEFT     OUTC
#define MOTOR_RIGHT    OUTB
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )

// Refresh period
#define MOTORS_PERIOD   50  // Motors update period in ms

int init_motors( void );
void *motors_main(void *arg);
void rotate_left(int angle);
void rotate_right(int angle);
void forward(enum linearSpeed);
void backward(enum linearSpeed);
void stop(void);

//globals
extern enum linearSpeed speed_linear;
extern speed_circular = 1050 * SPEED_CIRCULAR / 100;

#endif //OS_ROBOT_MOTORS_H
