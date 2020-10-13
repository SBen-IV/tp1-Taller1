#include "common_vigenere.h"

void vigenere_encodear(void* key, size_t* pos_key,
						unsigned char* msg, size_t tope){
	unsigned char* _key = key;

	size_t len_key = strlen((char*)_key), j = (*pos_key);

	for (size_t i = 0; i < tope; i++, j++) {
		if (j == len_key) j = 0;
		msg[i] = (msg[i] + _key[j])%256;
	}

	(*pos_key) = j;
}

void vigenere_desencodear(void* key, size_t* pos_key,
						unsigned char* msg, size_t tope){
	unsigned char* _key = key;

	size_t len_key = strlen((char*)_key), j = (*pos_key);

	for (size_t i = 0; i < tope; i++, j++) {
		if (j == len_key) j = 0;
		msg[i] = (msg[i] - _key[j])%256;
	}

	(*pos_key) = j;
}
