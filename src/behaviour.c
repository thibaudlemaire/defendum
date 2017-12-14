//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include <pthread.h>
#include <stdlib.h>
#include "behaviour.h"
#include "motors.h"
#include "main.h"
#include "brick.h"
#include "display.h"
#include "touch.h"
#include "head.h"

/*enum globalState robot_state = EXPLORING_ARENA;           // Robot state */
/*enum crossingArenaState crossing_state = SEARCHING_WALL;*/

enum crosstate crossing_state = EXPLORING_ARENA;

void *behaviour_main(void *arg)
{
      //print_console("Behaviour initialized");

      cross_arena();

      pthread_exit(NULL);

}

void cross_arena(void)
{
      switch (crossing_state)
      {
            case SEARCHING_WALL:
                search_wall();
                crossing_state++;
                break;
            case FOLLOWING_WALL:
                follow_wall();
                crossing_state++;
                break;
            case EXPLORING_ARENA:
                explore_arena();
                break;

      }
}

/*fonction qui déplace le robot de son point de départ et le positionne
  parallèle et proche d'un mur,le mur à sa droite*/
void search_wall(void)
{

      // Sleep to let head initialise
      sleep_ms(1000);

      int wall_detected = 0;
      /* first face a wall */
      motors_rotate_right(90);

      while(/*alive &&*/ wall_detected==0)
      {
          sleep_ms(TOUCH_PERIOD);
          motors_forward(TWO);

          if (obstacle_flag == FRONT_OBS)
          {
            wall_detected = 1;
            motors_rotate_left(90);
          }
      }
      return;
}

void follow_wall(void)
{
      while(alive)
      {

          sleep_ms(TOUCH_PERIOD);

          if (obstacle_flag != NO_OBS)
          {
                dodge_obstacle();
          }

          if (touch_is_touched())
          {
              /*set_Object(map,position_t point, 'W');*/
              motors_rotate_left(15);
              motors_forward(TWO);
              sleep_ms(1000);
          }
          else
          {
              motors_rotate_right(13);
              motors_forward(TWO);
              sleep_ms(1000);

          }

      }
      return;
}

/*
* Fonction qui explore le centre de l'arene, une fois que le contour est connu
*
*/
void explore_arena(void)
{
      //TODO : marche aléatoire dans l'arène en prenant en compte l'environnement
      while(alive)
      {
            sleep_ms(MOTORS_PERIOD);
            if (obstacle_flag != NO_OBS)
            {
                  motors_stop();
                  random_dodge_obstacle();
            }
            else
            {
                  motors_forward(ONE);
            }

      }
}

void dodge_obstacle(void)
{
      switch (obstacle_flag)
      {
        case LEFT_OBS:
              motors_rotate_right(15);
              break;
        case FRONT_OBS:
              motors_rotate_left(30);
              break;
        case RIGHT_OBS:
              motors_rotate_left(15);
              break;
        case NO_OBS:
              break;
      }
      return;
}

void random_dodge_obstacle(void)
{
      //TODO : éviter les obstacles
      int angle = rand ()%80 + 30;

      switch (obstacle_flag)
      {
        case LEFT_OBS:
              motors_rotate_right(angle);
              break;
        case FRONT_OBS:
              motors_rotate_left(angle);
              break;
        case RIGHT_OBS:
              motors_rotate_left(angle);
              break;
        case NO_OBS:
              break;
      }
      return;
}

/* ajouter des points à la carte
addoffset ?
set_Object(map map,position_t point, char objectType)
objectType = E(mpty), W(all), M(ovable), N(on movable) */
