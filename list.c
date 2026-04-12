#include "list.h"
#include "structs.h"

#include <stdio.h>
#include <stdlib.h>

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
        printf("B³ad alokacji pamieci!");
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
    // Zabezpieczenie przed pust¹ list¹
    if (list->tail == NULL) {
        return;
    }

    Node *temp = list->tail;
    list->tail = temp->prev;

    // Sprawdzenie czy po przesuniêciu ogona lista sta³a siê pusta
    if (list->tail == NULL) {
        list->head = NULL;
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