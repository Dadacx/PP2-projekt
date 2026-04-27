#include <stdio.h>
#include <windows.h>

#include "list.h"
#include "structs.h"
#include "ui.h"
#include "file_io.h"

int main(void) {
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    int choose = -1;
    DoublyLinkedList list = CreateList();
    if (!load_from_file(&list, "database.txt")) {
        puts("B³¹d podczas pobierania danych z pliku!");
        return 1;
    }

    while (choose != 0) {
        menu();
        printf("Wybór: ");

        // Sprawdzamy czy scanf poprawnie zczyta³ cyfrê
        if (scanf("%d", &choose) != 1) {
            choose = -1;
        }

        // Czyszczenie bufora (jeœli ktoœ wpisze tekst lub po wciœniêciu Entera dla cyfry)
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
            case 3: {
                save_to_file(&list, "database.txt");
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