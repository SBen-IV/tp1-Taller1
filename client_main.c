#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include "common_socket.h"
#include "common_codificador.h"

#define SUCCESS 0
#define ERROR -1

#define TAM_KEY 100

void enviar_mensaje(socket_t* socket, codificador_t* codificador) {
	unsigned char buffer[TAM_BUFFER], buffer_encriptado[TAM_BUFFER];
	int bytes_enviados = 0;

	do {
		int leidos = fread(buffer, 1, TAM_BUFFER, stdin);
		strncpy((char*)buffer_encriptado, (char*)buffer, leidos);

		codificador_encodear(codificador, buffer_encriptado, leidos);
		bytes_enviados = socket_enviar(socket, buffer_encriptado, leidos);
	}while (bytes_enviados > 0);
}

int main(int argc, char *argv[]) {
	if (argc < 5){
		printf("./client <ip> <puerto> --method=<metodo> --key=<key>\n");
		return 0;
	}

	socket_t socket;

	if (socket_inicializar(&socket, argv[1], argv[2], 0) != SUCCESS) {
		perror("Error inicializando socket\n");
		return 0;
	}

	codificador_t codificador;

	if (codificador_inicializar(&codificador, &argv[3][9],
								&argv[4][6]) == ERROR) return 0;

	if (socket_conectar(&socket) == SUCCESS) {
		enviar_mensaje(&socket, &codificador);
	}

	codificador_destruir(&codificador);
	socket_destruir(&socket);

	return 0;
}
