#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdbool.h>
#include "common_socket.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"

#define SUCCESS 0
#define ERROR -1

void enviar_mensaje(socket_t* socket){

	unsigned char buffer[TAM_BUFFER], key[15] = "Key";
	int leidos, bytes_enviados = 0;

	do {
		leidos = fread(buffer, 1, TAM_BUFFER, stdin);
//		cesar_encodear(240, buffer, leidos);
//		vigenere_encodear(key, buffer, leidos);
		rc4_encodear(key, buffer, leidos);
		bytes_enviados = socket_enviar(socket, buffer, leidos);
	}while (bytes_enviados > 0);
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