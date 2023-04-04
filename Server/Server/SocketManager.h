//
//  SocketManager.h
//  Process2
//
//  Created by Dio Brand on 2023/4/3.
//

#ifndef SocketManager_h
#define SocketManager_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int start(void);

#endif /* SocketManager_h */
