#include <stdio.h>
#include "../include/password.h"
#include "../include/menu.h"
#include "../include/linked_list.h"
#include "../include/hash_table.h"

int main(void)
{
    //menu();

    int result = hash_service("Google");

    printf("Bucket: %d\n", result);


    return 0;
}