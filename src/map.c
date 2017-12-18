//
// Created by Thibaud Lemaire on 23/11/2017.
//


#include "map.h"
#include "main.h"
#include "bluetooth.h"


#define max(x,y) ((x) >= (y)) ? (x) : (y)
#define min(x,y) ((x) <= (y)) ? (x) : (y)

const coordinates_t start_coordinates = {START_COORD_X, START_COORD_Y};
map_t map;

void init_map_random()
{
    int i;
    int j;

    for ( i = 0; i < map.width; ++i) {
        for ( j = 0; j < map.height ; ++j) {
            map.tab[i][j]= 'U';
        }
    }
}

void init_map_small_arena()
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

void set_Object(position_t position, char objectType)
{
    coordinates_t coordinates = position_to_coordinates(position);
    map.tab[coordinates.x][coordinates.y] = objectType;
}

char get_Object(position_t position)
{
    coordinates_t coordinates = position_to_coordinates(position);
    return (char) map.tab[coordinates.x][coordinates.y];
}

point_cluster get_points_of_a_type(char objectType)
{
    int i;
    int j;
    coordinates_t coordinates;
    point_cluster list_of_point;
    list_of_point.len = 0;

    for ( i = 0; i < map.width ; ++i)
    {
        for ( j = 0; j < map.height ; ++j)
        {
            if (map.tab[i][j] == objectType)
            {

                coordinates.x = i;
                coordinates.y = j;
                list_of_point.set[list_of_point.len] = coordinates;
                list_of_point.len ++;
            }

        }

    }
    return list_of_point;
}



void send_map()
{
    coordinates_t coordinates;
    int i;
    int j;

    for ( i = 0; i < map.width ; ++i)
    {
        for ( j = 0; j < map.height ; ++j)
        {
            coordinates.x = i;
            coordinates.y = j;

            switch (map.tab[i][j])
            {
                case 'U':                           //Unknown
                    bt_send_map_point(coordinates,(char) 255,(char) 255,(char) 255);
                case 'E':                           //Empty
                    bt_send_map_point(coordinates,(char) 240,(char) 255,(char) 240);
                case 'W':                           //Wall
                    bt_send_map_point(coordinates,(char) 0,(char) 0,(char) 0);
                case 'M':                           //Movable
                    bt_send_map_point(coordinates,(char) 70,(char) 130,(char) 180);
                case 'N':                           //Non movable
                    bt_send_map_point(coordinates,(char) 250,(char) 128,(char) 114);
            }
        }
    }
}

position_t coordinates_to_position(coordinates_t coordinates) {
    position_t position;
    position.x = (coordinates.x - start_coordinates.x) * 50;
    position.y = (coordinates.y - start_coordinates.y) * 50;
    return position;
}

coordinates_t position_to_coordinates(position_t position) {
    coordinates_t coordinates;
    coordinates.x = (position.x / 50) + start_coordinates.x;
    coordinates.y = (position.y / 50) + start_coordinates.y;
    return coordinates;
}






