#include "../include/storage.h"
#include "../include/menu.h"
#include "../include/password.h"
#include "../include/linked_list.h"
#include "../include/hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sodium.h>

void menu(void)
{

    int choice;
    char input[10];
    HashTable *table = hash_table_create();
    char master_password[256];
    
if (table == NULL)
{
    printf("Failed to create Hash Table!\n");
    return;
}



    printf("%s", "Enter Master Password: ");

    if (fgets(master_password, sizeof(master_password), stdin) == NULL)
{
    printf("Failed to read Master Password!\n");
    free(table);
    return;
}

    master_password[strcspn(master_password, "\n")] = '\0';

    if(strlen(master_password) == 0)
    {
        printf("Master Password cannot be empty!\n");
        free(table);
        return;
    }

    unsigned char salt[crypto_pwhash_SALTBYTES];

    unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES];

memset(key, 0, sizeof(key));

if (storage_open(table, master_password, salt, key) != 1)
{
    printf("Failed to open password vault!\n");

    sodium_memzero(master_password, sizeof(master_password));
    sodium_memzero(key, sizeof(key));

    free(table);
    return;
}

sodium_memzero(master_password, sizeof(master_password));

printf("Vault opened successfully!\n");
    

    

   do
   {

   

    printf("========== PASSWORD MANAGER ==========\n");
    printf("1. Add password\n");
    printf("2. Search password\n");
    printf("3. Delete password\n");
    printf("4. List passwords\n");
    printf("5. Exit & Save\n");
    printf("Choose an option: ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);//convert char to int

    

   
    

    switch (choice)
    {
    case 1:{
        {
    PasswordEntry *entry = password_create();
    
    
   int result= hash_table_insert(table, entry);
   if(result==0)
   {
    puts("Service already exists. Try a different name, e.g. google1 instead of google.");
   }
   else
   {
    puts("Your entry was added successfully!");
   }

        }
        

    
    break;
    }
    case 2:
    //  Search password
{
    char service[100];

    printf("Give service name: ");
    fgets(service, sizeof(service), stdin);


    service[strcspn(service, "\n")] = '\0';

    PasswordEntry *result = hash_table_search(table, service);

    
    if (result != NULL)
    {
       
        printf("Email: %s\n", result->email);
        printf("Username: %s\n", result->username);
        printf("Password: %s\n", result->password);
    }
    else
{
    printf("Service not found!\n");
}


}
    
    break;
    case 3:
    //Delete password 
    {
    
    char service[100];

    printf("Give name of service: ");
    fgets(service, 100, stdin);
    service[strcspn(service, "\n")] = '\0';

    int result = hash_table_delete(table, service);

    if(result ==1)
    {
        puts("Password deleted successfully!");
    }
    else
    {
        puts("It wasn't found!");
    }
    
    
    }
    break;

    case 4:
    // List passwords
    puts("");
    hash_table_list(table);


    break;

    case 5:
    // Exit and save
    {
        if (storage_save(table, salt, key) == 1)
    {
        puts("Passwords saved successfully!");
    }
    else
    {
        puts("Failed to save passwords!");
    }

    }
     
    break;

    

    
    default:
     printf("Invalid choice.\n");
        break;
    }

}
   while (choice!= 5);
   sodium_memzero(key, sizeof(key));


}

