#ifndef STORAGE_H
#define STORAGE_H
#include "hash_table.h"
// Include
int parse_line(const char *line, PasswordEntry **entry);

int storage_load(HashTable *table);

int storage_save(HashTable *table);



#endif