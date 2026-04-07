#include <stdio.h>
#include "list.h"
#include "structs.h"

void delete_contact_by_id(DoublyLinkedList* list, int target_id) {
    Node* current = list->head;

    while (current != NULL) {
        // Rzutujemy void* na nasz typ danych, żeby sprawdzić ID
        Contact c = current->data;

        if (c.ID == target_id) {
            // Znaleźliśmy węzeł, teraz wywołujemy uniwersalną funkcję usuwającą
            remove_node(list, current);
            printf("Kontakt o ID %d został usunięty.\n", target_id);
            return;
        }
        current = current->next;
    }
    printf("Nie znaleziono kontaktu o ID %d.\n", target_id);
}
void print_surname(Contact c) { printf("%s ", c.surname); }
void print_name(Contact c) { printf("%s ", c.name); }
void print_all(Contact c) { printf("%s %s +48 %s\n", c.name, c.surname, c.phone); }
int main(void) {
    Contact c1 = {
        .ID = 1,
        .surname = "Kowalski",
        .name = "Jan",
        .phone = "123456789",
        .address = {
            .city = "Warszawa",
            .postal_code = "00-001",
            .number = "23",
            .street = "Mickiewicza",
        }
    };
    Contact c2 = {
        .ID = 2,
        .surname = "Nowak",
        .name = "Karol",
        .phone = "987654321",
        .address = {
            .city = "Lodz",
            .postal_code = "40-101",
            .number = "223",
            .street = "Sienkiewicza",
        }
    };
    Contact c3 = {
        .ID = 3,
        .surname = "Kowal",
        .name = "Katarzyna",
        .phone = "497530673",
        .address = {
            .city = "Gdansk",
            .postal_code = "50-031",
            .number = "53",
            .street = "Rozana",
        }
    };

    DoublyLinkedList list = CreateList();
    push_back(&list, c1);
    push_back(&list, c2);
    push_back(&list, c3);
    puts("\nLista:");
    print(&list,print_name);
    puts("\nLista:");
    print(&list,print_surname);
    puts("\nLista:");
    print(&list,print_all);
    pop_back(&list);
    puts("\nLista:");
    print(&list,print_surname);
    delete_contact_by_id(&list,1);
    puts("\nLista:");
    print(&list,print_surname);
    clear(&list);
    puts("\nLista:");
    print(&list,print_surname);
    return 0;
}