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

void *behaviour_main(void *arg)
{
      //print_console("Behaviour initialized");
      explore_arena();

}

void explore_arena(void)
{
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
}
