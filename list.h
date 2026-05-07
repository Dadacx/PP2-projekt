#ifndef PP_PROJEKT_LIST_H
#define PP_PROJEKT_LIST_H
#include "structs.h"
#include <stdbool.h>

typedef int (*CompareFunc)(Contact, Contact);

DoublyLinkedList CreateList();
void push_back(DoublyLinkedList* list, Contact data);
void pop_back(DoublyLinkedList* list);
void remove_node(DoublyLinkedList* list, Node* node);
void clear(DoublyLinkedList* list);
bool is_empty(DoublyLinkedList* list);
int size(DoublyLinkedList* list);
void print(DoublyLinkedList *list, void (*print_func)(Contact));

// tu masz te nowe
void delete_contact_by_id(DoublyLinkedList* list, int target_id);
bool edit_contact_by_id(DoublyLinkedList* list, int target_id, Contact new_data);
void search_contacts(DoublyLinkedList* source_list, DoublyLinkedList* results_list, char* (*s_cmp)(Node *current), const char* value);
void sort_list(DoublyLinkedList* list, CompareFunc cmp_func, bool ascending);

char* s_cmp_name(Node *current);
char* s_cmp_surname(Node *current);
char* s_cmp_phone(Node *current);
char* s_cmp_street(Node *current);
char* s_cmp_number(Node *current);
char* s_cmp_postal_code(Node *current);
char* s_cmp_city(Node *current);

int cmp_by_surname(Contact a, Contact b);
int cmp_by_name(Contact a, Contact b);

#endif //PP_PROJEKT_LIST_H