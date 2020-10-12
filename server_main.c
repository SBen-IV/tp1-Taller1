#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include "common_socket.h"
#include "common_codificador.h"

#define SUCCESS 0
#define ERROR -1

void recibir_mensaje(socket_t* socket, codificador_t* codificador) {
	unsigned char buffer[TAM_BUFFER], buffer_desencriptado[TAM_BUFFER];
	int recibidos = 0;

	do{
		recibidos = socket_recibir(socket, buffer, TAM_BUFFER);
		strncpy((char*)buffer_desencriptado, (char*)buffer, recibidos);

		codificador_desencodear(codificador, buffer_desencriptado, recibidos);
		fwrite(buffer_desencriptado, 1, recibidos, stdout);
	} while (recibidos > 0);
}


int main(int argc, char *argv[]) {
	if (argc < 4){
		printf("./server <puerto> --method=<metodo> --key=<key>\n");
		return 0;
	}

	socket_t socket;

	if (socket_inicializar(&socket, NULL, argv[1], AI_PASSIVE)) {
		perror("Error inicializando socket\n");
		return 0;
	}

	codificador_t codificador;

	if (codificador_inicializar(&codificador, &argv[2][9],
								&argv[3][6]) == ERROR) return 0;

	socket_enlazar(&socket);

	if (socket_conectar_con_cliente(&socket) == SUCCESS){
		recibir_mensaje(&socket, &codificador);
	}

	socket_destruir(&socket);

	return 0;
}
