#ifndef BASE64_H
#define BASE64_H
#include <openssl/bio.h>
#include <openssl/evp.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

class base64
{
public:
    base64();
    char* base64Encode(const unsigned char *buffer, const size_t length);
    int base64Decode(const char *b64message, const size_t length, unsigned char **buffer);
    int calcDecodeLength(const char *b64input, const size_t length);
};

#endif // BASE64_H
