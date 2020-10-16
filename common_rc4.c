#include "common_rc4.h"

static void swap(unsigned char* string, size_t i, size_t j) {
	unsigned char aux = string[i];
	string[i] = string[j];
	string[j] = aux;
}

void rc4_inicializar(unsigned char s_box[TAM_S_BOX], void* key) {
	unsigned char *_key = key;
	size_t largo_key = strlen((char*)_key);
	size_t i, j;

	for (i = 0; i < TAM_S_BOX; i++) s_box[i] = i;

	for (i = j = 0; i < TAM_S_BOX; i++) {
		j = (j + _key[i % largo_key] + s_box[i]) % TAM_S_BOX;
		swap(s_box, i, j);
	}
}

static void code(unsigned char* s_box, size_t* pos_key_1, size_t* pos_key_2,
					unsigned char* buffer, size_t tope) {
	size_t i = (*pos_key_1), j = (*pos_key_2);

	for (size_t k = 0; k < tope; k++){
		i = (i + 1) % TAM_S_BOX;
		j = (j + s_box[i]) % TAM_S_BOX;

		swap(s_box, i, j);

		buffer[k] = (buffer[k] ^ (s_box[(s_box[i] + s_box[j])
					% TAM_S_BOX]));
	}

	(*pos_key_1) = i;
	(*pos_key_2) = j;
}

void rc4_encodear(void* key, size_t* pos_key_1, size_t* pos_key_2,
 					unsigned char* buffer, size_t tope,
 					unsigned char s_box[TAM_S_BOX]) {
	code(s_box, pos_key_1, pos_key_2, buffer, tope);
}

void rc4_desencodear(void* key, size_t* pos_key_1, size_t* pos_key_2,
 					unsigned char* buffer, size_t tope,
 					unsigned char s_box[TAM_S_BOX]) {	
	code(s_box, pos_key_1, pos_key_2, buffer, tope);
}
