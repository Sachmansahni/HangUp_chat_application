
# include "headers.h"

void error ( const char*msg ) {
    perror ( msg );    //interprets error number and  outputs the error description using stderr
    exit ( 1 );
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Port number not provided, program terminated.\n");
        exit(1);
    }

    char buffer[255];
    int sockfd, newsockfd, portno, n;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    memset((char*)&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Binding failed");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
    if (newsockfd < 0) {
        error("Error on accept");
    }

    while (1) {
        memset(buffer, 0, 255);
        n = recv(newsockfd, buffer, 255, 0);
        if (n < 0) {
            error("Error on reading");
        }
        printf("Client: %s", buffer);

        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);

        n = send(newsockfd, buffer, strlen(buffer), 0);
        if (n < 0) {
            error("Error on writing");
        }

        if (strcmp("Bye\n", buffer) == 0) {  // Include newline for fgets
            break;
        }
    }

    // Close sockets after exiting the loop
    close(newsockfd);
    close(sockfd);

    return 0;
}

// 172.21.21.200