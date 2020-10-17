#include <stdio.h>
#include <stdlib.h>
#include "common_cesar.h"

#define SUCCESS 0
#define ERROR -1

#define ERROR_CONVERSION 0

#define TAM_ABECEDARIO 256

static void aplicar_cesar(int key, unsigned char* msj, size_t tope_msj) {
	for(int i = 0; i < tope_msj; i++)
		msj[i] = (msj[i] + key) % TAM_ABECEDARIO;
}

int cesar_inicializar(cesar_t* cesar, void* key) {
	cesar->key = atoi((char*)key);

	if (cesar->key == ERROR_CONVERSION) return ERROR;

	return SUCCESS;
}

void cesar_encodear(cesar_t* cesar, unsigned char* mensaje,
					size_t largo_mensaje) {
	aplicar_cesar(cesar->key, mensaje, largo_mensaje);
}

void cesar_desencodear(cesar_t* cesar, unsigned char* mensaje,
						size_t largo_mensaje) {
	aplicar_cesar(cesar->key*(-1), mensaje, largo_mensaje);
}

int cesar_destruir(cesar_t* cesar) {
	return SUCCESS;
}
