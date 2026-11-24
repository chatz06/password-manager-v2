#include "../include/storage.h"
#include "../include/hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/encryption.h"
#include <sodium.h>
#include <errno.h>

int parse_line(const char *line, size_t line_len, PasswordEntry **entry)
{
    *entry = NULL;
    size_t length = line_len;

    char *fields[4] = {NULL, NULL, NULL, NULL};

    int field_count = 0;

    size_t i = 0;
    size_t j = 0;
    for (int k = 0; k < 4; k++)
   {
   fields[k] = malloc(length + 1);




    if (fields[k] == NULL)
    {
        for (int n = 0; n < k; n++){
            free(fields[n]);
        }
        


        return 0;

    }
        
    }

   while (i < line_len)
{
    if (line[i] == '\\')
    {
        if (i + 1 >= line_len) {
            for (int n = 0; n < 4; n++){
                free(fields[n]);
            }
            

            return 0;
        }
             

        if (line[i + 1] == '|' || line[i + 1] == '\\')
        {

            if (field_count >= 4){
                return 0;
            }
             

            fields[field_count][j] = line[i + 1];

             i += 2;
             j++;
        }
        else
        {
            for (int n = 0; n < 4; n++){
                free(fields[n]);
            }
            return 0;
        }
        
    }
    else if (line[i] == '|')
     {
        if (field_count >= 3)
         {
           for (int n = 0; n < 4; n++){
            free(fields[n]);
           
           }
            

    return 0;
          }
       fields[field_count][j] = '\0';
       field_count++;
       j = 0;
       i++;
    }
    else
     {
    fields[field_count][j] = line[i];
    j++;
    i++;
     }

     

}
fields[field_count][j] = '\0';

if (field_count != 3){
    for (int n = 0; n < 4; n++){
            free(fields[n]);
        }
        return 0;
}

    

    *entry = malloc(sizeof(PasswordEntry));

      if (*entry == NULL){

      for (int n = 0; n < 4; n++){
            free(fields[n]);
        }
        return 0;
    }

        

    (*entry)->service=fields[0];
    (*entry)->email=fields[1];
    (*entry)->username=fields[2];
    (*entry)->password=fields[3];

  
  return 1;
}

int storage_parse_plaintext(HashTable *table,
                            const unsigned char *plaintext,
                            size_t plaintext_len)
{
    size_t start = 0;
    size_t i = 0;

    while (i < plaintext_len)
{
    if (plaintext[i] == '\n')
{
    size_t line_len = i - start;

    PasswordEntry *entry = NULL;

if (parse_line((const char *)&plaintext[start],line_len,&entry) == 0)
{
    return 1;
}

if (hash_table_insert(table, entry) == 0)
{
    free(entry->service);
    free(entry->email);
    free(entry->username);
    free(entry->password);
    free(entry);

    return 1;
}

    start = i +1;

}

    i++;
}

if (start < plaintext_len)
{
    size_t line_len = plaintext_len - start;

    PasswordEntry *entry = NULL;

if (parse_line((const char *)&plaintext[start],line_len, &entry) == 0)
{
    return 1;
}

if (hash_table_insert(table, entry) == 0)
{
    free(entry->service);
    free(entry->email);
    free(entry->username);
    free(entry->password);
    free(entry);

    return 1;
}

}

return 0;
}


int storage_load(HashTable *table)
{
    FILE *file = fopen("passwords.txt", "r");



    if (file == NULL)
{
    
    file = fopen("passwords.txt", "w");

    if (file == NULL)
        return 0;

    fclose(file);
    return 1;
}

    char line[500];

while (fgets(line, sizeof(line), file) != NULL)
{
      line[strcspn(line, "\n")] = '\0';

      PasswordEntry *entry = NULL;
      if (parse_line(line,strlen(line), &entry) == 0)
       {
        fclose(file);
        return 0;
       }

       

       if (hash_table_insert(table, entry) == 0)
       { 
    free(entry->service);
    free(entry->email);
    free(entry->username);
    free(entry->password);
    free(entry);
       }
    
}
   if (ferror(file))
    {
    fclose(file);
    return 0;
    }

fclose(file);
return 1;

}
int write_field(FILE *file, const char *field)
{
    size_t i = 0;

    while (field[i] != '\0')
    {
        if((field[i]=='|') || (field[i]=='\\')){
            if(fputc('\\', file) == EOF)
            {
                return 0;
            }
        }

        if(fputc(field[i], file)== EOF)
        {
            return 0;
        }
        

        i++;
    }
    return 1;
}


static int buffer_append(
    unsigned char **buffer,
    size_t *length,
    size_t *capacity,
    unsigned char byte
)
{
    if (*length == *capacity)
    {
        size_t new_capacity;

    if (*capacity == 0)
     {
    new_capacity = 256;
     }
     else
     {
    new_capacity = *capacity * 2;
     }

        if (new_capacity < *capacity)
            return 0;

        unsigned char *temp = realloc(*buffer, new_capacity);

        if (temp == NULL)
            return 0;

        *buffer = temp;
        *capacity = new_capacity;
    }

    (*buffer)[*length] = byte;
    (*length)++;

    return 1;
}


static int buffer_append_field(
    unsigned char **buffer,
    size_t *length,
    size_t *capacity,
    const char *field
)
{
    size_t i = 0;

    while (field[i] != '\0')
    {
        if (field[i] == '|' || field[i] == '\\')
        {
            if (buffer_append(buffer, length, capacity, '\\') == 0)
                return 0;
        }

        if (buffer_append(buffer, length, capacity, field[i]) == 0)
            return 0;

        i++;
    }

    return 1;
}








