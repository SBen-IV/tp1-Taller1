#ifndef _COMMON_RC4_
#define _COMMON_RC4_

#include <string.h>
#include <stddef.h>

#define TAM_S_BOX 256

typedef struct rc4{
	size_t pos_s_box_1;
	size_t pos_s_box_2;
	unsigned char s_box[TAM_S_BOX];
}rc4_t;

//Pre: rc4 declarado, key inicializado.
//Post: Devuelve 0 si se pudo inicializar correctamente, -1 en caso de error.
int rc4_inicializar(rc4_t* rc4, void* key);

//Pre: rc4 inicializado.
//Post: Devuelve mensaje encriptado.
void rc4_encodear(rc4_t* rc4, unsigned char* mensaje, size_t largo_mensaje);

//Pre: rc4 inicializado, mensaje debe estar encriptado por rc4.
//Post: Devuelve mensaje desencriptado.
void rc4_desencodear(rc4_t* rc4, unsigned char* mensaje,
						size_t largo_mensaje);

//Pre: rc4 inicializado.
//Post: Devuelve 0.
int rc4_destruir(rc4_t* rc4);

#endif
