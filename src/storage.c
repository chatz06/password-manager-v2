#include "../include/storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_line(const char *line, PasswordEntry **entry)
{
    size_t length = strlen(line);

    char *fields[4] = {NULL, NULL, NULL, NULL};

    int field_count = 0;

    size_t i = 0;
    size_t j = 0;
    for (int k = 0; k < 4; k++)
   {
    fields[k] = malloc(strlen(line) + 1);

    if (fields[k] == NULL)
    {
        return 0;

    }
        
    }

   while (line[i] != '\0')
{
    if (line[i] == '\\')
    {
        if (line[i + 1] == '\0')
            return 0;

        if (line[i + 1] == '|' || line[i + 1] == '\\')
        {
            fields[field_count][j] = line[i + 1];

             i += 2;
             j++;
        }
        else
        {
            return 0;
        }
        
    }
    else if (line[i] == '|')
     {
       fields[field_count][j] = '\0';
       field_count++;
       j = 0;
       i++;
    }
    else
     {
    fields[field_count][j] = line[i];
    j++;
    i++;
     }

     fields[field_count][j] = '\0';

}


}

int storage_load(HashTable *table)
{
    FILE *file = fopen("passwords.txt", "r");



    if (file == NULL)
{
    
    file = fopen("passwords.txt", "w");

    if (file == NULL)
        return 0;

    fclose(file);
    return 1;
}

    char line[500];

while (fgets(line, sizeof(line), file) != NULL)
{
    
}


}

int storage_save(HashTable *table)
{


}