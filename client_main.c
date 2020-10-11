#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdbool.h>
#include "common_socket.h"
#include "common_cesar.h"

#define TAM_BUFFER 1
#define SUCCESS 0
#define ERROR -1

void enviar_mensaje(socket_t* socket){

	unsigned char buffer[TAM_BUFFER];
	int leidos, bytes_enviados = 0;
	bool socket_abierto = true;

	do {
		leidos = fread(buffer, 1, TAM_BUFFER, stdin);
		cesar_encodear(5, buffer, leidos);
		while (leidos > bytes_enviados && socket_abierto) {
			bytes_enviados += socket_enviar(socket,
		 					&buffer[bytes_enviados], leidos-bytes_enviados,
		 					&socket_abierto);
		}
		bytes_enviados = 0;	
	}while (leidos > 0 && socket_abierto);
}


int main(int argc, char const *argv[]){
	
	socket_t socket;

	if (socket_inicializar(&socket, "localhost", "8080", 0) != SUCCESS) {
		printf("Error.\n");
		return 0;
	}

	if (socket_conectar(&socket) == SUCCESS){
		enviar_mensaje(&socket);
	}

	socket_destruir(&socket);

	return 0;
}