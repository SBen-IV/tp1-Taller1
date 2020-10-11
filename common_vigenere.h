#ifndef _COMMON_VIGENERE_H_
#define _COMMON_VIGENERE_H_

#include <stddef.h>
#include <string.h>

void vigenere_encodear(unsigned char* key, unsigned char* msg, size_t tope);



void vigenere_desencodear(unsigned char* key, unsigned char* msg, size_t tope);


#endif