#ifndef OS_ROBOT_HEAD_H
#define OS_ROBOT_HEAD_H

#define WALL_DISTANCE   300 //in mm
#define HEAD_PERIOD     50

enum enumobstacle {
        NO_OBS,
        LEFT_OBS,
        FRONT_OBS,
        RIGHT_OBS,
};

enum crosstate {
        SEARCHING_WALL,
        FOLLOWING_WALL,
        EXPLORING_ARENA,
};

extern enum enumobstacle obstacle_flag;
extern enum crosstate crossing_state;

int init_head( void );
void *head_main(void *arg);
void rotate_head(void);
void look_left(void);
void look_front(void);
void look_right(void);
void head_up(void);
void head_down(void);
void examine(void);
int obstacle(void);
void searching_wall_head(void);
void following_wall_head(void);
void exploring_arena_head(void);

#endif //OS_ROBOT_HEAD_H
