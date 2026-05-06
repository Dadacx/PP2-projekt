#ifndef PP_PROJEKT_FILE_IO_H
#define PP_PROJEKT_FILE_IO_H
#include <stdbool.h>
#include <string.h>
#include "structs.h"
#include "list.h"

bool save_to_file(DoublyLinkedList *list, char file_name[]);
bool load_from_file(DoublyLinkedList *list, char file_name[]);

#endif //PP_PROJEKT_FILE_IO_H