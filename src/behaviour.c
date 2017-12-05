//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include "behaviour.h"
#include "motors.h"

void behaviour_main(void)
{
      while(alive)
      {
        rotate_right(90);
        forward(THREE);
        sleep_ms(5000);
      }
}
