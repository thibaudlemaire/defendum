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


void init_map(map map)
{
    for (int i = 0; i < map.width; ++i) {
        for (int j = 0; j < map.height ; ++j) {

            map.tab[i][j]=(char)"E";
        }
    }
}

void set_object(map map,position_t point, char objectType)
{

    map.tab[point.x][point.y] = objectType;

}

char get_Object(map map,position_t point)
{
    return map.tab[point.x][point.y];
}





//INTERPOLATION




