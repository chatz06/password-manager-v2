#include <stdio.h>
#include "../include/password.h"
#include "../include/menu.h"
#include "../include/linked_list.h"

Node *node_create(PasswordEntry *entry){
    Node *node = malloc(sizeof(*node));

    node->entry = entry;
    node->next = NULL;// κενο επειδη τωρα διμιηργηθηκε

    return node;
}