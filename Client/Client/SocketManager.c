//
//  SocketManager.c
//  Process1
//
//  Created by Dio Brand on 2023/4/3.
//

#include "SocketManager.h"

int port = 8000;
char *addr = "127.0.0.1";

int send_msg(struct msg_data *send_msg,struct msg_data *recv_msg) {
    int sockfd;
    unsigned long numbytes;
    char buff[BUFSIZ];
    bzero(buff, BUFSIZ);
    struct sockaddr_in server_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket create fail!\n");
        return -1;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(addr);
    bzero(&(server_addr.sin_zero), sizeof(server_addr.sin_zero));
    
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        printf("connect fail!\n");
        return -1;
    }
    printf("Connect Server success!\n");
    
    if (send(sockfd, send_msg->msg, send_msg->len, 0) < 0)
    {
        perror("socket send");
        return -1;
    }
    bzero(buff, BUFSIZ);
    numbytes = recv(sockfd, buff, BUFSIZ, 0);
    if (numbytes)
    {
        buff[numbytes] = '\0';
        printf("From Server:\n%s\n", buff);
        memcpy(recv_msg->msg, buff, numbytes);
        recv_msg->len = numbytes;
        bzero(buff, BUFSIZ);
    }
    else
    {
        printf("Server accepting close!\n");
    }
    
    close(sockfd);
    return 0;
}

int receive(struct msg_data *recv_msg) {
    int sockfd;
    unsigned long numbytes;
    char buff[BUFSIZ];
    bzero(buff, BUFSIZ);
    struct sockaddr_in server_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket create fail!\n");
        return -1;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(addr);
    bzero(&(server_addr.sin_zero), sizeof(server_addr.sin_zero));
    
    
    numbytes = recv(sockfd, buff, BUFSIZ, 0);
    printf("numbytes:%lu\n",numbytes);
    printf("line:%d\n",__LINE__);
    if (numbytes)
    {
        recv_msg->msg[numbytes] = '\0';
        printf("received message:%s\n", recv_msg->msg);
        memcmp(recv_msg->msg, buff, numbytes);
        recv_msg->len = numbytes;
    }
    else
    {
        printf("Server accepting close!\n");
        close(sockfd);
    }
    return 0;
}
