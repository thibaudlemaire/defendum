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

typedef struct {
    position_t set[MAX_PERIMETER];
    int len ;
}point_cluster;


void init_map_small_arena(map map);
char get_Object(map map,position_t point);
void set_Object(map map,position_t point, char objectType);
void init_map_random(map map);
point_cluster get_points_of_a_type(map map, char objectType);


#endif //OS_ROBOT_MAP_H
