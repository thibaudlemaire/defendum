//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include "map.h"
#include "../include/main.h"
#include "../include/display.h"

#define max(x,y) ((x) >= (y)) ? (x) : (y)
#define min(x,y) ((x) <= (y)) ? (x) : (y)


// WE CONSIDER THE MAP AS A MATRIX WITH ORIGIN IN THE TOP LEFT CORNER
const int MAP_WIDTH;
const int MAP_HEIGHT;
char map[MAP_WIDTH][MAP_HEIGHT];


void init_map()
{
    for (int i = 0; i < MAP_WIDTH; ++i) {
        for (int j = 0; j < MAP_HEIGHT; map[i][j]= "E"); //we initialize the map with empty spots E

    }
}

void set_object(int position[2], char objectType) {
    int i = position[0];
    int j = position[1];
    if (!(0 <= i < MAP_WIDTH) || !(0 <= j < MAP_HEIGHT)) //Test if we were given a position belonging to our map
    {
        print_console("the position doesn't belong to the map");
    }

    switch (objectType) {
        case 'E':
            map[i][j] = objectType;
        case 'W':
            map[i][j] = objectType;
        case 'S':
            map[i][j] = objectType;
        case 'M':
            map[i][j] = objectType;
    }
}




//INTERPOLATION

typedef struct {
    position_t set[];
    int nbPoint;
} set;

set CleanSet(set setOfPoints) //remove equal points
{

}


position_t findMinYPoint(set setOfPoints)
{
    int i = 0;
    position_t minPoint = setOfPoints.set[i];
    for (int j = 1; j <setOfPoints.nbPoint ; ++j) {
        position_t point = setOfPoints.set[j];
        if(point.y< minPoint.y)
        {
            minPoint = point;
        }
    }


    return minPoint;
}

set removePoint(set setOfPoints, position_t point)
{
    int i = 0;
    for (int j = 0; j <setOfPoints.nbPoint ; ++j) {
        position_t setPoint = setOfPoints.set[j];
        if(point.x == setPoint.x && point.y == setPoint.y)
        {
            setOfPoints.set[j]=setOfPoints.set[setOfPoints.nbPoint-1];
            setOfPoints.nbPoint--;

        }
    }
    return setOfPoints;
}

double distance(position_t u,position_t v)

{
    position_t vect;
    vect.x = u.x - v.x;
    vect.y = u.y - v.y;
    double distance = sqrt(vect.x^2 + vect.y^2);
    return  distance;
}

set nearestPoints(set setOfPoints,position_t currentPoint,int k)
{

}


set sortByAngle(set kNearestPoints,position_t currentPoint,double previousAngle)
{

}

set concaveHull(set pointsList, int k_neighnour) // the idea is to adapt the Jarvis method to the k closest neighbours to obtain the best concave hull represantative of the space
{
    int k = max(k_neighnour,3);
    set setOfPoints = CleanSet(pointsList);
    if( setOfPoints.nbPoint<3)
    {
        return null ;
    }

    if (setOfPoints.nbPoint==3)
    {
        return setOfPoints;
    }

    k = min(k,setOfPoints.nbPoint-1);
    position_t firstPoint = findMinYPoint(setOfPoints);
    set hull;
    hull.set[0] = firstPoint;
    position_t currentPoint = firstPoint;
    setOfPoints = removePoint(setOfPoints, firstPoint);
    double previousAngle = 0;
    int step =2;

    while ((!(currentPoint.x==firstPoint.x && currentPoint.y==firstPoint.y) || step==2)&&(setOfPoints.nbPoint>0))
    {
        if (step==5)
        {
            setOfPoints.set[setOfPoints.nbPoint]=firstPoint;
            setOfPoints.nbPoint++;
        }
        set kNearestPoints=nearestPoints(setOfPoints,currentPoint,k);
        set cPoints = sortByAngle(kNearestPoints,currentPoint,previousAngle);
        bool  its = true ;
        int i = 0;
        while (its == true && i < cPoints.nbPoint)
        {
            i++;
            int lastPoint = 0;
            if (cPoints.set[i].x == firstPoint.x && cPoints.set[i].y == firstPoint.y)
            {
                lastPoint = 1;
            }
            int j = 2;
            its = false;
            while ( its == false && j< hull.nbPoint-lastPoint)
            {
                its = intersectQ({hull.set[step-1],cPoints.set[i]}, {hull.set[step-1-j],hull.set[step-j]});
                j++;
            }

        }
        if (its)
        {
            return concaveHull(setOfPoints,k+1);
        }
        currentPoint =cPoints.set[i];
        hull.set[hull.nbPoint]= currentPoint;
        hull.nbPoint++;
        previousAngle = angle(hull.set[step],hull.set[step-1]);
        setOfPoints = removePoint(setOfPoints, currentPoint);
        step++;

    }
    bool allInside =true;
    while( allInside == true && setOfPoints.nbPoint>0 ) {
        allInside = pointInPolygonQ(setOfPoints.set[setOfPoints.nbPoint - 1], hull);
        setOfPoints.nbPoint--;
    }
    if (allInside == false)
    {
        return concaveHull(pointsList, k+1);
    }
    return  hull;







}


