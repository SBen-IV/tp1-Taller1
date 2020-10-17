#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include "common_socket.h"
#include "common_codificador.h"

#define SUCCESS 0
#define ERROR -1

#define BUFFER_VACIO ""

//Pre: -
//Post: copia tiene los mismos bytes que original hasta tope.
void pasar_bytes(unsigned char copia[TAM_BUFFER],
				unsigned char original[TAM_BUFFER], size_t tope) {
	for(size_t i = 0; i < tope; i++) copia[i] = original[i];
}

//Pre: socket y codificador inicializados.
//Post: -
void enviar_mensaje(socket_t* socket, codificador_t* codificador) {
	unsigned char buffer[TAM_BUFFER] = BUFFER_VACIO,
					buffer_encriptado[TAM_BUFFER] = BUFFER_VACIO;
	int bytes_enviados = 0;

	do {
		int leidos = fread(buffer, 1, TAM_BUFFER, stdin);
		pasar_bytes(buffer_encriptado, buffer, leidos);

		codificador_encodear(codificador, buffer_encriptado, leidos);
		bytes_enviados = socket_enviar(socket, buffer_encriptado, leidos);
	} while (bytes_enviados > 0);
}

int main(int argc, char *argv[]) {
	if (argc < 5) {
		printf("./client <ip> <puerto> --method=<metodo> --key=<key>\n");
		return 0;
	}

	socket_t socket;

	if (socket_inicializar(&socket, argv[1], argv[2], 0) == ERROR) {
		perror("Error inicializando socket\n");
		return 0;
	}

	codificador_t codificador;

	if (codificador_inicializar(&codificador, &argv[3][9],
								&argv[4][6]) == ERROR){
		socket_destruir(&socket);
		return 0;
	}

	if (socket_conectar(&socket) == SUCCESS) {
		enviar_mensaje(&socket, &codificador);
	}

	codificador_destruir(&codificador);
	socket_destruir(&socket);

	return 0;
}
