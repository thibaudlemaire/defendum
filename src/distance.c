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
 * Function called to update distance value
 */
void distance_update(void)
{
        distance_value = sensor_get_value(DISTANCE_CM_MODE, distance_sensor, 0);
}
