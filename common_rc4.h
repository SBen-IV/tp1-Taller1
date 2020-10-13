#ifndef _COMMON_RC4_
#define _COMMON_RC4_

#include <string.h>
#include <stddef.h>

void rc4_encodear(void* key, size_t* pos_key_1, size_t* pos_key_2,
					unsigned char* buffer, size_t tope);

void rc4_desencodear(void* key, size_t* pos_key_1, size_t* pos_key_2,
					unsigned char* buffer, size_t tope);

#endif
