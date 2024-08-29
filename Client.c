/*

filename server_ipaddress portno
argv[0] filename
argv[1] server_ipaddress
argv[2] portno

*/



# include "headers.h"

void error ( const char*msg ) {
    perror ( msg );    //interprets error number and  outputs the error description using stderr
    exit ( 1 );
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR OPENING SOCKET");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR NO SUCH HOST\n");
        exit(1);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR CONNECTING");
    }

    while (1) {
        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);
        n = send(sockfd, buffer, strlen(buffer), 0);
        if (n < 0) {
            error("ERROR ON WRITING");
        }

        memset(buffer, 0, 255);
        n = recv(sockfd, buffer, 255, 0);
        if (n < 0) {
            error("ERROR ON READING");
        }

        printf("server: %s", buffer);

        if (strcmp("Bye\n", buffer) == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}