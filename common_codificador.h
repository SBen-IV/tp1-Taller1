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

//Pre: codificador declarado.
//Post: Devuelve 0 si se pudo inicializar codificador correctamente,
//-1 en caso de error.
int codificador_inicializar(codificador_t* codificador,
							char metodo[TAM_METODO], void* key);

//Pre: codificador inicializado.
//Post: Devuelve mensaje encriptado por el método especificado al inicializar
//codificador.
void codificador_encodear(codificador_t* codificador,
							unsigned char mensaje[TAM_MENSAJE],
							size_t largo_mensaje);

//Pre: codificador inicializado.
//Post: Devuelve mensaje desencriptado por el método especificado al 
//inicializar codificador.
void codificador_desencodear(codificador_t* codificador,
							unsigned char mensaje[TAM_MENSAJE],
							size_t largo_mensaje);

//Pre: codificador inicializado.
//Post: Devuelve 0 en caso que se haya destruido correctamente, -1 en caso
//de error.
int codificador_destruir(codificador_t* codificador);

#endif
