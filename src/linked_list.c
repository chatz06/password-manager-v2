#include <stdio.h>
#include "../include/password.h"
#include "../include/menu.h"
#include "../include/linked_list.h"
#include <stdlib.h>

Node *node_create(PasswordEntry *entry){
    Node *node = malloc(sizeof(*node));

    node->entry = entry;
    node->next = NULL;

    return node;
}



void list_insert(Node **head, Node *node)
{
    if (*head == NULL)
    {
        *head = node;
    }
    else
    {
        Node *current = *head;

        while ((current->next)!=NULL)
{
    current = current->next;
}
     current->next = node;

    }
}