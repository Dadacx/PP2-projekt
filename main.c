#include <stdio.h>
#include "list.h"
#include "structs.h"

void print_surname(Contact c) { printf("%s ", c.surname); }
void print_name(Contact c) { printf("%s ", c.name); }
void print_all(Contact c) { printf("%s %s +48 %s\n", c.name, c.surname, c.phone); }

int main(void) {
    Contact c1 = {
        .ID = 1,
        .surname = "Kowalski",
        .name = "Jan",
        .phone = "123456789",
        .address = {.city = "Warszawa", .postal_code = "00-001", .number = "23", .street = "Mickiewicza"}
    };
    Contact c2 = {
        .ID = 2,
        .surname = "Nowak",
        .name = "Karol",
        .phone = "987654321",
        .address = {.city = "Lodz", .postal_code = "40-101", .number = "223", .street = "Sienkiewicza"}
    };
    Contact c3 = {
        .ID = 3,
        .surname = "Kowal",
        .name = "Katarzyna",
        .phone = "497530673",
        .address = {.city = "Gdansk", .postal_code = "50-031", .number = "53", .street = "Rozana"}
    };

    DoublyLinkedList list = CreateList();
    push_back(&list, c1);
    push_back(&list, c2);
    push_back(&list, c3);

    puts("\nLista:");
    print(&list, print_all);

    puts("\nWyszukiwanie 'Nowak':");
    Node* found = search_contact_by_surname(&list, "Nowak");
    if (found != NULL) {
        print_all(found->data);
    }

    puts("\nSortowanie rosnaco po nazwisku:");
    sort_list(&list, cmp_by_surname, true);
    print(&list, print_all);

    puts("\nEdycja kontaktu ID 1:");
    Contact c_edit = c1;
    sprintf(c_edit.surname, "Adamczyk");
    edit_contact_by_id(&list, 1, c_edit);
    print(&list, print_all);

    clear(&list);
    return 0;
}