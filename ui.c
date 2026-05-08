#include "ui.h"
#include "structs.h"
#include "list.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "file_io.h"

void init_menu(DoublyLinkedList *list, char db_name[]) {
    int choose = -1;
    while (choose != 0) {
        menu();
        printf("Wybór: ");

        // czy scanf poprawnie zczyta³ cyfre
        if (scanf("%d", &choose) != 1) {
            choose = -1;
        }

        // Czyszczenie bufora (jeœli ktoœ wpisze tekst)
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choose) {
            case 0: break;
            case 1: {
                print_book(list, "|                         Lista kontaktów                         |");
                break;
            }
            case 2: {
                add_contact(list);
                break;
            }
            case 3: {
                delete_contact(list);
                break;
            }
            case 4: {
                edit_contact(list);
                break;
            }
            case 5: {
                search(list);
                break;
            }
            case 6: {
                sort(list);
                break;
            }
            case 7: {
                if (save_to_file(list, db_name)) {
                    puts("\nKontakty zosta³y pomyœlnie zapisane do pliku");
                } else {
                    puts("\nNie uda³o sie zapisac kontaktów do pliku!");
                }
                break;
            }
            default: {
                puts("Nieprawidlowy wybor!");
                break;
            }
        }
    }
}

void menu() {
    puts("");
    puts("=-= Menu Ksiazki Telefonicznej =-=");
    puts("0. Zakoñcz program");
    puts("1. Wyœwietl liste kontaktów");
    puts("2. Dodaj nowy kontakt");
    puts("3. Usuñ kontakt");
    puts("4. Edytuj kontakt");
    puts("5. Wyszukaj kontakty");
    puts("6. Sortuj kontakty");
    puts("7. Zapisz");
    puts("");
}

void categoty_menu() {
    puts("");
    puts("=-= Wybierz kategorie =-=");
    puts("1. ID");
    puts("2. Imie");
    puts("3. Nazwisko");
    puts("4. Numer telefonu");
    puts("5. Miasto");
    puts("6. Ulica");
    puts("7. Numer domu");
    puts("8. kod pocztowy");
    puts("");
}

// void print_format(Contact c) {
//     printf("| %-10s %-10s | %15s %3s, %6s %-10s | %-15s| ID: %d \n", c.name, c.surname, c.address.street,
//            c.address.number, c.address.postal_code, c.address.city, c.phone, c.ID);
// }

void print_format(Contact c) {
    printf("%s %s\n%s %s, %s %s\nNumer telefonu: %s | ID: %d\n\n", c.name, c.surname, c.address.street,
           c.address.number, c.address.postal_code, c.address.city, c.phone, c.ID);
}

void print_book(DoublyLinkedList *list, char title[67]) {
    if (list->head == NULL) {
        puts("\nBrak kontaktów do wyœwietlenia");
        return;
    }
    // puts("+---------------------------------------------------------------------------------+");
    // puts("|    Imie i nazwisko    |                  Adres                 | Numer telefonu |");
    // puts("+---------------------------------------------------------------------------------+");
    puts("+-----------------------------------------------------------------+");
    // puts("|                         Lista kontaktów                         |");
    printf("%s\n", title);
    puts("+-----------------------------------------------------------------+");
    print(list, print_format);
    // puts("+---------------------------------------------------------------------------------+");
}

