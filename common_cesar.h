#ifndef _COMMON_CESAR_H_
#define _COMMON_CESAR_H_

typedef struct cesar{
	int key;
}cesar_t;

//Pre: cesar declarado, key inicializado.
//Post: Devuelve 0 si se pudo inicializar correctamente, -1 en caso de error.
int cesar_inicializar(cesar_t* cesar, void* key);

//Pre: cesar inicializado.
//Post: Devuelve mensaje encriptado.
void cesar_encodear(cesar_t* cesar, unsigned char* mensaje,
					size_t largo_mensaje);

//Pre: cesar inicializado, mensaje debe estar encriptado por cesar.
//Post: Devuelve mensaje desencriptado.
void cesar_desencodear(cesar_t* cesar, unsigned char* mensaje,
						size_t largo_mensaje);

//Pre: cesar inicializado.
//Post: Devuelve 0.
int cesar_destruir(cesar_t* cesar);

#endif
