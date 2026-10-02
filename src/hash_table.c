#include "../include/hash_table.h"
#include <stdlib.h>


HashTable *hash_table_create(void)
{
    HashTable *table = malloc(sizeof(*table));

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table->buckets[i] = NULL;
    }

    return table;
}