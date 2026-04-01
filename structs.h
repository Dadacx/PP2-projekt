#ifndef PP_PROJEKT_CONTACT_H
#define PP_PROJEKT_CONTACT_H

typedef struct {
    char street[50];
    char number[10];
    char city[50];
    char postal_code[6];
} Address;

typedef struct {
    int ID;
    char surname[30];
    char name[20];
    char phone[9];
    Address address;
} Contact;

// Lista dwukierunkowa
typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

typedef struct DoublyLinkedList {
    Node *head;
    Node *tail;
    int size;
} DoublyLinkedList;

#endif //PP_PROJEKT_CONTACT_H