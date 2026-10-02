#include "../include/menu.h"
#include "../include/password.h"
#include "../include/linked_list.h"
#include <stdio.h>
#include <stdlib.h>

void menu(void)
{

    int choice;
    char input[10];
    Node *head = NULL;
    

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

    
    PasswordEntry *entry = password_create();//τωρα κραταω και ονομα στο entry
    Node *node = node_create(entry);
    list_insert(&head, node);

  


    break;
    }
    case 2:
    //  Search password

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

