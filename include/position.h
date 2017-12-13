//
// Created by Thibaud Lemaire on 23/11/2017.
//

#ifndef OS_ROBOT_POSITION_H
#define OS_ROBOT_POSITION_H

#define POSITION_PERIOD   100 // sleep time in ms
#define WHEEL_RADIUS      20 // wheel radius in mm
#define X_OFFSET          1200 // X offset in mm
#define Y_OFFSET          0 // Y offset in mm

int init_position( void );
void *position_main(void *arg);
int update_postion( int state );
void initialize_position( void );
position_t add_offset(position_t point);

extern position_t current_position;

#endif //OS_ROBOT_POSITION_H
