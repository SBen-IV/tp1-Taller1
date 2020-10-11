#define _POSIX_C_SOURCE 200112L

#include "common_socket.h"

#include <stdio.h>

#define ERROR -1
#define SUCCESS 0

#define SOCKET_CERRADO 0

#define TAM_BUFFER 10

int socket_inicializar(socket_t* skt, const char* ip, const char* puerto,
						int flag){

	memset(&(skt->hints), 0, sizeof(struct addrinfo));
	skt->hints.ai_family = AF_INET;
	skt->hints.ai_socktype = SOCK_STREAM;
	skt->hints.ai_flags = flag;

	int estado = getaddrinfo(ip, puerto, &(skt->hints), &(skt->resultado));
	if (estado != 0) {
		freeaddrinfo(skt->resultado);
		return ERROR;
	}

	return SUCCESS;
}

int socket_conectar(socket_t* skt){

	skt->s = socket(skt->resultado->ai_family,
					skt->resultado->ai_socktype, 
					skt->resultado->ai_protocol);

	if (skt->s == ERROR) {
		freeaddrinfo(skt->resultado);
		return ERROR;	
	}

	if (connect(skt->s, skt->resultado->ai_addr,
				skt->resultado->ai_addrlen) != SUCCESS) {
		return ERROR;
	}

	printf("Conectado!\n");

	return SUCCESS;
}

int socket_destruir(socket_t* skt){
	close(skt->s);
	freeaddrinfo(skt->resultado);

	return SUCCESS;
}

int socket_enviar(socket_t* skt, unsigned char* mensaje, int largo,
					bool* socket_abierto){

	int bytes_enviados = send(skt->s, mensaje, largo, MSG_NOSIGNAL);

	if (bytes_enviados == ERROR) {
		perror("Cerrando socket");
		(*socket_abierto) = false;
		return ERROR;
	} else if (bytes_enviados == SOCKET_CERRADO) {
		printf("Socket cerrado\n");
		(*socket_abierto) = false;
		return SOCKET_CERRADO;
	}

	return bytes_enviados;
}
/*
int s = socket(resultado->ai_family, resultado->ai_socktype, resultado->ai_protocol);

	if(s == ERROR){
		freeaddrinfo(resultado);
		return ERROR;	
	}

	if (connect(s, resultado->ai_addr, resultado->ai_addrlen) == SUCCESS) {
		printf("Conectado...\n");
		enviar_mensajes(s);
	}

*/
/*
void enviar_mensajes(int socket){

	char buffer[TAM_BUFFER];
	int enviados = 0;
	int leidos = fread(buffer, 1, TAM_BUFFER, stdin);

	do {
		enviados += send(socket, &buffer[enviados], leidos-enviados, MSG_NOSIGNAL);
	} while (enviados < leidos);
}
*/