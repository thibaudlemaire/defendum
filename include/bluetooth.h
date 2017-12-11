//
// Created by Thibaud Lemaire on 20/11/2017.
//

#ifndef OS_ROBOT_BLUETOOTH_H
#define OS_ROBOT_BLUETOOTH_H

// Server communications
#define TEAM_ID                 3   // Team ID for bluetooth communication with server
#define SERVER_TEAM_ID          0xFF
#define SERV_ADDR               "dc:53:60:ad:61:90"     // Whatever the address of the server is
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
void send_position( position_t position );
void drop_obstacle( position_t position );
void pick_up_obstacle( position_t position );
void send_map_point(position_t position, char color);

#endif //OS_ROBOT_BLUETOOTH_H
