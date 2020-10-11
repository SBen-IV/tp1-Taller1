#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct socket{
	struct addrinfo hints;
	struct addrinfo* resultado;
	int s;
}socket_t;

//Pre: Declarar skt
//Post: Devuelve 0 en caso que se socket se haya inicializado
//correctamente, -1 en caso contrario
int socket_inicializar(socket_t* skt, const char* ip, const char* puerto,
						int flag);


//Pre: skt inicializado
//Post: se conecta al servidor pasado en inicializar
int socket_conectar(socket_t* skt);


//Pre: skt inicializado, mensaje no está vacío, largo > 0
//Post: Envia mensaje al servidor especificado en socket_inicialzar
int socket_enviar(socket_t* skt, unsigned char* mensaje, int largo,
					bool* socket_abierto);


//Pre: skt fue inicializado
//Post: devuelve 0 en caso de que se haya podido liberar
//la memoria que usaba socket, -1 en caso contario
int socket_destruir(socket_t* skt);

#endif