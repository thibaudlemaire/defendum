//
// Created by Thibaud Lemaire on 20/11/2017.
//

#ifndef OS_ROBOT_BLUETOOTH_H
#define OS_ROBOT_BLUETOOTH_H

// Server communications
#define TEAM_ID         1   // Team ID for bluetooth communication with server
#define SERV_ADDR   "dc:53:60:ad:61:90"     /* Whatever the address of the server is */
#define MESSAGE_MAX_LENGHT 58

enum {
    MSG_ACK,
    MSG_START,
    MSG_STOP,
    MSG_KICK,
    MSG_POSITION,
    MSG_MAPDATA,
    MSG_MAPDONE,
};

int init_bluetooth( void );
void *bluetooth_main( void *arg );

#endif //OS_ROBOT_BLUETOOTH_H
