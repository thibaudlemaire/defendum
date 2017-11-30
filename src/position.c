//
// Created by Thibaud Lemaire on 23/11/2017.
//

#include <pthread.h>
#include <time.h>
#include <math.h>
#include "brick.h"
#include "main.h"
#include "display.h"
#include "position.h"
#include "motors.h"


// Current position, global, it is initialized only when globalState -> WAITING_FOR_START called by bluetooth?
position_t current_position;
int32_t current_tacho;
int compass_offset;

/**
 * Function used to init position not sure if it is needed
 * @return 1
 */
int init_position( void )
{
        print_console("Position thread initialized");
        initialize_position();
        return 1;
}

/**
 * Main function of position thread
 * @param arg
 * @return a generic pointer used by pthread
 */
void *position_main(void *arg)
{
        while (alive)
        {
                print_console("position alive")
                if (robot_state == CROSSING_ARENA) {
                    update_postion(command);

                }
                sleep_ms(POSITION_PERIOD);
        }
        pthread_exit(NULL);
}

/**
 * Function used to update the position, must be called before every motor change
 * @param arg
 * @return 1 if the position have been update, 0 if it failed
 */
int update_postion( int state )
{
        int32_t temp_tacho;
        double temp_direction;
        print_console("update")
        switch (state) {
        case STOP | LEFT | RIGHT:
                // We are leaving a not moving state so we save the date to calcul further positions
                current_tacho = tacho_get_position(MOTOR_RIGHT,0);
                break;
        case FORTH | BACK:
                // TODO : calcul new position with last value, compass and delta of time_t
                print_console('change position')
                temp_tacho = tacho_get_position(MOTOR_RIGHT,0) - current_tacho;
                temp_direction = (double) ((compass_heading - compass_offset + 360) % 360)*M_PI/180;
                current_position.x = current_position.x + (temp_tacho*M_PI*WHEEL_RADIUS/180)*((int) cos(temp_direction));
                current_position.y = current_position.y + (temp_tacho*M_PI*WHEEL_RADIUS/180)*((int) sin(temp_direction));
                current_tacho = tacho_get_position(MOTOR_RIGHT,0);
                break;
        }
        return 1;
}

/**
 * Function to initialize current_position and current_tacho
 */
void initialize_position( void )
{
        current_position.x=0;
        current_position.y=0;
        compass_offset = compass_heading;
        current_tacho = tacho_get_position(MOTOR_RIGHT,0);
}
