#ifndef STORAGE_H
#define STORAGE_H
#include <stdio.h>
#include "hash_table.h"
// Include
int parse_line(const char *line, PasswordEntry **entry);

int storage_load(HashTable *table);

int write_field(FILE *file, const char *field);

int storage_save(HashTable *table);





#endif