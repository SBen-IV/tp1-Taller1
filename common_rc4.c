#include "common_rc4.h"

#define TAM_S_BOX 256

static void swap(unsigned char* string, size_t i, size_t j) {

	unsigned char aux = string[i];
	string[i] = string[j];
	string[j] = aux;
}

static void inicializar(unsigned char s_box[], unsigned char* key,
					size_t largo_key) {

	size_t i, j;

	for (i = 0; i < TAM_S_BOX; i++) s_box[i] = i;

	for (i = j = 0; i < TAM_S_BOX; i++) {
		j = (j + key[i % largo_key] + s_box[i]) & (TAM_S_BOX - 1);
		swap(s_box, i, j);
	}
}

static void code(unsigned char* s_box, unsigned char* buffer, size_t tope) {

	size_t i, j;

	i = j = 0;

	for (size_t k = 0; k < tope; k++){
		i = (i + 1) & (TAM_S_BOX - 1);
		j = (j + s_box[i]) & (TAM_S_BOX - 1);

		swap(s_box, i, j);

		buffer[k] = (buffer[k] ^ (s_box[(s_box[i] + s_box[j]) & (TAM_S_BOX - 1)]));
	}
}


void rc4_encodear(unsigned char* key, unsigned char* buffer, size_t tope) {

	unsigned char s_box[TAM_S_BOX];

	inicializar(s_box, key, strlen((char*)key));

	code(s_box, buffer, tope);
}

void rc4_desencodear(unsigned char* key, unsigned char* buffer, size_t tope) {

	unsigned char s_box[TAM_S_BOX];

	inicializar(s_box, key, strlen((char*)key));
	
	code(s_box, buffer, tope);
}