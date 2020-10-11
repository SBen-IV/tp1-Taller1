#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "common_socket.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"

void recibir_mensaje(socket_t* socket) {

	unsigned char buffer[TAM_BUFFER], key[15] = "Key";
	int recibidos = 0;

	do{
		recibidos = socket_recibir(socket, buffer, TAM_BUFFER);
//		cesar_desencodear(240, buffer, recibidos);
//		vigenere_desencodear(key, buffer, recibidos);
		rc4_desencodear(key, buffer, recibidos);
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