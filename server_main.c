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

void recibir_mensaje(socket_t* socket, codificador_t* codificador) {
	unsigned char buffer[TAM_BUFFER] = BUFFER_VACIO,
					buffer_desencriptado[TAM_BUFFER] = BUFFER_VACIO;
	int bytes_recibidos = 0;

	do {
		bytes_recibidos = socket_recibir(socket, buffer, TAM_BUFFER);
		pasar_bytes(buffer_desencriptado, buffer, bytes_recibidos);

		codificador_desencodear(codificador, buffer_desencriptado, bytes_recibidos);
		fwrite(buffer_desencriptado, 1, bytes_recibidos, stdout);
	} while (bytes_recibidos > 0);
}

int main(int argc, char *argv[]) {
	if (argc < 4){
		printf("./server <puerto> --method=<metodo> --key=<key>\n");
		return 0;
	}

	socket_t socket;

	if (socket_inicializar(&socket, NULL, argv[1], AI_PASSIVE) == ERROR) {
		perror("Error inicializando socket");
		return 0;
	}

	codificador_t codificador;

	if (codificador_inicializar(&codificador, &argv[2][9],
								&argv[3][6]) == ERROR) {
		socket_destruir(&socket);		
		return 0;
	}

	if (socket_conectar(&socket) == SUCCESS && 
		socket_conectar_con_cliente(&socket) == SUCCESS) {
		recibir_mensaje(&socket, &codificador);
	}

	codificador_destruir(&codificador);
	socket_destruir(&socket);

	return 0;
}
