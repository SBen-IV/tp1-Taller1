#ifndef _COMMON_VIGENERE_H_
#define _COMMON_VIGENERE_H_

#include <stddef.h>
#include <string.h>

typedef struct vigenere{
	unsigned char* key;
	size_t largo_key;
	size_t pos_key;
}vigenere_t;

int vigenere_inicializar(vigenere_t* vigenere, void* key);

void vigenere_encodear(vigenere_t* vigenere,
						unsigned char* mensaje, size_t largo_mensaje);

void vigenere_desencodear(vigenere_t* vigenere,
							unsigned char* mensaje, size_t largo_mensaje);

int vigenere_destruir(vigenere_t* vigenere);

#endif
