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
        printf("Wybór: ");
        scanf("%d", &choose);
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
                puts("Nieprawid³owy wybór!");
                break;
            }
        }
    }

    clear(&list);
    return 0;
}
