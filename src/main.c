#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/password.h"
#include "../include/menu.h"
#include "../include/linked_list.h"
#include "../include/hash_table.h"

int main(void)
{
    //menu();

     HashTable *table = hash_table_create();

    PasswordEntry *entry1 = malloc(sizeof(*entry1));
    PasswordEntry *entry2 = malloc(sizeof(*entry2));

    entry1->service = malloc(100 * sizeof(char));
    entry2->service = malloc(100 * sizeof(char));
    strcpy(entry1->service, "Google");
     strcpy(entry2->service, "oogleG");

    entry1->email = NULL;
    entry1->username = NULL;
    entry1->password = NULL;
    entry2->email = NULL;
    entry2->username = NULL;
    entry2->password = NULL;

    hash_table_insert(table, entry1);
     hash_table_insert(table, entry2);

    int index = hash_service("Google");

    printf("Bucket: %d\n", index);
    printf("Stored service: %s\n",
           table->buckets[index]->entry->service);
           printf("Second service: %s\n",
       table->buckets[index]->next->entry->service);


    return 0;
}