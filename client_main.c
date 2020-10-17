#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include "common_socket.h"
#include "common_codificador.h"

#define SUCCESS 0
#define ERROR -1

#define TAM_IP 16
#define TAM_PUERTO 6
#define TAM_KEY 256

#define FORMATO_PARAM_METODO "--method="
#define FORMATO_PARAM_KEY "--key="

#define VACIO ""

//Pre: -
//Post: copia tiene los mismos bytes que original hasta tope.
void pasar_bytes(unsigned char copia[],
				unsigned char original[], size_t tope) {
	for(size_t i = 0; i < tope; i++) copia[i] = original[i];
}

void pasar_bytes_signed(char copia[], char original[], size_t tope) {
	for(size_t i = 0; i < tope; i++) copia[i] = original[i];
}

//Pre: -
//Post: Valida si parametro tiene el formato de formato_parametro, en tal caso
//devuelve true, false en caso contrario.
bool es_parametro_valido(char* parametro, char* formato_parametro) {
	size_t largo_formato = strlen(formato_parametro),
			largo_parametro = strlen(parametro);

	if (largo_parametro <= largo_formato) return false;

	size_t i = 0;

	bool son_iguales = true;

	while (son_iguales && i < largo_formato) {
		if (parametro[i] != formato_parametro[i]) son_iguales = false;

		i++;
	}

	return son_iguales;
}

//Pre: socket y codificador inicializados.
//Post: -
void enviar_mensaje(socket_t* socket, codificador_t* codificador) {
	unsigned char buffer[TAM_BUFFER] = VACIO,
					buffer_encriptado[TAM_BUFFER] = VACIO;
	int bytes_enviados = 0;

	do {
		int leidos = fread(buffer, 1, TAM_BUFFER, stdin);
		pasar_bytes(buffer_encriptado, buffer, leidos);

		codificador_encodear(codificador, buffer_encriptado, leidos);
		bytes_enviados = socket_enviar(socket, buffer_encriptado, leidos);
	} while (bytes_enviados > 0);
}

//Pre: -
//Post: Inicia conexion con el servidor.
void iniciar_conexion(char ip[TAM_IP], char puerto[TAM_PUERTO],
						char metodo[TAM_METODO], char key[TAM_KEY]) {
	socket_t socket;

	if (socket_inicializar(&socket, ip, puerto, 0) == ERROR) {
		perror("Error inicializando socket\n");
		return;
	}

	codificador_t codificador;

	if (codificador_inicializar(&codificador, metodo, key) == ERROR) {
		socket_destruir(&socket);
		perror("Error inicializando codificador\n");
		return;
	}

	if (socket_conectar(&socket) == SUCCESS) {
		enviar_mensaje(&socket, &codificador);
	}

	codificador_destruir(&codificador);
	socket_destruir(&socket);
}

//Pre: -
//Post: Devuelve 0 si el parametro ingresado es valido, -1 en caso contrario.
int parsear_parametro(char* parametro_ingresado,
						char* parametro, char* formato_parametro) {
	if (es_parametro_valido(parametro_ingresado, formato_parametro)) {
		size_t inicio_parametro_ingresado = strlen(formato_parametro);
		pasar_bytes_signed(parametro,
					&(parametro_ingresado[inicio_parametro_ingresado]),
					strlen(&(parametro_ingresado[inicio_parametro_ingresado]))
					 + 1);

		return SUCCESS;
	}

	return ERROR;
}

int main(int argc, char *argv[]) {
	if (argc < 5) {
		printf("./client <ip> <puerto> --method=<metodo> --key=<key>\n");
		return 0;
	}

	char ip[TAM_IP] = VACIO, puerto[TAM_PUERTO] = VACIO;

	pasar_bytes_signed(ip, argv[1], strlen(argv[1]) + 1);
	pasar_bytes_signed(puerto, argv[2], strlen(argv[2]) + 1);

	char metodo[TAM_METODO] = VACIO, key[TAM_KEY] = VACIO;

	if (parsear_parametro(argv[3], metodo, FORMATO_PARAM_METODO) != ERROR && 
		parsear_parametro(argv[4], key, FORMATO_PARAM_KEY) != ERROR) {
		iniciar_conexion(ip, puerto, metodo, key);
	}

	return 0;
}
