//
// Created by Thibaud Lemaire on 17/12/2017.
//

#ifndef OS_ROBOT_NODE_H
#define OS_ROBOT_NODE_H

#define MOTOR_NODE      OUTA
#define NODE_SPEED      1000
#define NODE_RANGE      1100
#define NODE_PERIOD     50

int init_node( void );
void reset_node();
void node_up();
void node_down();
void node_reset();

#endif //OS_ROBOT_NODE_H
