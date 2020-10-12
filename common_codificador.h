#ifndef _COMMON_CODIFICADOR_H_
#define _COMMON_CODIFICADOR_H_

#include <stddef.h>
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"

//#define TAM_S_BOX 256
#define TAM_METODO 9

typedef struct codificador{

	void* key;
	void (*encodear)(void* , unsigned char*, size_t);
	void (*desencodear)(void* , unsigned char*, size_t);
}codificador_t;


int codificador_inicializar(codificador_t* codificador,
							char metodo[TAM_METODO], void* key);


void codificador_encodear(codificador_t* codificador, unsigned char* mensaje,
						size_t largo_mensaje);

void codificador_desencodear(codificador_t* codificador,
							unsigned char* mensaje, size_t largo_mensaje);


int codificador_destruir(codificador_t* codificador);

#endif