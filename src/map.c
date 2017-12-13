//
// Created by Thibaud Lemaire on 23/11/2017.
//


#include "map.h"
#include "main.h"
#include "display.h"
#include "bluetooth.h"


#define max(x,y) ((x) >= (y)) ? (x) : (y)
#define min(x,y) ((x) <= (y)) ? (x) : (y)

int i;
int j;






void init_map_random(map map)
{
    int i;
    int j;

    for ( i = 0; i < map.width; ++i) {
        for ( j = 0; j < map.height ; ++j) {
            map.tab[i][j]= 'U';
        }
    }
}

void init_map_small_arena(map map)
{

    int i;
    int j;

    map.height = 40;
    map.width = 24;

    for ( i = 1; i < map.width-1; ++i) {
        for ( j = 1; j < map.height-1 ; ++j) {
            map.tab[i][j]= 'U';
        }
    }

    for ( i = 0; i < map.height ; ++i)
    {
        map.tab[0][i] = 'W';
        map.tab[map.width-1][i]='W';
    }
    for ( j = 0; j < map.width ; ++j)
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
    return (char) map.tab[point.x][point.y];
}

point_cluster get_points_of_a_type(map map, char objectType)
{
    int i;
    int j;
    position_t p;
    point_cluster list_of_point;
    list_of_point.len = 0;

    for ( i = 0; i < map.width ; ++i)
    {
        for ( j = 0; j < map.height ; ++j)
        {
            if (map.tab[i][j] == objectType)
            {

                p.x = i;
                p.y = j;
                list_of_point.set[list_of_point.len] = p;
                list_of_point.len ++;
            }

        }

    }
    return list_of_point;
}



void send_map(map map)
{
    position_t p;
    int i;
    int j;


    for ( i = 0; i < map.width ; ++i)
    {
        for ( j = 0; j < map.height ; ++j)
        {
            p.x = i;
            p.y = j;

            switch (map.tab[i][j])
            {
                case 'U':                           //Unknown
                    send_map_point(p,(char) 255,(char) 255,(char) 255);
                case 'E':                           //Empty
                    send_map_point(p,(char) 240,(char) 255,(char) 240);
                case 'W':                           //Wall
                    send_map_point(p,(char) 0,(char) 0,(char) 0);
                case 'M':                           //Movable
                    send_map_point(p,(char) 70,(char) 130,(char) 180);
                case 'N':                           //Non movable
                    send_map_point(p,(char) 250,(char) 128,(char) 114);
            }
        }

    }
}






