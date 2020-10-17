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

	if (strcmp(metodo, METODO_CESAR) == 0){
		valor_ret_inicializar = cesar_inicializar(&(codificador->cesar), key);
	} else if (strcmp(metodo, METODO_VIGENERE) == 0){
		valor_ret_inicializar = vigenere_inicializar(&(codificador->vigenere),
													key);
	} else if (strcmp(metodo, METODO_RC4) == 0) {
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

	} else if (strcmp(codificador->nombre_metodo, METODO_RC4) == 0) {
	//	rc4_encodear(codificador->key, &(codificador->pos_key_1),
	//	 			&(codificador->pos_key_2), mensaje, largo_mensaje,
	//	 			codificador->s_box);
	}
}

void codificador_desencodear(codificador_t* codificador,
							unsigned char mensaje[TAM_MENSAJE],
							size_t largo_mensaje) {
	if (strcmp(codificador->nombre_metodo, METODO_CESAR) == 0) {
		cesar_desencodear(&(codificador->cesar), mensaje, largo_mensaje);

	} else if (strcmp(codificador->nombre_metodo, METODO_VIGENERE) == 0) {
		vigenere_desencodear(&(codificador->vigenere), mensaje, largo_mensaje);
		
	} else if (strcmp(codificador->nombre_metodo, METODO_RC4) == 0) {
	//	rc4_desencodear(codificador->key, &(codificador->pos_key_1),
	//					&(codificador->pos_key_2), mensaje, largo_mensaje,
	//					codificador->s_box);
	}
}

int codificador_destruir(codificador_t* codificador) {
	return SUCCESS;
}
