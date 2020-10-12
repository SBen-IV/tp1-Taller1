#include <stdio.h>
#include <stdlib.h>
#include "common_cesar.h"

static void code(int key, unsigned char* msg, size_t tope){

	for(int i = 0; i < tope; i++) msg[i]=(msg[i]+key)%256;
}

void cesar_encodear(void* key, unsigned char* msg, size_t tope){

	int _key = atoi((char*)key);

	code(_key, msg, tope);
}

void cesar_desencodear(void* key, unsigned char* msg, size_t tope){

	int _key = atoi((char*)key);

	code(_key*(-1), msg, tope);
}