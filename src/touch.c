//
// Created by Romain Parracone on 05/12/2017.
//

#include <pthread.h>
#include "touch.h"
#include "brick.h"
#include "main.h"
#include "display.h"
#include "behaviour.h"

POOL_T touch_sensor;             // touch sensor port

/**
 * Function used to init the touch sensor module
 * @return 1 if ok, 0 otherwise
 */
int init_touch( void )
{
        touch_sensor = sensor_search( LEGO_EV3_TOUCH );
        if ( touch_sensor ) {
                print_console("Touch sensor found and configured");
                return ( 1 );
        }
        print_error( "Touch sensor not found, exit" );
        return ( 1 );
}

void *touch_main(void *arg)
{
        while (alive)
        {
                if(sensor_get_value(TOUCH_CHANNEL, touch_sensor, 0))
                        obstacle_touched();
                sleep_ms(TOUCH_PERIOD);
        }
        pthread_exit(NULL);
}

int touch_is_touched(void)
{
  return sensor_get_value(TOUCH_CHANNEL, touch_sensor, 0);
}
