#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define TAM_BUFFER 64

typedef int (*funcion_enlazadora_t)(int, const struct sockaddr*, socklen_t);

typedef struct socket{
	struct addrinfo hints;
	struct addrinfo* resultado;
	int file_descriptor;
	int peer;
	funcion_enlazadora_t enlazar;
}socket_t;

//Pre: Declarar skt, flag = AI_PASSIVE para servidor, 0 para cliente.
//Post: Devuelve 0 en caso que socket se haya inicializado
//correctamente, -1 en caso contrario.
int socket_inicializar(socket_t* skt, const char* ip, const char* puerto,
						int flag);

//Pre: skt inicializado.
//Post:
//	- Como cliente: establece conexión con el servidor.
//	- Como servidor: obtiene un file_descriptor para ser usado por 
//	socket_conectar_con_cliente.
//	- En ambos casos devuelve 0 si se completó correctamente, -1 en caso
//	de error.
int socket_conectar(socket_t* skt);

//Pre: skt está enlazado.
//Post: Devuelve 0 en caso de haber conectado satisfactoriamente con el
//cliente, -1 en caso contrario.
int socket_conectar_con_cliente(socket_t* skt);

//Pre: skt inicializado y conectado con cliente.
//Post: Devuelve la cantidad de bytes recibidos, 0 en caso de que
//se haya perdido la conexión con el cliente, -1 en caso de error.
int socket_recibir(socket_t* skt, unsigned char buffer[TAM_BUFFER], 
					size_t bytes_a_recibir);

//Pre: skt inicializado y conectado al servidor.
//Post: Devuelve la cantidad de bytes enviados, 0 en caso de que
//se haya perdido la conexión con el servidor, -1 en caso de error.
int socket_enviar(socket_t* skt, unsigned char buffer[TAM_BUFFER],
					size_t bytes_a_enviar);

//Pre: skt inicializado.
//Post: Devuelve 0 con skt destruido.
int socket_destruir(socket_t* skt);

#endif
