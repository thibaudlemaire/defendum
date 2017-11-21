//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <pthread.h>
#include "distance.h"
#include "brick.h"
#include "main.h"
#include "display.h"

POOL_T distance_sensor;             /* Distance sensor port (will be detected) */

/**
 * Function used to init distance module
 * @return 1 is ok, 0 otherwise
 */
int init_distance( void )
{
    distance_sensor = sensor_search( LEGO_EV3_US );
    if ( distance_sensor ) {
        us_set_mode_us_dc_cm( distance_sensor );
        print_console("Distance sensor found and configured");
        return ( 1 );
    }
    print_error( "Distance sensor not found, exit" );
    return ( 0 );
}

/**
 * Main function of distance thread
 * @param arg
 * @return a generic pointer used by pthread
 */
void *distance_main(void *arg)
{
    int old_measure, measure; // Measure [0 ; 2 550] cm
    while (alive)
    {
        /* Waiting for measured distance change */
        if (( measure = sensor_get_value(DISTANCE_CM_MODE, distance_sensor, 0)) == old_measure ) {
            sleep_ms( DISTANCE_PERIOD );
            continue;
        }
        old_measure = measure;
        distance_value = measure;
    }
    pthread_exit(NULL);
}
