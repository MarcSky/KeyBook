#ifndef CRIPTER_H
#define CRIPTER_H
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <QDebug>
#include <stdio.h>
#include <string>
#include <string.h>

#define AES_KEYLEN 256
#define AES_ROUNDS 6
#define SUCCESS 1
#define FAILURE 0
#define KEY_AES        3
#define KEY_AES_IV     4

class cripter
{
public:
    cripter();
    ~cripter();
    int aesEncrypt(const unsigned char *msg, size_t msgLen, unsigned char **encMsg);
    int aesDecrypt(unsigned char *encMsg, size_t encMsgLen, unsigned char **decMsg);
    int getAESKey(unsigned char **aesKey);
    int setAESKey(unsigned char *aesKey, size_t aesKeyLen);
    int getAESIv(unsigned char **aesIv);
    int setAESIv(unsigned char *aesIv, size_t aesIvLen);

private:
    EVP_CIPHER_CTX *aesEncryptCtx;
    EVP_CIPHER_CTX *aesDecryptCtx;
    unsigned char *aesKey;
    unsigned char *aesIV;
    int init(void);
};

#endif // CRIPTER_H
