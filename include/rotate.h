//
// Created by Thibaud Lemaire on 17/12/2017.
//

#ifndef OS_ROBOT_ROTATE_H
#define OS_ROBOT_ROTATE_H

#define MOTOR_ROTATE      OUTD
#define ROTATE_SPEED      500
#define ROTATE_PERIOD     50

int init_rotate( void );
void reset_rotate();
void rotate_left();
void rotate_front();
void rotate_right();


#endif //OS_ROBOT_ROTATE_H
