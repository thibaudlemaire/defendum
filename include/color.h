//
// Created by Thibaud Lemaire on 17/11/2017.
//

#ifndef OS_ROBOT_COLOR_H
#define OS_ROBOT_COLOR_H

enum {
        NONE_COLOR,
        BLACK_COLOR,
        BLUE_COLOR,
        GREEN_COLOR,
        YELLOW_COLOR,
        RED_COLOR,
        WHITE_COLOR,
        BROWN_COLOR,
};

int init_color_sensor();
void color_update();

#endif //OS_ROBOT_COLOR_H
