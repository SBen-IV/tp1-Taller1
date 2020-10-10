#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "common_socket.h"

#define TAM_BUFFER 10
#define SUCCESS 0
#define ERROR -1

void enviar_mensaje(socket_t* socket){

	char buffer[TAM_BUFFER];

	int leidos; // = fread(buffer, 1, TAM_BUFFER, stdin);
	int bytes_enviados = 0;
/*
	while (leidos > bytes_enviados) {
		bytes_enviados += socket_enviar_mensaje(socket,
		 					&buffer[bytes_enviados], leidos-bytes_enviados);
		leidos = fread(buffer, 1, TAM_BUFFER, stdin);
	}
*/
	do {
		leidos = fread(buffer, 1, TAM_BUFFER, stdin);
		while (leidos > bytes_enviados) {
			bytes_enviados += socket_enviar_mensaje(socket,
		 					&buffer[bytes_enviados], leidos-bytes_enviados);
		}
		bytes_enviados = 0;	
	}while (leidos > 0);
}


int main(int argc, char const *argv[]){
	
	socket_t socket;

	if (socket_inicializar(&socket, "localhost", "8080") != 0) {
		printf("Error.\n");
		return 0;
	}

	if (socket_conectar(&socket) == SUCCESS){
		enviar_mensaje(&socket);
	}

	socket_destruir(&socket);

	return 0;
}