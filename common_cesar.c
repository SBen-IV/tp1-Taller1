#include <stdio.h>
#include "common_cesar.h"

static void code(int key, unsigned char* msg, size_t tope){

	for(int i = 0; i < tope; i++) msg[i]=(msg[i]+key)%256;
}

void cesar_encodear(int key, unsigned char* msg, size_t tope){

	code(key, msg, tope);
}

void cesar_desencodear(int key, unsigned char* msg, size_t tope){

	code(key*(-1), msg, tope);
}