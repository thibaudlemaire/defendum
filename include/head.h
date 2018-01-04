#ifndef OS_ROBOT_HEAD_H
#define OS_ROBOT_HEAD_H

#define WALL_DISTANCE   300 //in mm
#define HEAD_PERIOD     50

#define CLEAR_THRESHOLD 500
#define NEAR_THRESHOLD 200
#define STOP_THRESHOLD 70

enum enumobstacle {
        NO_OBS,
        NEAR_OBS,
        REALLY_NEAR_OBS,
        LEFT_OBS,
        FRONT_OBS,
        RIGHT_OBS,
};

typedef enum enumobstacle obstacle_t;

enum crosstate {
        SEARCHING_WALL,
        FOLLOWING_WALL,
        EXPLORING_ARENA,
};

enum headState {
    HEAD_MOVING,
    HEAD_HOLD
};

enum headMoveState {
    HEAD_LEFT,
    HEAD_FRONT_TO_RIGHT,
    HEAD_RIGHT,
    HEAD_FRONT_TO_LEFT,
};

extern enum enumobstacle obstacle_flag;
extern enum crosstate crossing_state;
extern enum headState head_state;
extern enum headMoveState head_move_state;

int init_head( void );
void *head_main(void *arg);
obstacle_t get_obstacle();
void head_measure();
void head_move_and_measure();
void look_left(void);
void look_front(void);
void look_right(void);
void head_up(void);
void head_down(void);
void head_move();
void head_stop();
void head_reset();


#endif //OS_ROBOT_HEAD_H
