#include "cripter.h"

cripter::cripter()
{
    init();
}

cripter::~cripter()
{
    EVP_CIPHER_CTX_cleanup(aesEncryptCtx);
    EVP_CIPHER_CTX_cleanup(aesDecryptCtx);
    free(aesEncryptCtx);
    free(aesDecryptCtx);
    free(aesKey);
    free(aesIV);
}

int cripter::init(void)
{
    aesEncryptCtx = (EVP_CIPHER_CTX*)malloc(sizeof(EVP_CIPHER_CTX));
    aesDecryptCtx = (EVP_CIPHER_CTX*)malloc(sizeof(EVP_CIPHER_CTX));

    // Always a good idea to check if malloc failed
    if(aesEncryptCtx == NULL || aesDecryptCtx == NULL) {
        qDebug() << "fuck1";
        return FAILURE;
    }

    // Init these here to make valgrind happy
    EVP_CIPHER_CTX_init(aesEncryptCtx);
    EVP_CIPHER_CTX_init(aesDecryptCtx);

    // Init AES
    aesKey = (unsigned char*)malloc(AES_KEYLEN/8);
    aesIV = (unsigned char*)malloc(AES_KEYLEN/8);

    unsigned char *aesPass = (unsigned char*)malloc(AES_KEYLEN/8);
    unsigned char *aesSalt = (unsigned char*)malloc(8);

    if(aesKey == NULL || aesIV == NULL || aesPass == NULL || aesSalt == NULL) {
        qDebug() << "fuck2";
        return FAILURE;
    }

    if(RAND_bytes(aesKey, AES_KEYLEN/8) == 0) {
        qDebug() << "fuck3";
        return FAILURE;
    }

    if(RAND_bytes(aesIV, AES_KEYLEN/8) == 0) {
        qDebug() << "fuck4";
        return FAILURE;
    }

    free(aesPass);
    free(aesSalt);
    return SUCCESS;
}


int cripter::aesEncrypt(const unsigned char *msg, size_t msgLen, unsigned char **encMsg) {
    size_t blockLen  = 0;
    size_t encMsgLen = 0;

    *encMsg = (unsigned char*)malloc(msgLen + AES_BLOCK_SIZE);
    if(encMsg == NULL) return FAILURE;

    if(!EVP_EncryptInit_ex(aesEncryptCtx, EVP_aes_256_cbc(), NULL, aesKey, aesIV)) {
        return FAILURE;
    }

    if(!EVP_EncryptUpdate(aesEncryptCtx, *encMsg, (int*)&blockLen, (unsigned char*)msg, msgLen)) {
        return FAILURE;
    }
    encMsgLen += blockLen;

    if(!EVP_EncryptFinal_ex(aesEncryptCtx, *encMsg + encMsgLen, (int*)&blockLen)) {
        return FAILURE;
    }

    EVP_CIPHER_CTX_cleanup(aesEncryptCtx);
    return encMsgLen + blockLen;
}

int cripter::aesDecrypt(unsigned char *encMsg, size_t encMsgLen, unsigned char **decMsg) {
    size_t decLen   = 0;
    size_t blockLen = 0;

    *decMsg = (unsigned char*)malloc(encMsgLen);
    if(*decMsg == NULL) return FAILURE;

    if(!EVP_DecryptInit_ex(aesDecryptCtx, EVP_aes_256_cbc(), NULL, aesKey, aesIV)) {
        return FAILURE;
    }

    if(!EVP_DecryptUpdate(aesDecryptCtx, (unsigned char*)*decMsg, (int*)&blockLen, encMsg, (int)encMsgLen)) {
        return FAILURE;
    }
    decLen += blockLen;

    if(!EVP_DecryptFinal_ex(aesDecryptCtx, (unsigned char*)*decMsg + decLen, (int*)&blockLen)) {
        return FAILURE;
    }
    decLen += blockLen;

    EVP_CIPHER_CTX_cleanup(aesDecryptCtx);

    return (int)decLen;
}

int cripter::getAESKey(unsigned char **aesKey) {
    *aesKey = this->aesKey;
    return AES_KEYLEN/8;
}

int cripter::setAESKey(unsigned char *aesKey, size_t aesKeyLen) {
    // Ensure the new key is the proper size
    if((int)aesKeyLen != AES_KEYLEN/8) {
        return FAILURE;
    }
    memcpy(this->aesKey, aesKey, AES_KEYLEN/8);
    return SUCCESS;
}

int cripter::getAESIv(unsigned char **aesIV) {
    *aesIV = this->aesIV;
    return AES_KEYLEN/16;
}

int cripter::setAESIv(unsigned char *aesIV, size_t aesIVLen) {
    // Ensure the new IV is the proper size
    if((int)aesIVLen != AES_KEYLEN/16) {
        return FAILURE;
    }

    memcpy(this->aesIV, aesIV, AES_KEYLEN/16);

    return SUCCESS;
}
