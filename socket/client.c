#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int port = 9999;
    if (argv[1] != NULL) {
        port = atoi(argv[1]);
    }

    int sd = socket(AF_INET, SOCK_STREAM, 0);   // socket descriptor
    if(sd < 0) {
        perror("fail to create socket");
        exit(-1);
    }

    struct sockaddr_in ssa;     // server socket address
    ssa.sin_family = AF_INET;
    ssa.sin_addr.s_addr = inet_addr("127.0.0.1");
    ssa.sin_port = htons(port);     // convert byte order

    printf("connecting to 127.0.0.1:%d...\n", ntohs(ssa.sin_port));
    if(connect(sd, (struct sockaddr *)&ssa, sizeof(ssa)) < 0) {
        perror("fail connect to server");
    }
    printf("connect successed.\n");

    /* send msg to server via socket descriptor */
    char *msg = "[client] hello socket server.";
    if (send(sd, msg, strlen(msg) + 1, 0) < 0) {
        perror("fail to send data");
    }
    printf("data sent. receive response...\n");

    /* hang & receive msg from server */
    char buf[1024];
    int n = recv(sd, &buf, sizeof(buf), 0);
    if(n > 0) {
        printf("%s\n", buf);
    } else if(n < 0) {
        perror("fail to receive bytes");
    }
}
