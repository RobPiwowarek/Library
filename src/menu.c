#include"../include/menu.h"
#include"../include/fileManager.h"

void menu(book **liBooks, int *current_book_elements, section **sects, int *current_section_elements) {
    int choice = 0;
    int clr = 0;

    printf("Choose an option:\n");
    printf("1) Manage books\n");
    printf("2) Manage sections\n");
    printf("3) Save/Load\n");
    printf("I choose: ");

    clr = scanf("%d", &choice);
    clearBuffer();
    printf("\n");

    switch (choice) {
        case 1:
            books(liBooks, current_book_elements, sects, current_section_elements);
            break;
        case 2:
            sections(sects, current_section_elements);
            break;
        case 3:
            fileMngr(liBooks, current_book_elements, sects, current_section_elements);
            break;
        default:
            printf("Error: menu -> something went wrong\n");
            // failed to scanf == chars left in buffer
    }
}

void books(book **libBooks, int *current_book_elements, section **sects, int *current_section_elements) {
    int choice = 0;
    char sig[SIG_LENGTH_LIMIT];

    clearCharArray(sig, SIG_LENGTH_LIMIT);

    while (1) {
        printf("Book Managment Menu\n");
        printf("1) Create book\n2) Modify book\n3) Remove book\n4) Display\n5) Back\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clearBuffer();
        printf("\n");
        switch (choice) {
            case 1:
                createBook(libBooks, current_book_elements, sects, current_section_elements);
                break;
            case 2:
                modifyBook(*libBooks, current_book_elements, sects, current_section_elements);
                break;
            case 3:
                if (*current_book_elements == 0) {
                    printf("There are no books to remove\n");
                    break;
                }
                clearCharArray(sig, SIG_LENGTH_LIMIT);
                printf("Enter signature of the book you want to remove\n");
                scanf("%s", sig);
                clearBuffer();
                while (validateSignature(sig)) {
                    printf("Incorrect signature\n");
                    printf("Please reenter\n");
                    clearCharArray(sig, SIG_LENGTH_LIMIT);
                    scanf("%s", sig);
                    clearBuffer();
                }
                removeBook(libBooks, current_book_elements, sig);
                break;
            case 4:
                bDisplayMenu(libBooks, *current_book_elements, sects, *current_section_elements);
                break;
            case 5:
                return;
            default:
                printf("Incorrect input.\n");
        }//switch

    }//while
}

void sections(section **sects, int *current_section_elements) {
    int choice = 0;
    int clr = 0;
    char name[WORD_LENGTH_LIMIT];

    clearCharArray(name, WORD_LENGTH_LIMIT);

    while (1) {
        printf("Section Managment Menu\n");
        printf("1) Create section\n2) Rename section\n3) Remove section\n4) Display sections\n5) Back\n");
        printf("Choose an option: ");
        clr = scanf("%d", &choice);
        clearBuffer();
        printf("\n");

        switch (choice) {
            case 1:
                createSection(sects, current_section_elements);
                break;
            case 2:
                printf("Enter section's name: ");

                fgets(name, WORD_LENGTH_LIMIT, stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("\n");
                renameSection(*sects, *current_section_elements, name);
                break;
            case 3:
                printf("Enter section's name: ");

                fgets(name, WORD_LENGTH_LIMIT, stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("\n");
                removeSection(sects, current_section_elements, name);
                break;
            case 4:
                displaySections(*sects, *current_section_elements);
                break;
            case 5:
                return;
            default:
                printf("Incorrect input\n");
                //failed scanf == chars left in buffer
        }//switch
    }//while
}

void fileMngr(book **liBooks, int *current_book_elements, section **sects, int *current_section_elements) {
    char line[WORD_LENGTH_LIMIT];
    char cmd[WORD_LENGTH_LIMIT];
    char filename[WORD_LENGTH_LIMIT];
    char temp[WORD_LENGTH_LIMIT];

    clearCharArray(line, WORD_LENGTH_LIMIT);
    clearCharArray(cmd, WORD_LENGTH_LIMIT);
    clearCharArray(filename, WORD_LENGTH_LIMIT);
    clearCharArray(temp, WORD_LENGTH_LIMIT);

    printf("File Manager\n");
    printf("Commands available: save/load filename\n");
    printf("Supported files: katalog.txt pozycje.txt baza.txt\n");
    printf("Enter command: ");
    fgets(line, WORD_LENGTH_LIMIT, stdin);
    printf("\n");

    strcpy(cmd, strtok(line, " "));
    strcpy(temp, strtok(NULL, " "));
    //remove \n added by fgets
    strcpy(filename, strndup(temp, strcspn(temp, "\n")));

    if (!strcasecmp(cmd, "save")) {
        if (!strcasecmp(filename, "katalog.txt"))
            saveSections(filename, sects, *current_section_elements);
        else if (!strcasecmp(filename, "pozycje.txt"))
            saveBooks(filename, liBooks, *current_book_elements);
        else if (!strcasecmp(filename, "baza.txt"))
            saveDatabase(filename, liBooks, *current_book_elements);
    }//if save
    else if (!strcasecmp(cmd, "load")) {
        if (!strcasecmp(filename, "katalog.txt"))
            loadSections(filename, sects, current_section_elements);
        if (!strcasecmp(filename, "pozycje.txt"))
            loadBooks(filename, liBooks, current_book_elements);
        if (!strcasecmp(filename, "baza.txt"))
            loadDatabase(filename, liBooks, sects, current_book_elements, current_section_elements);
    }//if load
    else {
        printf("Incorrect command\n");
        printf("Enter save filename or load filename\n");
    }

}

void bDisplayMenu(book **libBooks, int current_elements, section **sects, int current_section_elements) {
    int choice = 0;
    int a = 0;
    printf("Display Menu\n");
    printf("1) By title\n2) By author\n3) By year\n4) By section\n5) All books\n6) Back\n");
    printf("Choose an option: ");
    do {
        a = scanf("%d", &choice);
        clearBuffer();
        printf("\n");

        if (a == 0 || choice < 1 || choice > 5) {
            printf("Wrong input. Please re-enter:");
        }

    } while (a == 0 || choice < 1 || choice > 5);

    switch (choice) {
        case 1:
            displayByTitle(*libBooks, current_elements);
            break;
        case 2:
            displayByAuthor(*libBooks, current_elements);
            break;
        case 3:
            displayByYear(*libBooks, current_elements);
            break;
        case 4:
            displayBySection(*libBooks, *sects, current_elements, current_section_elements);
            break;
        case 5:
            displayAllBooks(*libBooks, current_elements);
            break;
        case 6:
            return;
    }
}

void about() {
    printf("Program created by Robert Piwowarek for PRI laboratories\n");
    printf("Group: 1I2\n");
    printf("Library - save, load, create book records and group them by sections\n");
}
