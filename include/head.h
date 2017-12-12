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
void rotate_head(void);
void look_left(void);
void look_front(void);
void look_right(void);
void head_up(void);
void head_down(void);
void examine(void);
int obtacle(void);

#endif //OS_ROBOT_HEAD_H
