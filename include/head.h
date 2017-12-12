#ifndef OS_ROBOT_HEAD_H
#define OS_ROBOT_HEAD_H

#define COLOR_PERIOD    50  // Color measure period in ms
#define DISTANCE_CM_MODE 0 // Don't change this
#define DISTANCE_PERIOD 50  // Distance measure period in ms
#define MOTOR_NODE      OUTD
#define MOTOR_ROTATE    OUTA
enum {
        RED_COLOR,
        GREEN_COLOR,
        BLUE_COLOR,
};

int init_head( void );
void *head_main(void *arg);
void color_update(void);
void distance_update(void);

#endif //OS_ROBOT_HEAD_H
