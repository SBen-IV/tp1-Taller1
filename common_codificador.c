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
	codificador->pos_key_1 = codificador->pos_key_2 = 0;

	if ((strcmp(metodo, METODO_CESAR) == 0) ||
		(strcmp(metodo, METODO_VIGENERE) == 0) ||
		(strcmp(metodo, METODO_RC4) == 0)) {
		strncpy(codificador->nombre_metodo, metodo, strlen(metodo) + 1);
	}

	return SUCCESS;
}

void codificador_encodear(codificador_t* codificador, unsigned char* mensaje,
						size_t largo_mensaje) {
	if (strcmp(codificador->nombre_metodo, METODO_CESAR) == 0) {
		cesar_encodear(codificador->key, mensaje, largo_mensaje);

	} else if (strcmp(codificador->nombre_metodo, METODO_VIGENERE) == 0) {
		vigenere_encodear(codificador->key, &(codificador->pos_key_1),
							mensaje, largo_mensaje);
		
	} else if (strcmp(codificador->nombre_metodo, METODO_RC4) == 0) {
		rc4_encodear(codificador->key, &(codificador->pos_key_1),
		 			&(codificador->pos_key_2), mensaje, largo_mensaje);
	}
}

void codificador_desencodear(codificador_t* codificador,
							unsigned char* mensaje,	size_t largo_mensaje) {
	if (strcmp(codificador->nombre_metodo, METODO_CESAR) == 0) {
		cesar_desencodear(codificador->key, mensaje, largo_mensaje);

	} else if (strcmp(codificador->nombre_metodo, METODO_VIGENERE) == 0) {
		vigenere_desencodear(codificador->key, &(codificador->pos_key_1),
							mensaje, largo_mensaje);
		
	} else if (strcmp(codificador->nombre_metodo, METODO_RC4) == 0) {
		rc4_desencodear(codificador->key, &(codificador->pos_key_1),
						&(codificador->pos_key_2), mensaje, largo_mensaje);
	}
}

int codificador_destruir(codificador_t* codificador) {
	return 0;
}
