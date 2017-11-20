//
// Created by Thibaud Lemaire on 20/11/2017.
//

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "bluetooth.h"
#include "brick.h"
#include "main.h"
#include "display.h"

int s;
uint16_t msgId = 0;

int read_from_server(int sock, char *buffer, size_t maxSize)
{
    int bytes_read = read(sock, buffer, maxSize);

    if (bytes_read <= 0) {
        print_error("Server unexpectedly closed connection...\n");
        close (s);
        // TODO Proper exit
    }

    return bytes_read;
}

int init_bluetooth( void )
{
    struct sockaddr_rc addr = { 0 };
    int status;

    /* allocate a socket */
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    /* set the connection parameters (who to connect to) */
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba(SERV_ADDR, &addr.rc_bdaddr);

    /* connect to server */
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    /* if connected */
    if( status == 0 ){
        char string[MESSAGE_MAX_LENGHT];
        /* Wait for START message */
        read_from_server(s, string, 9);
        if (string[4] == MSG_START) {
            print_console("Connected to the server !");
            return ( 1 );
        }
    }
    print_error("Failed to connect to server...");
    return ( 1 ); // TODO change to 0 when server is available
}

void *bluetooth_main(void *arg) {
    while (alive)
        sleep_ms(1000);
    pthread_exit(NULL);
}

