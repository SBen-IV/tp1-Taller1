#include "common_vigenere.h"

void vigenere_encodear(void* key, unsigned char* msg, size_t tope){
	unsigned char* _key = key;

	size_t len_key = strlen((char*)_key);

	for (size_t i = 0, j = 0; i < tope; i++, j++) {
		if (j == len_key) j = 0;
		msg[i] = (msg[i] + _key[j])%256;
	}
}

void vigenere_desencodear(void* key, unsigned char* msg, size_t tope){
	unsigned char* _key = key;

	size_t len_key = strlen((char*)_key);

	for (size_t i = 0, j = 0; i < tope; i++, j++) {
		if (j == len_key) j = 0;
		msg[i] = (msg[i] - _key[j])%256;
	}
}
