//
// Created by Thibaud Lemaire on 17/12/2017.
//

#ifndef OS_ROBOT_ROTATE_H
#define OS_ROBOT_ROTATE_H

#define MOTOR_ROTATE      OUTD
#define ROTATE_SPEED      300
#define ROTATE_PERIOD     50
#define POSITION_INIT     1000

typedef enum  {
    ROTATE_LEFT_POSITION,
    ROTATE_FRONT_POSITION,
    ROTATE_RIGHT_POSITION,
}rotate_pos_t;

int init_rotate( void );
void reset_rotate();
void rotate_left();
void rotate_front();
void rotate_right();
rotate_pos_t get_current_rotate_position();


#endif //OS_ROBOT_ROTATE_H
