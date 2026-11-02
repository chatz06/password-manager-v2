#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../include/linked_list.h"
#define TABLE_SIZE 20


typedef struct {
    Node *buckets[TABLE_SIZE];
} HashTable;

void hash_table_insert(HashTable *table, PasswordEntry *entry);

HashTable *hash_table_create(void);

int hash_service(const char *service);

#endif