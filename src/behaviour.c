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
#include "head.h"

enum globalState robot_state = INITIALIZING;            // Robot state
enum specificState specif_state;                        // Secondary state

/**
 * Main function of the behaviour thread
 * @param arg
 * @return pointer to the thread
 */
void *behaviour_main(void *arg)
{
    while(alive)
    {
        robot_state = WAITING_FOR_START;
        if (!wait_for(START_RECEIVED)) break;
        motors_forward(FIVE);
    }
        pthread_exit(NULL);
}

/**
 * Function used to wait for a particular global state
 * @param condition
 * @return 0 if program stop, 1 when condition is satisfied
 */
int wait_for(enum globalState condition) {
    while(alive && robot_state != condition)
        sleep_ms(BEHAVIOUR_PERIOD);
    if(alive) return 0;
    else return 1;
}

/**
 * Function called by bluetooth module when server start the game
 */
void start_received() {
    robot_state = START_RECEIVED;
}

/**
 * Function called by bluetooth module when server stop the game
 */
void stop_received() {
    return;
}

/**
 * Function called by the bluetooth module when robot get kicked
 */
void kicked() {
    motors_stop();
    alive = 0;
    robot_state = KICKED;
}

void obstacle_found() {
    return;
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
