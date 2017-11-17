//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <stdio.h>
#include <pthread.h>
#include "rotation.h"
#include "brick.h"
#include "main.h"

POOL_T rotation_sensor;             /* Rotation sensor port (will be detected) */

int init_rotation( void )
{
    rotation_sensor = sensor_search( LEGO_EV3_GYRO );
    if ( rotation_sensor ) {
        gyro_set_mode_gyro_g_and_a( rotation_sensor );
        printf("Rotation sensor found and configured as Angle + Rotational speed\n");
        return ( 1 );
    }
    printf( "Rotation sensor not found, exit\n" );
    return ( 0 );
}

/* Thread of rotation sensor */
void *rotation_main(void *arg)
{
    int old_angle, angle, old_rspeed, rspeed;  // Angle [-32 768 ; 32 767] deg; RSpeed [-440 ; 440] deg/s
    if ( rotation_sensor == SOCKET__NONE_ ) pthread_exit(NULL);
    while (alive)
    {
        /* Waiting rotation change */
        if (( angle = sensor_get_value(ROTATION_ANGLE, rotation_sensor, 0)) != old_angle ) {
            old_angle = angle;
            printf("Angle : %d° \n", angle);
        }
        if ((rspeed = sensor_get_value(ROTATION_SPEED, rotation_sensor, 0)) != old_rspeed ) {
            old_rspeed = rspeed;
            printf("Rotational speed : %d°/s \n", rspeed);
        }
        sleep_ms(ROTATION_PERIOD);

    }
    printf("Exit rotation\n");
    pthread_exit(NULL);
}
