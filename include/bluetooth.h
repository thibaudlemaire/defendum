//
// Created by Thibaud Lemaire on 20/11/2017.
//

#ifndef OS_ROBOT_BLUETOOTH_H
#define OS_ROBOT_BLUETOOTH_H

// Server communications
#define TEAM_ID                 3   // Team ID for bluetooth communication with server
#define SERVER_TEAM_ID          0xFF
#define SERV_ADDR               "9C:B6:D0:E2:82:BC"     // Whatever the address of the server is
#define MESSAGE_MAX_LENGHT      58
#define READ_TIMEOUT_SEC        2
#define RECONNEXION_PERIOD_SEC  2

// State
enum BtState {
        DISCONNECTED,
        CONNECTED,
};

// Protocol header positions
enum {
        MSG_ID_LSB,
        MSG_ID_MSB,
        MSG_SRC,
        MSG_DST,
        MSG_TYPE,
};

// Message types
enum {
        MSG_TYPE_ACK,
        MSG_TYPE_START,
        MSG_TYPE_STOP,
        MSG_TYPE_KICK,
        MSG_TYPE_POSITION,
        MSG_TYPE_MAPDATA,
        MSG_TYPE_MAPDONE,
        MSG_TYPE_OBSTACLE,
};

// Prototypes
int init_bluetooth( void );
void *bluetooth_main( void *arg );
void bt_send_coordinates( coordinates_t coordinates );
void bt_drop_obstacle( coordinates_t coordinates );
void bt_pick_up_obstacle( coordinates_t coordinates );
void bt_send_map_point( coordinates_t coordinates, char R,char G, char B);
void bluetooth_close();

#endif //OS_ROBOT_BLUETOOTH_H
