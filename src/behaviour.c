//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include <pthread.h>
#include "behaviour.h"
#include "motors.h"
#include "main.h"
#include "brick.h"
#include "display.h"
#include "touch.h"

enum globalState robot_state = EXPLORING_ARENA;           // Robot state
enum crossingArenaState crossing_state = SEARCHING_WALL;

void *behaviour_main(void *arg)
{
      print_console("Behaviour initialized");

      cross_arena();

      pthread_exit(NULL);

}

void cross_arena(void)
{
      search_wall();
      crossing_state++;

      follow_wall();
      crossing_state++;

      explore_arena();


}


void search_wall(void)
{

      // Sleep to let head initialise
      sleep_ms(1000);

      int wall_detected = 0;
      /* first face a wall */
      motors_rotate_right(90);

      while(alive && wall_detected==0)
      {
          sleep_ms(TOUCH_PERIOD);
          motors_forward(TWO);

          if (distance_value < 50)
          {
            sleep_ms(50);

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

          if (touch_is_touched())
          {
              motors_rotate_left(5);
              motors_forward(TWO);
              sleep_ms(1000);
          }
          else
          {
              motors_rotate_right(3);
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
}
