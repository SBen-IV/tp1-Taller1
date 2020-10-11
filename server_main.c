#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include "common_socket.h"


int main(int argc, char const *argv[]) {

	socket_t socket;

	if (socket_inicializar(&socket, NULL, "8080", AI_PASSIVE)) {
		printf("Error\n");
		return 0;
	}

	socket_destruir(&socket);

	return 0;
}