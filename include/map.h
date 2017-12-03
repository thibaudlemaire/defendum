//
// Created by Thibaud Lemaire on 23/11/2017.
//


#ifndef OS_ROBOT_MAP_H
#define OS_ROBOT_MAP_H

#define MAP_WIDTH 24;
#define MAP_HEIGHT 40;

typedef struct {
    char tab[MAX_WIDTH][MAX_HEIGHT];
    int width;
    int height;

} map;



void init_map(map map);
char get_Object(map map,position_t point);
void set_object(map map,position_t point, char objectType);



#endif //OS_ROBOT_MAP_H
