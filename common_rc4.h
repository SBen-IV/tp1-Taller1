#ifndef _COMMON_RC4_
#define _COMMON_RC4_

#include <string.h>
#include <stddef.h>

#define TAM_S_BOX 256

typedef struct rc4{
	int key;
}rc4_t;

void rc4_inicializar(rc4_t* rc4, void* key);

void rc4_encodear(void* key, size_t* pos_key_1, size_t* pos_key_2,
					unsigned char* buffer, size_t tope,
					unsigned char s_box[TAM_S_BOX]);

void rc4_desencodear(void* key, size_t* pos_key_1, size_t* pos_key_2,
					unsigned char* buffer, size_t tope,
					unsigned char s_box[TAM_S_BOX]);

#endif
