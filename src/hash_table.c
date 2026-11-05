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

int hash_table_insert(HashTable *table, PasswordEntry *entry)
{
   if((hash_table_search(table,entry->service)) != NULL ) {
    return 0;

    
   }
   int index = hash_service(entry->service);

    Node *node = node_create(entry);

    list_insert(&table->buckets[index], node);
    
    return 1;
    
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


int hash_table_delete(HashTable *table, const char *service)
{
     int flag =0;
     Node *previous = NULL;
    int i =hash_service(service);

    
    Node *current = table->buckets[i];
    

    while ((current!=NULL) && (flag==0))
    {
        if (strcmp(current->entry->service, service) == 0)
        {
            if(previous == NULL)
            {
                table->buckets[i]=current->next;

            }
            else if (current->next != NULL)
            {
                previous->next=current->next;


            }
            else
            {
                previous->next=NULL;

            }
            
            

            free(current->entry->service);
            free(current->entry->email);
            free(current->entry->username);
            free(current->entry->password);

            flag=1;

        }

        previous= current;
        current= current->next;
        
    }
    
   return flag;
}