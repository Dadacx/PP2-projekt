#ifndef PP_PROJEKT_LIST_H
#define PP_PROJEKT_LIST_H
#include "structs.h"
#include  <stdbool.h>

DoublyLinkedList CreateList();
void push_back(DoublyLinkedList* list, Contact data);
void pop_back(DoublyLinkedList* list);
void remove_node(DoublyLinkedList* list, Node* node);
void clear(DoublyLinkedList* list);
bool is_empty(DoublyLinkedList* list);
int size(DoublyLinkedList* list);
void print(DoublyLinkedList *list, void (*print_func)(Contact));

#endif //PP_PROJEKT_LIST_H