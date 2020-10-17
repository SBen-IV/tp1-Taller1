#include "common_rc4.h"

#define SUCCESS 0

//Pre: buffer tiene posiciones válidas en i y j.
//Post: Intercambia valores entre buffer[i] y buffer[j].
static void swap(unsigned char* buffer, size_t i, size_t j) {
	unsigned char aux = buffer[i];
	buffer[i] = buffer[j];
	buffer[j] = aux;
}

//Pre: s_box declarado.
//Post: Devuelve s_box inicializado.
static void inicializar_s_box(unsigned char s_box[TAM_S_BOX],
								unsigned char* key, size_t largo_key) {
	size_t i, j;

	for (i = 0; i < TAM_S_BOX; i++) s_box[i] = i;

	for (i = j = 0; i < TAM_S_BOX; i++) {
		j = (j + key[i % largo_key] + s_box[i]) % TAM_S_BOX;
		swap(s_box, i, j);
	}
}

int rc4_inicializar(rc4_t* rc4, void* key) {
	unsigned char *_key = key;
	size_t largo_key = strlen((char*)_key);

	rc4->pos_s_box_1 = rc4->pos_s_box_2 = 0;
	inicializar_s_box(rc4->s_box, _key, largo_key);

	return SUCCESS;
}

static void aplicar_rc4(unsigned char s_box[TAM_S_BOX], size_t* pos_s_box_1,
						size_t* pos_s_box_2, unsigned char* msj,
						size_t tope_msj) {
	size_t i = (*pos_s_box_1), j = (*pos_s_box_2);

	for (size_t k = 0; k < tope_msj; k++){
		i = (i + 1) % TAM_S_BOX;
		j = (j + s_box[i]) % TAM_S_BOX;

		swap(s_box, i, j);

		msj[k] = (msj[k] ^ (s_box[(s_box[i] + s_box[j])
					% TAM_S_BOX]));
	}

	(*pos_s_box_1) = i;
	(*pos_s_box_2) = j;
}

void rc4_encodear(rc4_t* rc4, unsigned char* mensaje, size_t largo_mensaje) {
	aplicar_rc4(rc4->s_box, &(rc4->pos_s_box_1), &(rc4->pos_s_box_2), mensaje,
		largo_mensaje);
}

void rc4_desencodear(rc4_t* rc4, unsigned char* mensaje,
					size_t largo_mensaje) {	
	aplicar_rc4(rc4->s_box, &(rc4->pos_s_box_1), &(rc4->pos_s_box_2), mensaje,
		largo_mensaje);
}

int rc4_destruir(rc4_t* rc4) {
	return SUCCESS;
}
