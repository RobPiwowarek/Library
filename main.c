#include "helpers.h"
#include "book.h"
#include "menu.h"

int main(void) {
    book *library = NULL;
    section *sections = NULL;
    int lib_elements = 0, sect_elements = 0;

    about();
    while (1) {
        menu(&library, &lib_elements, &sections, &sect_elements);
    }
}
