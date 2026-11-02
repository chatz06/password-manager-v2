#include "../include/password.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PasswordEntry *password_create(void)
{
    PasswordEntry *entry = malloc(sizeof(*entry));
    entry->service = malloc(100 * sizeof(char));
    entry->email = malloc(100 * sizeof(char));
    entry->username = malloc(100 * sizeof(char));
    entry->password = malloc(100 * sizeof(char));

   printf("Give name of service: ");
   fgets(entry->service, 100, stdin);
   entry->service[strcspn(entry->service, "\n")] = '\0';
   printf("Give email: ");
   fgets(entry->email, 100, stdin);
   entry->email[strcspn(entry->email, "\n")] = '\0';
   printf("Give username : ");
   fgets(entry->username, 100, stdin);
   entry->username[strcspn(entry->username, "\n")] = '\0';
   printf("Give password: ");
   fgets(entry->password, 100, stdin);
   entry->password[strcspn(entry->password, "\n")] = '\0';


   return entry;
}