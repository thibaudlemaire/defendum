//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include "behaviour.h"
#include "motors.h"
#include "main.h"
#include "brick.h"
#include "display.h"
#include "touch.h"

void behaviour_main(void)
{
      print_console("Behaviour initialized");

      /*
      motors_rotate_right(90);
      motors_forward(THREE);
      sleep_ms(3000);
      motors_stop();*/

      while(alive)
      {
          sleep_ms(TOUCH_PERIOD);

          if (touch_is_touched())
          {
              motors_rotate_left(5);
              motors_forward(THREE);
              sleep_ms(1000);
          }
          else
          {
              motors_rotate_right(3);
              motors_forward(THREE);
              sleep_ms(1500);

          }

      }

}