void get_text(char *bufor, int length) {
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

bool is_valid_postal_code(char *postal_code) {
    if (strlen(postal_code) == 0) {
        return false;
    }
    if (isdigit(postal_code[0]) && isdigit(postal_code[1]) && postal_code[2] == '-' && isdigit(postal_code[3]) &&
        isdigit(postal_code[4]) && isdigit(postal_code[5])) {
        return true;
    }
    return false;
}

bool is_valid_number(char *number) {
    if (strlen(number) != 9) {
        return false;
    }
    for (int i = 0; i < strlen(number); i++) {
        if (!isdigit(number[i])) {
            return false;
        }
    }
    return true;
}

void add_contact(DoublyLinkedList *list) {
    Contact c;

    c.ID = (list->head == NULL) ? 1 : list->tail->data.ID + 1;

    puts("Podaj imie:");
    get_text(c.name, sizeof(c.name));
    puts("Podaj nazwisko:");
    get_text(c.surname, sizeof(c.surname));
    puts("Podaj miasto:");
    get_text(c.address.city, sizeof(c.address.city));
    puts("Podaj ulice:");
    get_text(c.address.street, sizeof(c.address.street));
    puts("Podaj numer domu/mieszkania:");
    get_text(c.address.number, sizeof(c.address.number));
    puts("Podaj kod pocztowy:");
    get_text(c.address.postal_code, sizeof(c.address.postal_code));
    while (!is_valid_postal_code(c.address.postal_code)) {
        puts("Podany kod pocztowy jest nieprawid³owy! Wpisz jeszcze raz w prawid³owym formacie (XX-XXX)");
        get_text(c.address.postal_code, sizeof(c.address.postal_code));
    }
    puts("Podaj numer telefonu:");
    get_text(c.phone, sizeof(c.phone));
    while (!is_valid_number(c.phone)) {
        puts("Podany numer telefonu jest nieprawid³owy! Podaj jeszcze raz 9-cio cyfrowy numer telefonu");
        get_text(c.phone, sizeof(c.phone));
    }

    push_back(list, c);
    puts("\nNowy kontakt zosta³ dodany");
}

void delete_contact(DoublyLinkedList *list) {
    int id = 0;

    puts("Podaj ID kontaktu, który chcesz usun¹æ");
    while (true) {
        if (scanf("%d", &id) == 1) break;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        puts("ID musi byæ liczb¹!");
    }
    delete_contact_by_id(list, id);
}

void edit_contact(DoublyLinkedList *list) {
    int id = 0;
    char bufor[55];

    puts("Podaj ID kontaktu, który chcesz edytowaæ");
    while (true) {
        if (scanf("%d", &id) == 1) break;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        puts("ID musi byæ liczb¹!");
    }

    Node *current = list->head;
    while (current != NULL && current->data.ID != id) {
        current = current->next;
    }
    if (current != NULL) {
        Contact tmp_contact = current->data;

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        puts("\nWcisnij sam Enter, aby zostawic wartoœæ bez zmian");

        printf("Podaj imie [%s]:", tmp_contact.name);
        get_text(bufor, sizeof(tmp_contact.name));
        if (strlen(bufor) > 0) strcpy(tmp_contact.name, bufor);

        printf("Podaj nazwisko [%s]:", tmp_contact.surname);
        get_text(bufor, sizeof(tmp_contact.surname));
        if (strlen(bufor) > 0) strcpy(tmp_contact.surname, bufor);

        printf("Podaj miasto [%s]:", tmp_contact.address.city);
        get_text(bufor, sizeof(tmp_contact.address.city));
        if (strlen(bufor) > 0) strcpy(tmp_contact.address.city, bufor);

        printf("Podaj ulice [%s]:", tmp_contact.address.street);
        get_text(bufor, sizeof(tmp_contact.address.street));
        if (strlen(bufor) > 0) strcpy(tmp_contact.address.street, bufor);

        printf("Podaj numer domu/mieszkania [%s]:", tmp_contact.address.number);
        get_text(bufor, sizeof(tmp_contact.address.number));
        if (strlen(bufor) > 0) strcpy(tmp_contact.address.number, bufor);

        printf("Podaj kod pocztowy [%s]:", tmp_contact.address.postal_code);
        get_text(bufor, sizeof(tmp_contact.address.postal_code));
        while (!is_valid_postal_code(bufor) && strlen(bufor) > 0) {
            puts("Podany kod pocztowy jest nieprawid³owy! Wpisz jeszcze raz w prawid³owym formacie (XX-XXX)");
            get_text(bufor, sizeof(tmp_contact.address.postal_code));
        }
        if (strlen(bufor) > 0) strcpy(tmp_contact.address.postal_code, bufor);

        printf("Podaj numer telefonu [%s]:", tmp_contact.phone);
        get_text(bufor, sizeof(tmp_contact.phone));
        while (!is_valid_number(bufor) && strlen(bufor) > 0) {
            puts("Podany numer telefonu jest nieprawid³owy! Podaj jeszcze raz 9-cio cyfrowy numer telefonu");
            get_text(bufor, sizeof(tmp_contact.phone));
        }
        if (strlen(bufor) > 0) strcpy(tmp_contact.phone, bufor);

        if (edit_contact_by_id(list, id, tmp_contact)) {
            printf("\nKontakt o ID %d zosta³ zaktualizowany\n", id);
        } else {
            printf("N\nie uda³o siê zaktualizowaæ kontaktu o ID %d\n", id);
        }
    } else {
        printf("\nNie znaleziono kontaktu o ID %d\n", id);
    }
}

void search(DoublyLinkedList *list) {
    char bufor[100];
    char * (*s_cmp_func)(Node *) = NULL;
    int choose = 0;
    DoublyLinkedList search_results = CreateList();

    categoty_menu();
    while (choose < 1 || choose > 8) {
        printf("Wybór: ");

        if (scanf("%d", &choose) != 1) {
            choose = -1;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choose) {
            case 1: {
                s_cmp_func = s_cmp_id;
                break;
            }
            case 2: {
                s_cmp_func = s_cmp_name;
                break;
            }
            case 3: {
                s_cmp_func = s_cmp_surname;
                break;
            }
            case 4: {
                s_cmp_func = s_cmp_phone;
                break;
            }
            case 5: {
                s_cmp_func = s_cmp_city;
                break;
            }
            case 6: {
                s_cmp_func = s_cmp_street;
                break;
            }
            case 7: {
                s_cmp_func = s_cmp_number;
                break;
            }
            case 8: {
                s_cmp_func = s_cmp_postal_code;
                break;
            }
            default: {
                puts("Nieprawidlowy wybor!");
                break;
            }
        }
    }

    puts("Podaj wysukiwan¹ frazê: ");
    get_text(bufor, sizeof(bufor));

    search_contacts(list, &search_results, s_cmp_func, bufor);

    if (search_results.head == NULL) {
        printf("Nie znaleziono zadnych kontaktow o podanych kryteriach: %d, %s\n", choose, bufor);
    } else {
        print_book(&search_results, "|                       ZNALEZIONE KONTAKTY                       |");
        clear(&search_results);
    }
}

void sort(DoublyLinkedList *list) {
    int choose = 0;
    int asc = 0;
    int (*cmp_func)(Contact, Contact) = NULL;

    categoty_menu();
    while (choose < 1 || choose > 8) {
        printf("Wybór: ");

        if (scanf("%d", &choose) != 1) {
            choose = -1;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choose) {
            case 1: {
                cmp_func = cmp_by_id;
                break;
            }
            case 2: {
                cmp_func = cmp_by_name;
                break;
            }
            case 3: {
                cmp_func = cmp_by_surname;
                break;
            }
            case 4: {
                cmp_func = cmp_by_phone;
                break;
            }
            case 5: {
                cmp_func = cmp_by_city;
                break;
            }
            case 6: {
                cmp_func = cmp_by_street;
                break;
            }
            case 7: {
                cmp_func = cmp_by_number;
                break;
            }
            case 8: {
                cmp_func = cmp_by_postal_code;
                break;
            }
            default: {
                puts("Nieprawidlowy wybor!");
                break;
            }
        }
    }
    puts("\n=-= Wybierz porz¹dek sortowania =-=\n1. Rosn¹co\n2. Malej¹co\n");

    while (asc < 1 || asc > 2) {
        printf("Wybór: ");

        if (scanf("%d", &asc) != 1) {
            asc = 0;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        switch (asc) {
            case 1: {
                sort_list(list, cmp_func,true);
                break;
            }
            case 2: {
                sort_list(list, cmp_func,false);
                break;
            }
            default: {
                puts("Nieprawidlowy wybor!");
            }
        }
    }
    puts("\nLista kontaktów zosta³a posortowana.");
}