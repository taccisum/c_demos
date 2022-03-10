#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int port = 9999;
    if (argv[1] != NULL) {
        port = atoi(argv[1]);
    }

    int sd = socket(AF_INET, SOCK_STREAM, 0);   // socket descriptor
    if (sd < 0)
    {
        perror("fail to create socket");
        exit(1);
    }

    /* use function bind() to assigns a name to the unamed socket created above */
    struct sockaddr_in ssa;     // server socket address
    ssa.sin_family = AF_INET;
    ssa.sin_addr.s_addr = inet_addr("127.0.0.1");
    ssa.sin_port = htons(port);     // notes that port is host byte order, should convert to network byte order via htons()
    if (bind(sd, (struct sockaddr *)&ssa, sizeof(ssa)) < 0)
    {
        perror("fail to bind socket addr");
        exit(2);
    }

    /* call function listen(). if success, means named socket is ready to aceept connection requests(from pending queue) */
    if(listen(sd, 5) < 0) 
    {
        perror("fail to listen socket");
        exit(3);
    }

    printf("[%d] listen 127.0.0.1:%d. server is ready for connection requests now...\n", getpid(), ntohs(ssa.sin_port));
    while(1)
    {
        /* call function accept(). wait for next incoming connection request */
        int csd;   // connection socket descriptor
        struct sockaddr_in csa;     // client socket address
        socklen_t sl = sizeof(csa);
        if((csd = accept(sd, (struct sockaddr *)&csa, &sl)) < 0)
        {
            perror("fail to accept conn");
        }
        printf("[%d] accepted connection. socket fd: %d.\n", getpid(), csd);

        if(fork() == 0) {
            // fork child process to handle this connection request
            printf("[%d] handle connection. receive data...\n", getpid());
            char buf[1024];
            int n = recv(csd, &buf, sizeof(buf), 0);
            if(n > 0) {
                printf("%s\n", buf);
            } else if(n < 0) {
                perror("fail to receive bytes");
            }
            char *msg = "[server] hi socket client.";
            send(csd, msg, strlen(msg) + 1, 0);
            printf("[%d] response sent.\n", getpid());
            exit(0);
        }
    }
}
