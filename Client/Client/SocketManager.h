//
//  SocketManager.h
//  Process1
//
//  Created by Dio Brand on 2023/4/3.
//

#ifndef SocketManager_h
#define SocketManager_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>    // for open
#include <unistd.h> // for close

struct msg_data {
    char msg[BUFSIZ];
    unsigned long len;
};

int send_msg(struct msg_data *send_msg,struct msg_data *recv_msg);
int receive(struct msg_data *recv_msg);

#endif /* SocketManager_h */
