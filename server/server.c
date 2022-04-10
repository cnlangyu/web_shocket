#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<ctype.h>
#include<arpa/inet.h>

// 服务器端口
#define SERVER_POST 8888


int main(void){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_POST);

    //实现服务器与端口的绑定
    bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));

    listen(sock, 128);

    printf("await client link...\n");

    for(int i = 1; ; ){
        printf("start ...");
        struct sockaddr_in client;
        socklen_t client_addr_len = sizeof(client);
        int client_sock = accept(sock, (struct sockaddr *)&client, &client_addr_len);

        char client_ip[64];

        printf("client ip : %s, port : %d\n", 
            inet_ntop(AF_INET, &client.sin_addr.s_addr, client_ip, sizeof(client_ip)),
            ntohs(client.sin_port));

        //读取客户端数据
        char buf[1024];
        int len = read(client_sock, buf, sizeof(buf) - 1);
        buf[len] = '\0';
        printf("receive[%d]: %s\n", len, buf);

        len = write(client_sock, buf, len);

        printf("write[%d] finished...\n", len);
        close(client_sock);

    }

    return 0;
}