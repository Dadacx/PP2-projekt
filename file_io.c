#include "file_io.h"

#include <stdio.h>
#include <stdlib.h>

bool save_to_file(DoublyLinkedList *list, char file_name[]) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        // printf("Błąd podczas otwierania pliku '%s'",file_name);
        return false;
    }
    Node *current = list->head;
    while (current != NULL) {
        Contact *c = &(current->data);
        fprintf(file,"%d;%s;%s;%s;%s;%s;%s;%s\n",
            c->ID,
            c->surname,
            c->name,
            c->phone,
            c->address.street,
            c->address.number,
            c->address.city,
            c->address.postal_code);

        current = current->next;
    }
    fclose(file);
    return true;
}

bool load_from_file(DoublyLinkedList *list, char file_name[]) {
    char bufor[255];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        return false;
    }
    // wczytywanie po 1 linii
    while (fgets(bufor, 255, file) != NULL) {
        bufor[strcspn(bufor, "\r\n")] = 0;

        Contact c;
        char* token;

        token = strtok(bufor, ";");
        if (token != NULL) c.ID = atoi(token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(c.surname, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(c.name, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(c.phone, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(c.address.street, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(c.address.number, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(c.address.city, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(c.address.postal_code, token);

        push_back(list, c);
    }
    fclose(file);
    return true;
}