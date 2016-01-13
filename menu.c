#include "menu.h"

void menu(book **books, int *current_book_elements, section **sections, int *current_section_elements) {
    int choice = 0;
    int clr = 0;

    printf("Choose an option:\n");
    printf("1) Manage books\n");
    printf("2) Manage sections\n");
    printf("3) Save/Load\n");
    printf("I choose: ");

    clr = scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            books(books, current_book_elements, sections, current_section_elements);
            break;
        case 2:
            sections(sections, current_section_elements);
            break;
        case 3:
            fileMngr();
            break;
        default:
            printf("Error: menu -> something went wrong\n");
            // failed to scanf == chars left in buffer
            if (clr == 0) clearBuffer();
    }
}

void books(book **books, int *current_book_elements, section **sections, int *current_section_elements) {
    int choice = 0;
    while (1) {
        printf("Book Managment Menu\n");
        printf("1) Create book\n2) Modify book\n3) Remove book\n4) Display\n5)Back\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1:
                createBook(books, current_book_elements);
                break;
            case 2:
                modifyBook(*books, current_book_elements);
                break;
            case 3:
                char sig[SIG_LENGTH_LIMIT];
                if (*current_book_elements == 0) {
                    printf("There are no books to remove\n");
                    break;
                }
                clearCharArray(sig, SIG_LENGTH_LIMIT);
                printf("Enter signature of the book you want to remove\n")
                scanf("%s", sig);
                while (validateSignature(sig)) {
                    printf("Incorrect signature\n");
                    printf("Please reenter\n");
                    clearCharArray(sig, SIG_LENGTH_LIMIT);
                    scanf("%s", sig);
                }
                removeBook(books, current_book_elements, sig);
                break;
            case 4:
                bDisplayMenu(books, current_book_elements);
                break;
            case 5:
                return;
            default:
                printf("Incorrect input.\n");
        }//switch

    }//while
}

void sections(section **sections, int *current_section_elements) {
    int choice = 0;
    int clr = 0;
    char name[WORD_LENGTH_LIMIT];

    while (1) {
        printf("Section Managment Menu\n");
        printf("1) Create section\n2) Rename section\n3) Remove section\n4) Display sections\n5) Back");
        printf("Choose an option: ");
        clr = scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                createSection(sections, current_section_elements);
                break;
            case 2:
                printf("Enter section's name: ");
                scanf("%s", name);
                printf("\n");
                renameSection(*sections, *current_section_elements, name);
                break;
            case 3:
                printf("Enter section's name: ");
                scanf("%s", name);
                printf("\n");
                removeSection(sections, current_section_elements, name);
                break;
            case 4:
                displaySections(*sections, *current_section_elements);
                break;
            case 5:
                return;
            default:
                printf("Incorrect input\n");
                //failed scanf == chars left in buffer
                if (clr == 0) clearBuffer();
        }//switch

    }//while
}

void fileMngr(book **books, int *current_book_elements, section **sections, int *current_section_elements) {
    char line[WORD_LENGTH_LIMIT];
    char cmd[WORD_LENGTH_LIMIT];
    char filename[WORD_LENGTH_LIMIT];
    char temp[WORD_LENGTH_LIMIT];
    int i = 0;

    clearCharArray(command, WORD_LENGTH_LIMIT);
    clearCharArray(cmd, WORD_LENGTH_LIMIT);
    clearCharArray(filename, WORD_LENGTH_LIMIT);
    clearCharArray(temp, WORD_LENGTH_LIMIT);

    printf("File Manager\n");
    printf("Commands available: save/load filename\n");
    printf("Supported files: katalog.txt pozycje.txt baza.txt\n");
    printf("Enter command: ");
    fgets(command, WORD_LENGTH_LIMIT, stdin);
    printf("\n");

//check if works
    cmd = strtok(line, " ");
    temp = strtok(NULL, " ");
    //remove \n added by fgets
    filename = strndup(temp, strcspn(temp, "\n"));

    if (!strcasecmp(cmd, "save")) {
        if (!strcasecmp(filename, "katalog.txt"))
            saveSections(filename, sections, *current_section_elements);
        else if (!strcasecmp(filename, "pozycje.txt"))
            saveBooks(filename, books, *current_book_elements);
        else if (!strcasecmp(filename, "baza.txt"))
            saveDatabase(filename, books, *current_book_elements);
    }//if save
    else if (!strcasecmp(cmd, "load")) {
        if (!strcasecmp(filename, "katalog.txt"))
            loadSections(filename, sections, current_section_elements);
        if (!strcasecmp(filename, "pozycje.txt"))
            loadBooks(filename, books, current_book_elements);
        if (!strcasecmp(filename, "baza.txt"))
            loadDatabase(filename, books, current_book_elements, sections, current_section_elements);
    }//if load
    else {
        printf("Incorrect command\n");
        printf("Enter save filename or load filename\n");
    }

}

void about() {
    printf("Program created by Robert Piwowarek for PRI laboratories\n");
    printf("Group: 1I2\n");
    printf("Library - save, load, create book records and group them by sections\n");
}
