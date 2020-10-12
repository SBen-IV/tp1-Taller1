#define _POSIX_C_SOURCE 200112L

#include "common_socket.h"

#include <stdio.h>

#define ERROR -1
#define SUCCESS 0

#define SOCKET_CERRADO 0

int socket_inicializar(socket_t* skt, const char* ip, const char* puerto,
						int flag) {

	memset(skt, 0, sizeof(socket_t));
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

int socket_conectar(socket_t* skt) {

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

	return SUCCESS;
}

int socket_enlazar(socket_t* skt) {
	skt->s = socket(skt->resultado->ai_family,
					skt->resultado->ai_socktype, 
					skt->resultado->ai_protocol);

	if (skt->s == ERROR) {
		freeaddrinfo(skt->resultado);
		return ERROR;	
	}

	if (bind(skt->s, skt->resultado->ai_addr,
				skt->resultado->ai_addrlen) != SUCCESS) {
		return ERROR;
	}

	return SUCCESS;
}

int socket_conectar_con_cliente(socket_t* skt) {

	if (listen(skt->s, 1) == SUCCESS){
		skt->peer = accept(skt->s, skt->resultado->ai_addr,
							&(skt->resultado->ai_addrlen));

		if (skt->peer == ERROR) {
			perror("Error al conectar con cliente");
			return ERROR;
		}
	}

	return SUCCESS;
}

int socket_recibir(socket_t* skt, unsigned char buffer[TAM_BUFFER],
					size_t bytes_a_recibir) {

	int bytes_recibidos = 0, total_bytes_recibidos = 0;
	bool socket_abierto = true;
	
	while (bytes_recibidos < bytes_a_recibir && socket_abierto){
		bytes_recibidos = recv(skt->peer, &buffer[total_bytes_recibidos],
								bytes_a_recibir-total_bytes_recibidos, 0);

		if (bytes_recibidos == ERROR) {
			perror("Error");
			socket_abierto = false;
		} else if (bytes_recibidos == SOCKET_CERRADO) {
			socket_abierto = false;
		} else {
			total_bytes_recibidos += bytes_recibidos;
		}
	}

	return total_bytes_recibidos;
}

int socket_enviar(socket_t* skt, unsigned char mensaje[TAM_BUFFER],
					size_t bytes_a_enviar){

	int bytes_enviados = 0, total_bytes_enviados = 0;
	bool socket_abierto = true;

	while (bytes_enviados < bytes_a_enviar && socket_abierto) {
		bytes_enviados = send(skt->s, &mensaje[total_bytes_enviados],
								bytes_a_enviar-total_bytes_enviados,
								MSG_NOSIGNAL);

		if (bytes_enviados == ERROR) {
			perror("Cerrando socket");
			socket_abierto = false;
		} else if (bytes_enviados == SOCKET_CERRADO) {
			printf("Socket cerrado");
			socket_abierto = false;
		} else {
			total_bytes_enviados += bytes_enviados;
		}
	}

	return total_bytes_enviados;
}

int socket_destruir(socket_t* skt) {

	if(skt->peer) close(skt->peer);
	close(skt->s);
	freeaddrinfo(skt->resultado);

	return SUCCESS;
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