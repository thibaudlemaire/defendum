//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <stdio.h>
#include <pthread.h>
#include "compass.h"
#include "brick.h"
#include "main.h"

POOL_T compass_sensor;             /* Compass sensor port (will be detected) */

int init_compass( void )
{
    compass_sensor = sensor_search( HT_NXT_COMPASS );
    if ( compass_sensor ) {
        sensor_set_mode( compass_sensor, HT_NXT_COMPASS_COMPASS );
        printf("Compass sensor found and configured\n");
        return ( 1 );
    }
    printf( "Compass sensor not found, exit\n" );
    return ( 0 );
}

/* Thread of compass sensor */
void *compass_main(void *arg)
{
    int old_measure, measure; // Measure [0 ; 2 550] cm
    if ( compass_sensor == SOCKET__NONE_ ) pthread_exit(NULL);
    while (alive)
    {
        /* Waiting for measured compass change */
        if (( measure = sensor_get_value(COMPASS_DIRECTION, compass_sensor, 0)) == old_measure ) {
            sleep_ms( COMPASS_PERIOD );
            continue;
        }
        old_measure = measure;
        printf("Compass : %u° \n", measure);
    }
    printf("Exit compass\n");
    pthread_exit(NULL);
}
