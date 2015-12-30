#include "helpers.h"
#include "book.h"
#include "section.h"

int main(void) {
    book *library = NULL;
    section *sections = NULL;
    int lib_elements = 0, sect_elements = 0;

    for (int i = 0; i < 5; i++) {
//createBook(&library, &lib_elements);
        createSection(&sections, &sect_elements);

        for (int j = 0; j < sect_elements; j++) printf("[%d] %s\n", j, (sections+j)->name);

        printf("DUPA%d\n", 8 + i);
    }


    return 0;
}
