#include "common_codificador.h"
#include <string.h>

#define METODO_CESAR "cesar"
#define METODO_VIGENERE "vigenere"
#define METODO_RC4 "rc4"

#define SUCCESS 0
#define ERROR -1

int codificador_inicializar(codificador_t* codificador, char* metodo,
							void* key) {
	strncpy(codificador->nombre_metodo, metodo, strlen(metodo) + 1);
	int valor_ret_inicializar = ERROR;

	if (strcmp(codificador->nombre_metodo, METODO_CESAR) == 0){
		valor_ret_inicializar = cesar_inicializar(&(codificador->cesar), key);
		
	} else if (strcmp(codificador->nombre_metodo, METODO_VIGENERE) == 0){
		valor_ret_inicializar = vigenere_inicializar(&(codificador->vigenere),
													key);
	} else if (strcmp(codificador->nombre_metodo, METODO_RC4) == 0) {
		valor_ret_inicializar = rc4_inicializar(&(codificador->rc4), key);
	}

	return valor_ret_inicializar;
}

void codificador_encodear(codificador_t* codificador,
						unsigned char mensaje[TAM_MENSAJE],
						size_t largo_mensaje) {
	if (strcmp(codificador->nombre_metodo, METODO_CESAR) == 0) {
		cesar_encodear(&(codificador->cesar), mensaje, largo_mensaje);

	} else if (strcmp(codificador->nombre_metodo, METODO_VIGENERE) == 0) {
		vigenere_encodear(&(codificador->vigenere), mensaje, largo_mensaje);

	} else {
		rc4_encodear(&(codificador->rc4), mensaje, largo_mensaje);
	}
}

void codificador_desencodear(codificador_t* codificador,
							unsigned char mensaje[TAM_MENSAJE],
							size_t largo_mensaje) {
	if (strcmp(codificador->nombre_metodo, METODO_CESAR) == 0) {
		cesar_desencodear(&(codificador->cesar), mensaje, largo_mensaje);

	} else if (strcmp(codificador->nombre_metodo, METODO_VIGENERE) == 0) {
		vigenere_desencodear(&(codificador->vigenere), mensaje, largo_mensaje);
		
	} else {
		rc4_desencodear(&(codificador->rc4), mensaje, largo_mensaje);
	}
}

int codificador_destruir(codificador_t* codificador) {
	int valor_ret_destruir = ERROR;

	if (strcmp(codificador->nombre_metodo, METODO_CESAR) == 0){
		valor_ret_destruir = cesar_destruir(&(codificador->cesar));
	} else if (strcmp(codificador->nombre_metodo, METODO_VIGENERE) == 0){
		valor_ret_destruir = vigenere_destruir(&(codificador->vigenere));
	} else {
		valor_ret_destruir = rc4_destruir(&(codificador->rc4));
	}

	return valor_ret_destruir;
}
