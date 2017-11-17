//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_MOTORS_H
#define OS_ROBOT_MOTORS_H

#define MOTOR_LEFT     OUTC
#define MOTOR_RIGHT    OUTB
#define MOTOR_BOTH     ( MOTOR_LEFT | MOTOR_RIGHT )

int init_motors( void );
void *motors_main(void *arg);

#endif //OS_ROBOT_MOTORS_H
