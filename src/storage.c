#include "../include/storage.h"
#include "../include/hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/encryption.h"
#include <sodium.h>
#include <errno.h>

int parse_line(const char *line, PasswordEntry **entry)
{
    *entry = NULL;
    size_t length = strlen(line);

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

   while (line[i] != '\0')
{
    if (line[i] == '\\')
    {
        if (line[i + 1] == '\0'){
            for (int n = 0; n < 4; n++){
                free(fields[n]);
            }
            

            return 0;
        }
             

        if (line[i + 1] == '|' || line[i + 1] == '\\')
        {
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
      if (parse_line(line, &entry) == 0)
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







int storage_save(HashTable *table,
                 const unsigned char *salt,
                 const unsigned char *key)
{
    FILE *file = fopen("passwords.txt", "w");

    if (file == NULL)
    {
        return 0;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
{
    Node *current = table->buckets[i];

    while (current != NULL)
    {
        if(write_field(file,current->entry->service)==0){
           fclose(file);
           return 0;
        }
        if (fputc('|', file) == EOF)
        {
         fclose(file);
         return 0;
        }
           
        if(write_field(file,current->entry->email)==0)
        {
           fclose(file);
           return 0;
        }

        
        if (fputc('|', file) == EOF)
        {
         fclose(file);
         return 0;
        }

        if(write_field(file, current->entry->username)==0)
        {
           fclose(file);
           return 0;
        }

        if (fputc('|', file) == EOF)
        {
         fclose(file);
         return 0;
        }

        if(write_field(file,current->entry->password)==0)
        {
           fclose(file);
           return 0;
        }
        
       
        

        current = current->next;
        if (fputc('\n', file) == EOF)
        {
         fclose(file);
         return 0;
        }
    }
}

   if (ferror(file))
   {
    fclose(file);
    return 0;
    }

  if (fclose(file) == EOF){
    return 0;
  }
    

  return 1;
}



int storage_open(HashTable *table,
                 const char *master_password,
                 unsigned char *salt,
                 unsigned char *key)
{
    unsigned char nonce[crypto_aead_xchacha20poly1305_ietf_NPUBBYTES];

    errno = 0;

    FILE *file = fopen("vault.dat", "rb");





if (errno == ENOENT)
{
    if (encryption_generate_salt(salt) != 0)
    return 0;
    encryption_derive_key(master_password, salt, key)

    if (encryption_derive_key(master_password, salt, key) == -1)
{
    printf("Failed to derive encryption key!\n");
    sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
    return 0;
}
sodium_memzero((void *)master_password, strlen(master_password));
   return 1;
}
else
{
    size_t bytes_read_salt = fread(salt, 1, crypto_pwhash_SALTBYTES, file);

    if (bytes_read_salt != crypto_pwhash_SALTBYTES)
{
    fclose(file);
    return 0;
}

 size_t bytes_read_nonce = fread(nonce, 1, crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, file);

    if (bytes_read_nonce!= crypto_aead_xchacha20poly1305_ietf_NPUBBYTES)
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

if (file_size == -1L)
{
    fclose(file);
    return 0;
}

long ciphertext_size = file_size - crypto_pwhash_SALTBYTES - crypto_aead_xchacha20poly1305_ietf_NPUBBYTES;

if (ciphertext_size < crypto_aead_xchacha20poly1305_ietf_ABYTES)
{
    fclose(file);
    return 0;
}
    
    unsigned char *ciphertext = malloc(ciphertext_size);

    if(ciphertext == NULL)
    {
        fclose(file);
        return 0;
    }
    
   fread(ciphertext, 1, ciphertext_size, file);

    if ( ciphertext_size!= ciphertext)
{
    fclose(file);
    return 0;
}
 size_t bytes_read_ciphertext = fread(ciphertext, 1, (size_t)ciphertext_size, file);
 
 if( bytes_read_ciphertext != (size_t)ciphertext_size )
 {
    free(ciphertext);
    fclose(file);
    return 0;
 }

if (encryption_derive_key(master_password, salt, key) !=-1 )
{
    free(ciphertext);
   sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
    fclose(file);
    return 0;
}

unsigned char *plaintext =NULL;
size_t plaintext_len = 0;

 if(encryption_decrypt(ciphertext,ciphertext_len,key,nonce,&plaintext,&plaintext_len) !=0 )
 {
   free(ciphertext);
   sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
   sodium_memzero(plaintext, plaintext_len);
   fclose(file);
   return 0;

 }

}

}