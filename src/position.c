//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include <pthread.h>
#include <time.h>
#include "position.h"
#include "brick.h"
#include "main.h"
#include "display.h"


// Current position, global, it is initialized only when globalState -> WAITING_FOR_START called by bluetooth?
position_t current_position;
time_t last_update_date;

/**
  * Function used to init position not sure if it is needed
  * @return 1
  */
int init_position( void )
{
  print_console("Position thread initialized");
  return 1;
}

/**
  * Main function of position thread
  * @param arg
  * @return a generic pointer used by pthread
  */
void *pthread_main(void *arg)
{
  while (alive)
  {
    update_postion();
    sleep_ms(POSITION_PERIOD);
  }
  pthread_exit(NULL);
}

/**
  * Function used to update the position, must be called before every motor change
  * @param arg
  * @return 1 if the position have been update, 0 if it failed
  */
int update_postion( void )
{
  time_t current_time = time(NULL);
  switch (state) {
    case STOP | LEFT | RIGHT :
        // We are leaving a not moving state so we save the date to calcul further positions
        last_update_date = time(NULL);
        break;
    case FORTH :
        // TODO : calcul new position with last value, compass and delta of time_t
        break;
    case BACK :
        // TODO : calcul new position with last value, compass and delta of time_t
        break;
  }
  return 1;
}

/**
  * Function to initialize current_position
  */
void initialize_position( void )
{
  current_position->x=0;
  current_position->y=0;
}
