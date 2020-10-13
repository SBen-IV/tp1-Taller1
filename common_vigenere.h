#ifndef _COMMON_VIGENERE_H_
#define _COMMON_VIGENERE_H_

#include <stddef.h>
#include <string.h>

void vigenere_encodear(void* key, size_t* pos_key,
						unsigned char* msg, size_t tope);

void vigenere_desencodear(void* key, size_t* pos_key,
							unsigned char* msg, size_t tope);

#endif
