#include "../include/password.h"
#include <stdlib.h>
#include <stdio.h>

PasswordEntry *password_create(void)
{
    PasswordEntry *entry = malloc(sizeof(*entry));
    entry->service = malloc(100 * sizeof(char));
    entry->email = malloc(100 * sizeof(char));
    entry->username = malloc(100 * sizeof(char));
    entry->password = malloc(100 * sizeof(char));

   printf("Give name of service: ");
   fgets(entry->service, 100, stdin);
   printf("Give email: ");
   fgets(entry->email, 100, stdin);
   printf("Give username : ");
   fgets(entry->username, 100, stdin);
   printf("Give password: ");
   fgets(entry->password, 100, stdin);


   return entry;
}