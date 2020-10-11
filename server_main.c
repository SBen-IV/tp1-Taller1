#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "common_socket.h"

void recibir_mensaje(socket_t* socket) {

	unsigned char buffer[TAM_BUFFER];
	int recibidos = 0;

	do{
		recibidos = socket_recibir(socket, buffer, TAM_BUFFER);
		fwrite(buffer, 1, recibidos, stdout);
	} while (recibidos > 0);
}


int main(int argc, char const *argv[]) {

	socket_t socket;

	if (socket_inicializar(&socket, NULL, "8080", AI_PASSIVE)) {
		printf("Error\n");
		return 0;
	}

	socket_enlazar(&socket);

	socket_conectar_con_cliente(&socket);

	recibir_mensaje(&socket);

	socket_destruir(&socket);

	return 0;
}