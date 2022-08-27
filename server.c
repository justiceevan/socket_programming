#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h> 
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<unistd.h>

int main(){
    system("clear");
    /*s = socket(domain, type, protocol)

    If the protocol is unspecified (a value of 0), the system selects a protocol that supports the requested socket type.
    
    Protocol family table

    AF_APPLETALK -Apple Computer Inc. Appletalk network 
    AF_INET - Internet domain 
    AF_PUP - Xerox Corporation PUP internet 
    AF_UNIX - Unix file system 

    Socket types are defined in sys/socket.h. These types--SOCK_STREAM, SOCK_DGRAM, or SOCK_RAW--are supported by AF_INET and AF_UNIX. 
    The following creates a stream socket in the Internet domain:

    s = socket(AF_INET, SOCK_STREAM, 0);

    This call results in a stream socket with the TCP protocol providing the underlying communication

    */
    int serverfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Creates a socket 
    if (serverfd == -1){
        perror("Socket creation failed\n");
        exit(0);
    }

    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr=INADDR_ANY;
    /*
    The bind() call allows a process to specify the local address of the socket. 
    This forms the set local address, local port (or local pathname) while connect() and accept() complete a socket's 
    association by fixing the remote half of the address tuple. The bind() function call is used as follows:

    bind (s, name, namelen);

    */
    int b = bind(serverfd, (struct sockaddr*)&server, sizeof(server));
    if (b == -1){
        perror("Bind failed\n");
        exit(0);
    }

    listen(serverfd, 5);  /* Allow queue of 5 connections */
    printf("Listening for request\n");
    int size = sizeof(client);
    int clientfd = accept(serverfd, (struct sockaddr*)&client, &size);
    if (clientfd == -1){
        perror("Accept failed\n");
        exit(0);
    }
    printf("Requested from %s\n", inet_ntoa(client.sin_addr));

    int num1, num2, result;

    /* recv(s, buf, sizeof buf, flags);
    The flag can be passed as a non zero if one or more of the following
        Send and receive out-of-band data
        Look at data without reading
        Send data without routing packets*/

    recv(clientfd, &num1, 4, 0);
    recv(clientfd, &num2, 4, 0);

    result = num1 + num2;
    send(clientfd, &result, 4, 0);
    
    close(clientfd);
    close(serverfd);
}