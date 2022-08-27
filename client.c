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
    int client_sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (client_sock == -1){
        perror("Socket creation failed\n");
        exit(0);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr=INADDR_ANY;

    int c = connect(client_sock, (struct sockaddr*)&server, sizeof(server));
    if (c == -1){
        perror("Connection failed\n");
        exit(0);
    }

    int num1, num2, result;
    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    send(client_sock, &num1, 4, 0);
    send(client_sock, &num2, 4, 0);

    recv(client_sock, &result, 4, 0);
    printf("\n\nThe sum is: %d\n", result);
    
    close(client_sock);
}