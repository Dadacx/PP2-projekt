#include <stdio.h>
#include <windows.h>

#include "list.h"
#include "structs.h"
#include "ui.h"

int main(void) {
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    int choose = -1;
    DoublyLinkedList list = CreateList();

    while (choose != 0) {
        menu();
        printf("Wyb�r: ");

        // Sprawdzamy czy scanf poprawnie zczyta� cyfr�
        if (scanf("%d", &choose) != 1) {
            choose = -1;
        }

        // Czyszczenie bufora (je�li kto� wpisze tekst lub po wci�ni�ciu Entera dla cyfry)
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choose) {
            case 0: break;
            case 1: {
                print_book(&list);
                break;
            }
            case 2: {
                add_contact(&list);
                break;
            }
            default: {
                puts("Nieprawidlowy wybor!");
                break;
            }
        }
    }

    clear(&list);
    return 0;
}