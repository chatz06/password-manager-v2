
#include "../include/encryption.h"
#include <sodium.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const char *master_password = "TestPassword123!";
    const char *message = "This is a secret message!";

    size_t plaintext_len = strlen(message);
    size_t ciphertext_len = 0;

    size_t decrypted_len = 0;

unsigned char *decrypted = NULL;

unsigned char wrong_key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES];

    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES];
    unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES];

    unsigned char *ciphertext = NULL;

    // Initialize libsodium
    if (encryption_init() != 0)
    {
        printf("Initialization failed!\n");
        return 1;
    }

    // Generate salt
    if (encryption_generate_salt(salt) != 0)
    {
        printf("Salt generation failed!\n");
        return 1;
    }

    // Derive encryption key
    if (encryption_derive_key(master_password, salt, key) != 0)
    {
        printf("Key derivation failed!\n");
        return 1;
    }

    // Encrypt message
    if (encryption_encrypt(
            (const unsigned char *)message,
            plaintext_len,
            key,
            nonce,
            &ciphertext,
            &ciphertext_len
        ) != 0)
    {
        printf("Encryption failed!\n");
        sodium_memzero(key, sizeof(key));
        return 1;
    }

    printf("Encryption successful!\n");
    printf("Plaintext size: %zu bytes\n", plaintext_len);
    printf("Ciphertext size: %zu bytes\n", ciphertext_len);

   if (ciphertext_len != plaintext_len +
    crypto_aead_xchacha20poly1305_ietf_ABYTES)
{
    printf("Ciphertext size verification failed!\n");
    free(ciphertext);
    sodium_memzero(key, sizeof(key));
    return 1;
}


    printf("Ciphertext size verification passed!\n");


    if (encryption_decrypt(
        ciphertext,
        ciphertext_len,
        key,
        nonce,
        &decrypted,
        &decrypted_len
    ) != 0)
{
    printf("Decryption failed!\n");
    free(ciphertext);
    sodium_memzero(key, sizeof(key));
    return 1;
}

printf("Decryption successful!\n");

if (encryption_derive_key("WrongPassword", salt, wrong_key) != 0)
{
    printf("Wrong key derivation failed!\n");
    return 1;
}

unsigned char *wrong_decrypted = NULL;
size_t wrong_decrypted_len = 0;

if (encryption_decrypt(
    ciphertext,
    ciphertext_len,
    wrong_key,
    nonce,
    &wrong_decrypted,
    &wrong_decrypted_len
) == 0)
{
    printf("Security test failed! Wrong password accepted!\n");
    sodium_memzero(wrong_decrypted, wrong_decrypted_len);
    free(wrong_decrypted);
    return 1;
}

printf("Wrong password rejected successfully!\n");

sodium_memzero(wrong_key, sizeof(wrong_key));

if (decrypted_len != plaintext_len ||
    memcmp(decrypted, message, plaintext_len) != 0)
{
    printf("Decrypted message verification failed!\n");
    sodium_memzero(decrypted, decrypted_len);
free(decrypted);
free(ciphertext);
sodium_memzero(key, sizeof(key));
    return 1;
}

printf("Decrypted message verification passed!\n");

sodium_memzero(decrypted, decrypted_len);
free(decrypted);

free(ciphertext);

sodium_memzero(key, sizeof(key));

    return 0;
}
