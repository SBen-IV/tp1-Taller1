#ifndef _COMMON_VIGENERE_H_
#define _COMMON_VIGENERE_H_

#include <stddef.h>
#include <string.h>

typedef struct vigenere{
	unsigned char* key;
	size_t largo_key;
	size_t pos_key;
}vigenere_t;

//Pre: vigenere declarado, key inicializado.
//Post: Devuelve 0 si se pudo inicializar correctamente, -1 en caso de error.
int vigenere_inicializar(vigenere_t* vigenere, void* key);

//Pre: vigenere inicializado.
//Post: Devuelve mensaje encriptado.
void vigenere_encodear(vigenere_t* vigenere,
						unsigned char* mensaje, size_t largo_mensaje);

//Pre: vigenere inicializado, mensaje debe estar encriptado por vigenere.
//Post: Devuelve mensaje desencriptado.
void vigenere_desencodear(vigenere_t* vigenere,
							unsigned char* mensaje, size_t largo_mensaje);

//Pre: viegenere inicializado.
//Post: Devuelve 0.
int vigenere_destruir(vigenere_t* vigenere);

#endif
