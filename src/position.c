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
#include "bluetooth.h"
#include "map.h"


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
                update_position(command);
                bt_send_coordinates(position_to_coordinates(current_position));
                sleep_ms(POSITION_PERIOD);
        }
        pthread_exit(NULL);
}

/**
 * Function used to update the position, must be called before every motor change
 * @param arg
 * @return 1 if the position have been update, 0 if it failed
 */
int update_position( int state )
{
        int temp_tacho;
        double temp_direction;
        switch (state) {
        case STOP:
        case LEFT:
        case RIGHT:
                // We are leaving a not moving state so we save the date to calcul further positions
                current_tacho = tacho_get_position(MOTOR_RIGHT,0);
                break;
        case FORTH:
        case BACK:
                temp_tacho = (int) tacho_get_position(MOTOR_RIGHT,10) - current_tacho;
                temp_direction = (double) (rotation_angle - compass_offset)*M_PI/180;
                current_position.y = (int) (current_position.y + (temp_tacho*M_PI*WHEEL_RADIUS/180)*(cos(temp_direction)));
                current_position.x = (int) (current_position.x + (temp_tacho*M_PI*WHEEL_RADIUS/180)*(sin(temp_direction)));
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
        compass_offset = rotation_angle;
        current_tacho = tacho_get_position(MOTOR_RIGHT,0);
}
