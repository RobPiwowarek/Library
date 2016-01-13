#include"../include/helpers.h"
#include"../include/book.h"
#include"../include/menu.h"

int main(void) {
    book *library = NULL;
    section *sections = NULL;
    int lib_elements = 0, sect_elements = 0;

    about();
    while (1) {
        menu(&library, &lib_elements, &sections, &sect_elements);
    }
}
