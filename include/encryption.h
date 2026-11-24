#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stddef.h>


int encryption_init(void);

int encryption_derive_key(const char *master_password, const unsigned char *salt, unsigned char *key);

int encryption_generate_salt(unsigned char *salt);

int encryption_encrypt(
    const unsigned char *plaintext,
    size_t plaintext_len,
    const unsigned char *key,
    unsigned char *nonce,
    unsigned char **ciphertext,
    size_t *ciphertext_len
);

int encryption_decrypt(
    const unsigned char *ciphertext,
    size_t ciphertext_len,
    const unsigned char *key,
    const unsigned char *nonce,
    unsigned char **plaintext,
    size_t *plaintext_len
);

#endif