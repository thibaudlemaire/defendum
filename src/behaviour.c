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
#include "map.h"

enum crosstate crossing_state = EXPLORING_ARENA;

void *behaviour_main(void *arg)
{
      //print_console("Behaviour initialized");

      cross_arena();

      pthread_exit(NULL);

}

void cross_arena(void)
{
      while(alive)
      {
            sleep_ms(MOTORS_PERIOD);
            switch (crossing_state)
            {
                  case SEARCHING_WALL:
                      search_wall();
                      break;
                  case FOLLOWING_WALL:
                      follow_wall();
                      break;
                  case EXPLORING_ARENA:
                      explore_arena();
                      break;
                  case MOVABLE_OBJ_DETECTED:
                      //catch_movable_obj();
                      break;
            }
      }

}

/* fonction qui déplace le robot depuis son point de départ et le positionne
*  proche d'un mur, parallèle au mur, le mur à sa droite
*/
void search_wall(void)
{

      if(0) //TODO si l'orientation n'est pas bonne, on oriente le robot comme il faut
      {
            motors_rotate_right(90);
      }


      if (obstacle_flag == FRONT_OBS)
      {
            motors_rotate_left(90);
            crossing_state++;
      }
      else
      {
            motors_forward(TWO);
      }

      return;
}

//non opérationnel
void follow_wall(void)
{

      if (obstacle_flag != NO_OBS)
      {
            dodge_obstacle();
      }

      if (touch_is_touched())
      {
          /*set_Object(map, current_position, 'W');*/
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


      //quitte quand y < 0, car on a fini de faire le tour, éventuellement à revoir
      /*if (current_position.y > 0) //erreur ici avec current_position
      {
          crossing_state++;
      }*/
      return;
}

/*
* Fonction qui explore le centre de l'arene, appelée après celle qui détermine le contour
*/
void explore_arena(void)
{
      if (obstacle_flag != NO_OBS)
      {
            random_dodge_obstacle();
            switch (obstacle_flag)
            {
                case LEFT_OBS:
                    print_console("left_obs");
                    break;
                case FRONT_OBS:
                    print_console("front_obs");
                    break;
                case RIGHT_OBS:
                    print_console("right_obs");
                    break;
                default:
                    break;
            }

      }
      else
      {
            //set_Object(map, current_position, 'E');
            motors_forward(ONE);
      }

      /*
      if (movable_objet_detected)
      {
            crossing_state = MOVABLE_OBJ_DETECTED;
      }
      */

      return;
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

void catch_movable_obj(void)
{
      //TODO

      motors_stop();

      //Une fois l'objet attrapé, retourner à l'état précédent
      /*if (obj_caught)
      {
        crossing_state = EXPLORING_ARENA;
      }*/

      return;
}
