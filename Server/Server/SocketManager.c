//
//  SocketManager.c
//  Process2
//
//  Created by Dio Brand on 2023/4/3.
//

#include "SocketManager.h"

int port = 8000;
int listen_port = 5; // 最大监听数

int start(void) {
    int sockfd, client_fd;
    unsigned int struct_len;
    unsigned long numbytes;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char buff[BUFSIZ];
    bzero(buff, BUFSIZ);
    struct_len = sizeof(struct sockaddr_in);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
loop:
    bzero(&(server_addr.sin_zero), sizeof(server_addr.sin_zero));
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket create fail!\n");
        return -1;
    }
    int ret;
    do
    {
        ret = bind(sockfd, (struct sockaddr *)&server_addr, struct_len);
    } while (ret != -1);
    
    if (listen(sockfd, listen_port) == -1)
    { // 监听 port
        printf("Listening fail\n");
        return -1;
    }
    
    printf("Ready for Accept,Waitting...\n");
    client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &struct_len);
    printf("Client was accepting\n");
    
    while (1)
    {
        // recv 返回接收的数据长度
        numbytes = recv(client_fd, buff, BUFSIZ, 0);
        if (numbytes > 0)
        {
            //            buff[numbytes] = 0; // 把接收到的二进制数据当作字符串来处理
            //            printf("message from client:%s\n", buff);
            //            strcat(buff, " | your message was received!");
            // 把接收到的消息原封不动的返回
            if (send(client_fd, buff, numbytes, 0) < 0)
            {
                perror("write");
                return -1;
            }
            bzero(buff, BUFSIZ);
        }
        else
        {
            printf("Client accepting close!\n");
            close(client_fd);
            close(sockfd);
            break;
        }
    }
    
    goto loop;
    return 0;
}
