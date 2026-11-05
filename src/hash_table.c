#include "../include/hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


HashTable *hash_table_create(void)
{
    HashTable *table = malloc(sizeof(*table));

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table->buckets[i] = NULL;
    }

    return table;
}


int hash_service(const char *service)
{
    int hash = 0;

  for (int i = 0; service[i] != '\0'; i++)
  {

    char c = service[i];
    hash+=c;

  }

  hash %=TABLE_SIZE;
    

return hash;
}

void hash_table_insert(HashTable *table, PasswordEntry *entry)
{
    
    int index = hash_service(entry->service);

    Node *node = node_create(entry);

    list_insert(&table->buckets[index], node);
    
}

PasswordEntry *hash_table_search(HashTable *table, const char *service)
{

int index = hash_service(service);

     Node *current = table->buckets[index];
   
         while (current != NULL)
    {
      
        if (strcmp(current->entry->service, service) == 0)
        {
             return current->entry;

        }

        current = current->next;
    }

    return NULL;
}
    
void hash_table_list(HashTable *table)
{
  for (int i = 0; i < TABLE_SIZE; i++)
   {
    Node *current = table->buckets[i];

    while (current!=NULL)
    {
        printf("Service: %s\n", current->entry->service);
        printf("Email: %s\n", current->entry->email);
        printf("Username: %s\n", current->entry->username);
        printf("Password: %s\n", current->entry->password);

        printf("-----------------------------\n");
        current= current->next;
        
    }
    
   }
}
