//
// Created by Thibaud Lemaire on 18/11/2017.
//

#ifndef OS_ROBOT_COMPASS_H
#define OS_ROBOT_COMPASS_H

#define COMPASS_DIRECTION_MODE 0 // Don't change this

#define COMPASS_PERIOD  50  // Compass measure period in ms

int init_compass( void );
void *compass_main(void *arg);

#endif //OS_ROBOT_COMPASS_H
