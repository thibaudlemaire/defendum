//
// Created by Thibaud Lemaire on 17/11/2017.
//

#include <pthread.h>
#include "compass.h"
#include "brick.h"
#include "main.h"
#include "display.h"

POOL_T compass_sensor;             // Compass sensor port

/**
 * Function used to init hte compass sensor module
 * @return 1 if ok, 0 otherwise
 */
int init_compass( void )
{
        compass_sensor = sensor_search( HT_NXT_COMPASS );
        if ( compass_sensor ) {
                sensor_set_mode( compass_sensor, HT_NXT_COMPASS_COMPASS );
                compass_heading = sensor_get_value(COMPASS_DIRECTION_MODE, compass_sensor, 0);
                print_console("Compass sensor found and configured");
                return ( 1 );
        }
        print_error( "Compass sensor not found, exit" );
        return ( 0 );
}

/**
 * Main function of the compass thread
 * @param arg
 * @return a generic pointer used by pthread
 */
void *compass_main(void *arg)
{
        int old_measure, measure; // Measure [0 ; 359] deg
        if ( compass_sensor == SOCKET__NONE_ ) pthread_exit(NULL);
        while (alive)
        {
                /* Waiting for measured compass change */
                if (( measure = sensor_get_value(COMPASS_DIRECTION_MODE, compass_sensor, 0)) == old_measure ) {
                        sleep_ms( COMPASS_PERIOD );
                        continue;
                }
                old_measure = measure;
                compass_heading = measure;
        }
        pthread_exit(NULL);
}
