#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    system("clear");

    printf("\x1b[33m%s\x1b[0m", " ___________________________________________________\n");
    printf("\x1b[33m%s\x1b[0m", "|  ____        _   _   _       _____ _     _        |\n");
    printf("\x1b[33m%s\x1b[0m", "| |  _ \\      | | | | | |     / ____| |   (_)       |\n");
    printf("\x1b[33m%s\x1b[0m", "| | |_) | __ _| |_| |_| | ___| (___ | |__  _ _ __   |\n");
    printf("\x1b[33m%s\x1b[0m", "| |  _ < / _` | __| __| |/ _ \\\\___ \\| '_ \\| | '_ \\  |\n");
    printf("\x1b[33m%s\x1b[0m", "| | |_) | (_| | |_| |_| |  __/____) | | | | | |_) | |\n");
    printf("\x1b[33m%s\x1b[0m", "| |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_| .__/  |\n");
    printf("\x1b[33m%s\x1b[0m", "|                                           | |     |\n");
    printf("\x1b[33m%s\x1b[0m", "|                                           |_|     |\n");
    printf("\x1b[33m%s\x1b[0m", "|  Version: 0.1                                     |\n");
    printf("\x1b[33m%s\x1b[0m", "|___________________________________________________|\n\n");

    char ip[15];
    printf("\x1b[34m%s\x1b[0m", "Ingresa la ip del servidor:");
    scanf("%s", ip);

    int puerto;
    printf("\x1b[34m%s\x1b[0m", "Ingresa el puerto del servidor:");
    scanf("%d", &puerto);

    char nick[30];
    printf("\x1b[32m%s\x1b[0m", "Ingresa tu nickname:");
    scanf("%s", nick);

    int server_socket, msg;
    char buffer[1024];
    struct sockaddr_in server;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(puerto);

    if( connect(server_socket, (struct sockaddr *) &server, sizeof(server)) == -1 ) {
		perror("conexión: No se pudo establecer la conexión");
        exit(1);
    }

    printf("\x1b[34m%s\x1b[0m", "has ingresado a la sala!\n\n");

    while(1){
        msg = read(0, buffer, 1024);

        if(send(server_socket, buffer, msg, 0) == -1){
            printf("\x1b[31m%s\x1b[0m", "Se ha perdido la conexión\n");
            printf("\x1b[31m%s\x1b[0m", "La partida ha finalizado\n");
			exit(1);
        }
    }

    return 0;
}