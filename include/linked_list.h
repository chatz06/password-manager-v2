
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "password.h"

typedef struct Node {
    PasswordEntry *entry;
    struct Node *next;
} Node;

Node *node_create(PasswordEntry *entry);

void list_insert(Node **head, Node *node);

#endif