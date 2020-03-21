#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
//#include <sys/socket.h>

int main(){
    system("clear");

    printf("\x1b[33m%s\x1b[0m", " _____________________________________________________________________________________\n");
    printf("\x1b[33m%s\x1b[0m", "|  ____        _   _   _       _____ _     _          _____                           |\n");
    printf("\x1b[33m%s\x1b[0m", "| |  _ \\      | | | | | |     / ____| |   (_)        / ____|                          |\n");
    printf("\x1b[33m%s\x1b[0m", "| | |_) | __ _| |_| |_| | ___| (___ | |__  _ _ __   | (___   ___ _ ____   _____ _ __  |\n");
    printf("\x1b[33m%s\x1b[0m", "| |  _ < / _` | __| __| |/ _ \\\\___ \\| '_ \\| | '_ \\   \\___ \\ / _ \\ '__\\ \\ / / _ \\ '__| |\n");
    printf("\x1b[33m%s\x1b[0m", "| | |_) | (_| | |_| |_| |  __/____) | | | | | |_) |  ____) |  __/ |   \\ V /  __/ |    |\n");
    printf("\x1b[33m%s\x1b[0m", "| |____/ \\__,_|\\__|\\__|_|\\___|_____/|_| |_|_| .__/  |_____/ \\___|_|    \\_/ \\___|_|    |\n");
    printf("\x1b[33m%s\x1b[0m", "|                                           | |                                       |\n");
    printf("\x1b[33m%s\x1b[0m", "|                                           |_|                                       |\n");
    printf("\x1b[33m%s\x1b[0m", "|_____________________________________________________________________________________|\n\n");

    char player_one[30], player_two[30];

    int puerto;
    printf("\x1b[34m%s\x1b[0m", "Ingresa el puerto a utilizar:");
    scanf("%d", &puerto);
    
    //printf(puerto);

    //Configuracion de Socket
    int server_socket, client_socket;
    char buffer[1024];
    struct sockaddr_in server;
    struct sockaddr client;

    socklen_t client_size;
    int status;

    pid_t id;

    //Preparando Socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket == -1){
        perror("server: error al crear el Socket");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(puerto);

    if(bind(server_socket, (struct sockaddr*) &server, sizeof(server)) != 0){
        perror("server: error al inicializar el socket");
    }

    if(listen(server_socket, 2) != 0){
        perror("server: error al establecer la cantidad de jugadores");
        exit(1);
    }

    printf("\x1b[32m%s\x1b[0m", "Esperando a los jugadores...\n\n");

    while(1) {
        client_socket = accept(server_socket, &client, &client_size);

        if(client_socket < 0) {
            perror("accept");
        }

        printf("\x1b[34m%s\x1b[0m", "Se ha conectado un jugador \n");

        if((id = fork()) == 0){
            close(server_socket);

            if( (status = recv(client_socket, buffer, 1024, 0)) == 0 ) { 
                printf("\x1b[31m%s\x1b[0m", "Un jugador se ha desconectado \n");
                exit(1);
            }
            else {
                write(1, buffer, status);
            }

        }

    }






    return 0;
}