#include "common_vigenere.h"

#define SUCCESS 0

#define TAM_ABECEDARIO 256

int vigenere_inicializar(vigenere_t* vigenere, void* key) {
	vigenere->key = key;
	vigenere->largo_key = strlen((char*)vigenere->key);
	vigenere->pos_key = 0;

	return SUCCESS;
}

void vigenere_encodear(vigenere_t* vigenere, unsigned char* mensaje,
						size_t largo_mensaje) {
	for (size_t i = 0; i < largo_mensaje; i++, vigenere->pos_key++) {
		if (vigenere->pos_key == vigenere->largo_key) vigenere->pos_key = 0;

		mensaje[i] = (mensaje[i] + vigenere->key[vigenere->pos_key])
						% TAM_ABECEDARIO;
	}
}

void vigenere_desencodear(vigenere_t* vigenere,	unsigned char* mensaje,
						size_t largo_mensaje) {
	for (size_t i = 0; i < largo_mensaje; i++, vigenere->pos_key++) {
		if (vigenere->pos_key == vigenere->largo_key) vigenere->pos_key = 0;

		mensaje[i] = (mensaje[i] - vigenere->key[vigenere->pos_key])
						% TAM_ABECEDARIO;
	}
}

int vigenere_destruir(vigenere_t* vigenere) {
	return SUCCESS;
}
