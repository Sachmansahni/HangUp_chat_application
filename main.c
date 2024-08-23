# include "headers.h"

void error ( const char*msg ) {
    perror ( msg );    //interprets error number and  outputs the error description using stderr
    exit ( 1 );
}

int main ( int argc , char *argv[] ){
    if(argc<2){
        fprintf( stderr , "port number not provided,program terminated \n" );
        exit ( 1 ) ;
    }

    char buffer[255];                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    int sockfd , newsockfd , portno , n;

    struct sockaddr_in serv_addr,cli_addr;   //sockaddr_in gives/contains internet address 
    socklen_t clilen;  

    sockfd = socket(AF_INET , SOCK_STREAM ,0);
    if(sockfd<0){
        error("error opening socket");
    }  

    memset((char*)&serv_addr, 0, sizeof(serv_addr));
    portno=atoi(argv[1]);     //agrv[1] contains the file name and argv[0] contains the port number;

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(portno);    //htons-> host to network short

    if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        error("binding failed");
    }

    listen(sockfd,5);
    clilen=sizeof(cli_addr);

    newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);

    if(newsockfd<0){
        error("error on accept");
    }

    while(1){
        memset(buffer,0,255);
        n=recv(newsockfd,buffer,255,0);
        if(n<0){
            error("error on reading");
        }
        printf("Client : %s",buffer);

        memset(buffer,0,255);
        fgets(buffer,255,stdin);

        n=send(newsockfd,buffer,strlen(buffer),0);
        if(n<0){
            error("error on writing");
        }


        int i=strcmp("Bye",buffer);
        if(i==0){
            break;
        }
        closesocket(newsockfd);
        closesocket(sockfd);

        return 0;
    }
}