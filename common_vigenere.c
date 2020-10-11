#include "common_vigenere.h"

void vigenere_encodear(unsigned char* key, unsigned char* msg, size_t tope){

	size_t len_key = strlen((char*)key), j = 0;

	for (size_t i = 0; i < tope; i++, j++) {
		if (j == len_key) j = 0;
		msg[i] = (msg[i] + key[j])%256;
	}
}



void vigenere_desencodear(unsigned char* key, unsigned char* msg, size_t tope){

	size_t len_key = strlen((char*)key), j = 0;

	for (size_t i = 0; i < tope; i++, j++) {
		if (j == len_key) j = 0;
		msg[i] = (msg[i] - key[j])%256;
	}
}

