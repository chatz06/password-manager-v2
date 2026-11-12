#include "../include/encryption.h"
#include <sodium.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>


int encryption_init(void)
{
  if (sodium_init() < 0)
  {
    return -1;
  }
  return 0;
}

int encryption_generate_salt(unsigned char *salt){

randombytes_buf(salt, crypto_pwhash_SALTBYTES);

  return 0;
}

int encryption_derive_key(const char *master_password, const unsigned char *salt, unsigned char *key){

    
    if (crypto_pwhash(
        key,
        crypto_aead_xchacha20poly1305_ietf_KEYBYTES,
        master_password,
        strlen(master_password),
        salt,
        crypto_pwhash_OPSLIMIT_INTERACTIVE,
        crypto_pwhash_MEMLIMIT_INTERACTIVE,
        crypto_pwhash_ALG_ARGON2ID13
    ) != 0)
    {
      return -1;
    }
        
    





    return 0;
}

int encryption_encrypt(
    const unsigned char *plaintext,
    size_t plaintext_len,
    const unsigned char *key,
    unsigned char *nonce,
    unsigned char **ciphertext,
    size_t *ciphertext_len
)
{
    if (plaintext == NULL || key == NULL ||
    nonce == NULL || ciphertext == NULL ||
    ciphertext_len == NULL)
{
    return -1;
}

    randombytes_buf(nonce, crypto_aead_xchacha20poly1305_ietf_NPUBBYTES);

    *ciphertext = malloc( plaintext_len + crypto_aead_xchacha20poly1305_ietf_ABYTES);

    if (*ciphertext == NULL)
    {
    return -1;
    }

    unsigned long long encrypted_len;

    if (crypto_aead_xchacha20poly1305_ietf_encrypt(
        *ciphertext,
        &encrypted_len,
        plaintext,
        (unsigned long long) plaintext_len,
        NULL,
        0,
        NULL,
        nonce,
        key
    ) != 0)
{
    free(*ciphertext);
    *ciphertext = NULL;
    return -1;
}

*ciphertext_len = (size_t) encrypted_len;

  return 0;
}