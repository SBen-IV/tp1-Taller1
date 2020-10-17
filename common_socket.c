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
	if (estado != SUCCESS) {
		freeaddrinfo(skt->resultado);
		return ERROR;
	}

	if (flag == AI_PASSIVE) {
		skt->enlazar = bind;
	} else {
		skt->enlazar = connect;
	}

	return SUCCESS;
}

int socket_conectar(socket_t* skt) {
	bool esta_conectado = false;
	struct addrinfo* resultado_aux = skt->resultado;

	while (resultado_aux && !esta_conectado) {
		skt->file_descriptor = socket(resultado_aux->ai_family,
									resultado_aux->ai_socktype, 
									resultado_aux->ai_protocol);

		if (skt->file_descriptor != ERROR) {
			if (skt->enlazar(skt->file_descriptor, resultado_aux->ai_addr,
					resultado_aux->ai_addrlen) == SUCCESS) {
				esta_conectado = true;
			} else {
				close(skt->file_descriptor);
			}
		}

		resultado_aux = resultado_aux->ai_next;
	}

	if (!esta_conectado) return ERROR;

	return SUCCESS;
}

int socket_conectar_con_cliente(socket_t* skt) {
	if (listen(skt->file_descriptor, 1) == SUCCESS){
		skt->peer = accept(skt->file_descriptor, NULL, NULL);

		if (skt->peer == ERROR) {
			perror("Error al conectar con cliente");
			return ERROR;
		}
	}

	return SUCCESS;
}

int socket_recibir(socket_t* skt, unsigned char buffer[TAM_BUFFER],
					size_t bytes_a_recibir) {
	int total_bytes_recibidos = 0;
	bool socket_abierto = true;
	
	while (total_bytes_recibidos < bytes_a_recibir && socket_abierto){
		int bytes_recibidos = recv(skt->peer, &buffer[total_bytes_recibidos],
								bytes_a_recibir-total_bytes_recibidos, 0);

		if (bytes_recibidos == ERROR) {
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
	int total_bytes_enviados = 0;
	bool socket_abierto = true;

	while (total_bytes_enviados < bytes_a_enviar && socket_abierto) {
		int bytes_enviados = send(skt->file_descriptor,
								&mensaje[total_bytes_enviados],
								bytes_a_enviar-total_bytes_enviados,
								MSG_NOSIGNAL);

		if (bytes_enviados == ERROR) {
			socket_abierto = false;
		} else if (bytes_enviados == SOCKET_CERRADO) {
			socket_abierto = false;
		} else {
			total_bytes_enviados += bytes_enviados;
		}
	}

	return total_bytes_enviados;
}

int socket_destruir(socket_t* skt) {
	if (skt->peer) close(skt->peer);
	if (skt->file_descriptor) close(skt->file_descriptor);

	freeaddrinfo(skt->resultado);

	return SUCCESS;
}
