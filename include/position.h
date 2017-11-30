//
// Created by Thibaud Lemaire on 23/11/2017.
//

#ifndef OS_ROBOT_POSITION_H
#define OS_ROBOT_POSITION_H

#define POSITION_PERIOD   50 // sleep time in ms
#define WHEEL_RADIUS      20 // wheel radius in mm

int init_position( void );
void *position_main(void *arg);
int update_postion( int state );
void initialize_position( void );

extern position_t current_position;

#endif //OS_ROBOT_POSITION_H
