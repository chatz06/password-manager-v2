#include "../include/menu.h"
#include "../include/password.h"
#include "../include/linked_list.h"
#include "../include/hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void)
{

    int choice;
    char input[10];
    Node *head = NULL;
    
HashTable *table = hash_table_create();
printf("MENU TABLE: %p\n", (void *)table);
   do
   {

   

    printf("========== PASSWORD MANAGER ==========\n");
    printf("1. Add password\n");
    printf("2. Search password\n");
    printf("3. Delete password\n");
    printf("4. List passwords\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);//convert char to int

    

   
    

    switch (choice)
    {
    case 1:{

    
    PasswordEntry *entry = password_create();
    
    
    hash_table_insert(table, entry);
    

  


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

    break;

    case 4:
    // List passwords


    break;

    case 5:
    // Exit

    break;

    
    default:
     printf("Invalid choice.\n");
        break;
    }

}
   while (choice!= 5);


}

