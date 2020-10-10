#include <stdio.h>

void code(unsigned char* msg, int key, size_t tope){

	for(int i = 0; i < tope; i++) msg[i]=(msg[i]+key)%256;
}

void encodear(unsigned char* msg, int key, size_t tope){

	code(msg, key, tope);
}

void desencodear(unsigned char* msg, int key, size_t tope){

	code(msg, key*(-1), tope);
}

/*
int main(int argc, char const *argv[]){
	
	unsigned char msg[19] = "holaz";

	encodear(msg, 250, 5);

	printf("%s\n", msg);

	desencodear(msg, 250, 5);

	printf("%s\n", msg);

	return 0;
}
*/