int storage_save(
    HashTable *table,
    const unsigned char *salt,
    const unsigned char *key
)
{
    unsigned char *buffer = NULL;

    size_t length = 0;
    size_t capacity = 0;

    unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES];

    unsigned char *ciphertext = NULL;
    size_t ciphertext_len = 0;

    FILE *file = NULL;

    int temp_file_created = 0;
    int success = 0;

   

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = table->buckets[i];

        while (current != NULL)
        {
            PasswordEntry *entry = current->entry;

            if (buffer_append_field(&buffer, &length, &capacity, entry->service) == 0)
                goto cleanup;

            if (buffer_append(&buffer, &length, &capacity, '|') == 0)
                goto cleanup;

            if (buffer_append_field(&buffer, &length, &capacity, entry->email) == 0)
                goto cleanup;

            if (buffer_append(&buffer, &length, &capacity, '|') == 0)
                goto cleanup;

            if (buffer_append_field(&buffer, &length, &capacity, entry->username) == 0)
                goto cleanup;

            if (buffer_append(&buffer, &length, &capacity, '|') == 0)
                goto cleanup;

            if (buffer_append_field(&buffer, &length, &capacity, entry->password) == 0)
                goto cleanup;

            if (buffer_append(&buffer, &length, &capacity, '\n') == 0)
                goto cleanup;

            current = current->next;
        }
    }

    

    const unsigned char *plaintext = buffer;

    if (plaintext == NULL)
        plaintext = (const unsigned char *)"";

    if (encryption_encrypt(
            plaintext,
            length,
            key,
            nonce,
            &ciphertext,
            &ciphertext_len
        ) != 0)
    {
        goto cleanup;
    }


    file = fopen("vault.tmp", "wb");

    if (file == NULL)
        goto cleanup;

    temp_file_created = 1;

    

    if (fwrite(salt, 1, crypto_pwhash_SALTBYTES, file)
        != crypto_pwhash_SALTBYTES)
    {
        goto cleanup;
    }

    

    if (fwrite(nonce, 1, crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, file)
        != crypto_aead_xchacha20poly1305_ietf_NPUBBYTES)
    {
        goto cleanup;
    }

    

    if (fwrite(ciphertext, 1, ciphertext_len, file) != ciphertext_len)
        goto cleanup;

    

    int close_result = fclose(file);
    file = NULL;

    if (close_result == EOF)
        goto cleanup;

    

    if (rename("vault.tmp", "vault.dat") != 0)
        goto cleanup;

    temp_file_created = 0;

    success = 1;

cleanup:

    if (file != NULL)
        fclose(file);

    if (temp_file_created)
        remove("vault.tmp");

    if (buffer != NULL)
    {
        sodium_memzero(buffer, length);
        free(buffer);
    }

    if (ciphertext != NULL)
        free(ciphertext);

    return success;
}


int storage_open(
    HashTable *table,
    const char *master_password,
    unsigned char *salt,
    unsigned char *key
)
{
    unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES];

    errno = 0;

    FILE *file = fopen("vault.dat", "rb");

    

    if (file == NULL && errno == ENOENT)
    {
        if (encryption_generate_salt(salt) != 0)
            return 0;

        if (encryption_derive_key(master_password, salt, key) == -1)
        {
            sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
            return 0;
        }

        return 1;
    }

    

    if (file == NULL)
        return 0;


    if (fread(salt, 1, crypto_pwhash_SALTBYTES, file)
        != crypto_pwhash_SALTBYTES)
    {
        fclose(file);
        return 0;
    }

    

    if (fread(nonce, 1, crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, file)
        != crypto_aead_xchacha20poly1305_ietf_NPUBBYTES)
    {
        fclose(file);
        return 0;
    }

    

    if (fseek(file, 0, SEEK_END) != 0)
    {
        fclose(file);
        return 0;
    }

    long file_size = ftell(file);

    if (file_size < 0)
    {
        fclose(file);
        return 0;
    }

    long ciphertext_size = file_size
        - crypto_pwhash_SALTBYTES
        - crypto_aead_xchacha20poly1305_ietf_NPUBBYTES;

    if (ciphertext_size < crypto_aead_xchacha20poly1305_ietf_ABYTES)
    {
        fclose(file);
        return 0;
    }

    

    size_t ciphertext_len = (size_t)ciphertext_size;

    unsigned char *ciphertext = malloc(ciphertext_len);

    if (ciphertext == NULL)
    {
        fclose(file);
        return 0;
    }

    

    if (fseek(file,
              crypto_pwhash_SALTBYTES +
              crypto_aead_xchacha20poly1305_ietf_NPUBBYTES,
              SEEK_SET) != 0)
    {
        free(ciphertext);
        fclose(file);
        return 0;
    }

    if (fread(ciphertext, 1, ciphertext_len, file) != ciphertext_len)
    {
        free(ciphertext);
        fclose(file);
        return 0;
    }

    if (fclose(file) == EOF)
    {
        free(ciphertext);
        return 0;
    }

    

    if (encryption_derive_key(master_password, salt, key) == -1)
    {
        free(ciphertext);
        sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
        return 0;
    }

    

    unsigned char *plaintext = NULL;
    size_t plaintext_len = 0;

    if (encryption_decrypt(
            ciphertext,
            ciphertext_len,
            key,
            nonce,
            &plaintext,
            &plaintext_len
        ) != 0)
    {
        free(ciphertext);
        sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
        return 0;
    }

    free(ciphertext);

    

    if (storage_parse_plaintext(table, plaintext, plaintext_len) != 0)
    {
        sodium_memzero(plaintext, plaintext_len);
        free(plaintext);
        sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
        return 0;
    }

    sodium_memzero(plaintext, plaintext_len);
    free(plaintext);

    return 1;
}

