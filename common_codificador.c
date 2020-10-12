#include "common_codificador.h"
#include <string.h>

#define METODO_CESAR "cesar"
#define METODO_VIGENERE "vigenere"
#define METODO_RC4 "rc4"

#define SUCCESS 0
#define ERROR -1

int codificador_inicializar(codificador_t* codificador, char* metodo,
							void* key) {
	codificador->key = key;
	codificador->pos_key = 0;

	if (strcmp(metodo, METODO_CESAR) == 0) {
		codificador->encodear = cesar_encodear;
		codificador->desencodear = cesar_desencodear;
	} else if (strcmp(metodo, METODO_VIGENERE) == 0) {
		codificador->encodear = vigenere_encodear;
		codificador->desencodear = vigenere_desencodear;
	} else if (strcmp(metodo, METODO_RC4) == 0) {
		codificador->encodear = rc4_encodear;
		codificador->desencodear = rc4_desencodear;
	} else {
		return ERROR;
	}

	return SUCCESS;
}

void codificador_encodear(codificador_t* codificador, unsigned char* mensaje,
						size_t largo_mensaje) {
	codificador->encodear(codificador->key, mensaje, largo_mensaje,
							codificador->pos_key);
}

void codificador_desencodear(codificador_t* codificador,
							unsigned char* mensaje,	size_t largo_mensaje) {
	codificador->desencodear(codificador->key, mensaje, largo_mensaje,
							codificador->pos_key);
}

int codificador_destruir(codificador_t* codificador) {
	return 0;
}
