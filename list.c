#include "list.h"
#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

DoublyLinkedList CreateList() {
    DoublyLinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return list;
}

Node *CreateNode(Contact data) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node == NULL) {
        printf("B³¹d alokacji pamieci!");
        exit(-1); // b³¹d przy alokacji pamiêci zakoñczy program
    } else {
        node->data = data;
        node->next = NULL;
        node->prev = NULL;
        return node;
    }
}

void push_back(DoublyLinkedList *list, Contact data) {
    Node *node = CreateNode(data);
    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
        list->size++;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->size++;
}

void pop_back(DoublyLinkedList *list) {
    //  to jest zabezpieczenie przed pust¹ lista
    if (list->tail == NULL) {
        return; // jesli ma czego usuwaæ, po prostu wychodzimy z funkcji
    }

    Node *temp = list->tail;
    list->tail = temp->prev;

    //  sprawdzenie czy po przesuniêciu ogona lista sta³a siê pusta
    if (list->tail == NULL) {
        list->head = NULL; // skoro nie ma ogona, nie mo¿e byæ te¿ g³owy
    } else {
        list->tail->next = NULL;
    }
    free(temp);
    list->size--;
}

void remove_node(DoublyLinkedList *list, Node *node) {
    if (list == NULL || node == NULL) return;

    // Przepinanie wskaŸnika 'next' u poprzednika
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    // Przepinanie wskaŸnika 'prev' u nastêpnika
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }
    free(node);
    list->size--;
}

void clear(DoublyLinkedList *list) {
    Node *current = list->head;
    Node *next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

bool is_empty(DoublyLinkedList *list) {
    return list->size == 0;
}

int size(DoublyLinkedList *list) {
    return list->size;
}

void print(DoublyLinkedList *list, void (*print_func)(Contact)) {
    Node *current = list->head;
    while (current != NULL) {
        print_func(current->data);
        current = current->next;
    }
}

// funkcje z 2

void delete_contact_by_id(DoublyLinkedList* list, int target_id) {
    Node* current = list->head;

    while (current != NULL) {
        if (current->data.ID == target_id) {
            // wywolujemy uniwersaln¹ funkcjê usuwaj¹c¹
            remove_node(list, current);
            printf("Kontakt o ID %d zosta³ usuniêty.\n", target_id);
            return;
        }
        current = current->next;
    }
    printf("Nie znaleziono kontaktu o ID %d.\n", target_id);
}

bool edit_contact_by_id(DoublyLinkedList* list, int target_id, Contact new_data) {
    Node* current = list->head;
    while(current != NULL) {
        if (current->data.ID == target_id) {
            int old_id = current->data.ID;
            current->data = new_data;
            current->data.ID = old_id;
            return true;
        }
        current = current->next;
    }
    return false;
}

void search_contacts_by_surname(DoublyLinkedList* source_list, DoublyLinkedList* results_list, const char* surname) {
    Node* current = source_list->head;

    while(current != NULL) {
        if (strcmp(current->data.surname, surname) == 0) {
            push_back(results_list, current->data);
        }
        current = current->next;
    }
}

int cmp_by_surname(Contact a, Contact b) {
    return strcmp(a.surname, b.surname);
}

int cmp_by_name(Contact a, Contact b) {
    return strcmp(a.name, b.name);
}

void sort_list(DoublyLinkedList* list, CompareFunc cmp_func, bool ascending) {
    if (list == NULL || list->size < 2) return;

    bool swapped;
    Node* current;
    Node* last_ptr = NULL;

    do {
        swapped = false;
        current = list->head;

        while (current->next != last_ptr) {
            int res = cmp_func(current->data, current->next->data);
            bool should_swap = ascending ? (res > 0) : (res < 0);

            if (should_swap) {
                Contact temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
        last_ptr = current;
    } while (swapped);
}