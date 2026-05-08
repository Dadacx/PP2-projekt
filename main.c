#include <stdio.h>
#include <windows.h>

#include "list.h"
#include "structs.h"
#include "ui.h"
#include "file_io.h"

int main(void) {
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    DoublyLinkedList list = CreateList();
    char db_name[] = "database.txt";

    if (!load_from_file(&list, db_name)) {
        puts("Nie znaleziono pliku z danymi, tworzê nowy plik...");
        save_to_file(&list,db_name);
    }

    init_menu(&list,db_name);

    clear(&list);
    return 0;
}