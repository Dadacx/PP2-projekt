#ifndef PP_PROJEKT_UI_H
#define PP_PROJEKT_UI_H
#include "structs.h"
#include <stdbool.h>

void init_menu(DoublyLinkedList *list, char db_name[]);
void menu();
void print_book(DoublyLinkedList *list, char title[67]);
void add_contact(DoublyLinkedList *list);
void delete_contact(DoublyLinkedList *list);
void edit_contact(DoublyLinkedList *list);
void search(DoublyLinkedList *list);
void sort(DoublyLinkedList *list);
void get_text(char* bufor, int length);

#endif //PP_PROJEKT_UI_H