//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include "behaviour.h"
#include "motors.h"
#include "main.h"
#include "brick.h"
#include "display.h"

void behaviour_main(void)
{
      print_console("Behaviour initialized");

      rotate_right(90);
      forward(THREE);
      sleep_ms(3000);
      rotate_left(180);
      backward(TWO);
      sleep(2000);
      stop();

}
