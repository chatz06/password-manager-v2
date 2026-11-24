#ifndef STORAGE_H
#define STORAGE_H
#include <stdio.h>
#include <stddef.h>
#include "hash_table.h"

int parse_line(const char *line, size_t line_len, PasswordEntry **entry);

int storage_parse_plaintext(HashTable *table,
                            const unsigned char *plaintext,
                            size_t plaintext_len);

int storage_load(HashTable *table);



int write_field(FILE *file, const char *field);

int storage_save(HashTable *table,
                 const unsigned char *salt,
                 const unsigned char *key);

int storage_open(HashTable *table,
                 const char *master_password,
                 unsigned char *salt,
                 unsigned char *key);



#endif