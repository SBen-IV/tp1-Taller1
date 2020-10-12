#ifndef _COMMON_RC4_
#define _COMMON_RC4_

#include <string.h>
#include <stddef.h>

void rc4_encodear(void* key, unsigned char* buffer, size_t tope);

void rc4_desencodear(void* key, unsigned char* buffer, size_t tope);

#endif