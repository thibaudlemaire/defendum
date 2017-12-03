//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <pthread.h>
#include "rotation.h"
#include "brick.h"
#include "main.h"
#include "display.h"

POOL_T rotation_sensor;             /* Rotation sensor port (will be detected) */

/**
 * Function used to init rotation module
 * @return 1 if ok, 0 otherwise
 */
int init_rotation( void )
{
        rotation_sensor = sensor_search( LEGO_EV3_GYRO );
        if ( rotation_sensor ) {
                gyro_set_mode_gyro_g_and_a( rotation_sensor );
                rotation_angle = sensor_get_value(ROTATION_ANGLE, rotation_sensor, 0);
                rotation_rspeed = sensor_get_value(ROTATION_SPEED, rotation_sensor, 0);
                print_console("Rotation sensor found and configured");
                return ( 1 );
        }
        print_error( "Rotation sensor not found, exit" );
        return ( 0 );
}

/**
 * Main function of rotation thread
 * @param arg
 * @return
 */
void *rotation_main(void *arg)
{
        int old_angle, angle, old_rspeed, rspeed; // Angle [-32 768 ; 32 767] deg; RSpeed [-440 ; 440] deg/s
        if ( rotation_sensor == SOCKET__NONE_ ) pthread_exit(NULL);
        while (alive)
        {
                /* Waiting rotation change */
                if (( angle = sensor_get_value(ROTATION_ANGLE, rotation_sensor, 0)) != old_angle ) {
                        old_angle = angle;
                        rotation_angle = angle;
                }
                if ((rspeed = sensor_get_value(ROTATION_SPEED, rotation_sensor, 0)) != old_rspeed ) {
                        old_rspeed = rspeed;
                        rotation_rspeed = rspeed;
                }
                sleep_ms(ROTATION_PERIOD);

        }
        pthread_exit(NULL);
}
