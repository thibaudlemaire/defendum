//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include <tkDecls.h>
#include "map.h"
#include "main.h"
#include "display.h"
#include "../include/main.h"

#define max(x,y) ((x) >= (y)) ? (x) : (y)
#define min(x,y) ((x) <= (y)) ? (x) : (y)


// WE CONSIDER THE MAP AS A MATRIX WITH ORIGIN IN THE TOP LEFT CORNER

typedef struct {
    char tab[MAX_WIDTH][MAX_HEIGHT];
    int width;
    int height;

} map;

typedef struct {
    position_t set[MAX_PERIMETER];
    int len ;
}point_cluster;


void init_map_random(map map)
{
    for (int i = 0; i < map.width; ++i) {
        for (int j = 0; j < map.height ; ++j) {

            map.tab[i][j]= 'E';
        }
    }
}

void init_map_small_arena(map map)
{
    map.height = 40;
    map.width = 24;
    for (int i = 0; i < map.height ; ++i)
    {
        map.tab[0][i] = 'W';
        map.tab[map.width-1][i]='W';
    }
    for (int j = 0; j < map.width ; ++j)
    {
        map.tab[j][0] = 'W';
        map.tab[j][map.height-1]='W';
    }
}

void set_Object(map map,position_t point, char objectType)
{

    map.tab[point.x][point.y] = objectType;

}

char get_Object(map map,position_t point)
{
    return map.tab[point.x][point.y];
}

point_cluster get_points_of_a_type(map map, char objectType)
{
    point_cluster list_of_point;
    list_of_point.len = 0;
    for (int i = 0; i < map.width ; ++i)
    {
        for (int j = 0; j < map.height ; ++j)
        {
            if (map.tab[i][j] = objectType)
            {
                position_t p;
                p.x = i;
                p.y = j;
                list_of_point[list_of_point.len] = p;
                list_of_point.len ++;
            }

        }

    }
    return list_of_point;
}







