#ifndef _COMMON_CODIFICADOR_H_
#define _COMMON_CODIFICADOR_H_

#include <stdlib.h>
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"

#define TAM_METODO 10
#define TAM_MENSAJE 64

typedef struct codificador{
	cesar_t cesar;
	vigenere_t vigenere;
	rc4_t rc4;
	char nombre_metodo[TAM_METODO];
}codificador_t;

int codificador_inicializar(codificador_t* codificador,
							char metodo[TAM_METODO], void* key);

void codificador_encodear(codificador_t* codificador,
							unsigned char mensaje[TAM_MENSAJE],
							size_t largo_mensaje);

void codificador_desencodear(codificador_t* codificador,
							unsigned char mensaje[TAM_MENSAJE],
							size_t largo_mensaje);

int codificador_destruir(codificador_t* codificador);

#endif
