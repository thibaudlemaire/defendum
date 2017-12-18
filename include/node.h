//
// Created by Thibaud Lemaire on 17/12/2017.
//

#ifndef OS_ROBOT_NODE_H
#define OS_ROBOT_NODE_H

#define MOTOR_NODE      OUTD
#define NODE_FLOOR_OFFSET   20
#define NODE_SPEED      1000
#define NODE_RANGE      80
#define NODE_PERIOD     50

int init_node( void );
void reset_node();
void node_up();
void node_down();

#endif //OS_ROBOT_NODE_H
