#ifndef _COMMON_CESAR_H_
#define _COMMON_CESAR_H_

typedef struct cesar{
	int key;
}cesar_t;

int cesar_inicializar(cesar_t* cesar, void* key);

void cesar_encodear(cesar_t* cesar, unsigned char* mensaje,
					size_t largo_mensaje);

void cesar_desencodear(cesar_t* cesar, unsigned char* mensaje,
						size_t largo_mensaje);

int cesar_destruir(cesar_t* cesar);

#endif
