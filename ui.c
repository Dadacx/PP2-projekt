#include "ui.h"
#include "structs.h"
#include "list.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void menu() {
    puts("");
    puts("= Menu Ksiazki Telefonicznej =");
    puts("0. Zakoñcz program");
    puts("1. Wyœwietl liste kontaktów");
    puts("2. Dodaj nowy kontakt");
}
void print_format_old(Contact c) {
    printf("| %-10s %-10s | %15s %3s, %6s %-10s | %-15s| ID: %d \n",c.name,c.surname,c.address.street,c.address.number,c.address.postal_code,c.address.city,c.phone,c.ID);
}
void print_format(Contact c) {
    printf("%s %s\n%s %s, %s %s\nNumer telefonu: %s | ID: %d\n\n",c.name,c.surname,c.address.street,c.address.number,c.address.postal_code,c.address.city,c.phone,c.ID);
}
void print_book(DoublyLinkedList *list) {
    if (list->head == NULL) {
        puts("Brak kontaktów do wyœwietlenia");
        return;
    }
    // puts("+---------------------------------------------------------------------------------+");
    // puts("|    Imie i nazwisko    |                  Adres                 | Numer telefonu |");
    // puts("+---------------------------------------------------------------------------------+");
    puts("+-----------------------------------------------------------------+");
    puts("|                         Lista kontaktów                         |");
    puts("+-----------------------------------------------------------------+");
    print(list,print_format);
    // puts("+---------------------------------------------------------------------------------+");
}

void get_text(char* bufor, int length) {
    if (fgets(bufor, length, stdin) != NULL) {
        if (strchr(bufor, '\n') == NULL) {
            // gdy uzytkownik poda³ za d³ugi tekst czyœci bufor
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            bufor[strcspn(bufor, "\n")] = 0;
        }
    }
}

bool is_valid_postal_code(char* postal_code) {
    if (strlen(postal_code) == 0) {
        return false;
    }
    if (isdigit(postal_code[0]) && isdigit(postal_code[1]) && postal_code[2] == '-' && isdigit(postal_code[3]) &&
        isdigit(postal_code[4]) && isdigit(postal_code[5])) {
        return true;
    }
    return false;
}

bool is_valid_number(char* number) {
    if (strlen(number) == 0) {
        return false;
    }
    for (int i = 0; i < strlen(number); i++) {
        if (!isdigit(number[i])) {
            return false;
        }
    }
    return true;
}

bool add_contact(DoublyLinkedList *list) {
    Contact c;

    c.ID = (list->head == NULL) ? 1 : list->tail->data.ID + 1;

    puts("Podaj imie:");
    get_text(c.name,sizeof(c.name));
    puts("Podaj nazwisko:");
    get_text(c.surname,sizeof(c.surname));
    puts("Podaj miasto");
    get_text(c.address.city,sizeof(c.address.city));
    puts("Podaj ulice:");
    get_text(c.address.street,sizeof(c.address.street));
    puts("Podaj numer domu/mieszkania:");
    get_text(c.address.number,sizeof(c.address.number));
    puts("Podaj kod pocztowy:");
    get_text(c.address.postal_code,sizeof(c.address.postal_code));
    while (!is_valid_postal_code(c.address.postal_code)) {
        puts("Podany kod pocztowy jest nieprawid³owy! Wpisz jeszcze raz w prawid³owym formacie (XX-XXX)");
        get_text(c.address.postal_code,sizeof(c.address.postal_code));
    }
    puts("Podaj numer telefonu:");
    get_text(c.phone,sizeof(c.phone));
    while (!is_valid_number(c.phone)) {
        puts("Podany numer telefonu jest nieprawid³owy! Podaj jeszcze raz 9-cio cyfrowy numer telefonu");
        get_text(c.phone,sizeof(c.phone));
    }

    push_back(list,c);

    // Zwracam true, bo funkcja w deklaracji zwraca bool
    return true;
}