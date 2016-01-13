#include "book.h"

void modifyBook(book *books, int *current_elements, section **sects, int *current_section_elements) {
    char sig[SIG_LENGTH_LIMIT];
    int j = 0;
    printf("Enter signature of the book you want to modify: ");
    scanf("%s", sig);
    clearBuffer();
    j = findBook(books, *current_elements, sig);
    if (j == -1) {
        printf("Book not found\n");
        return;
    }

    setTitle((books + j));
    setAuthorName((books + j));
    setAuthorSurname((books + j));
    setYear((books + j));
    if (*current_section_elements == 0)
        printf("There are currently no sections to set");
    else
        setSection((books + j), *sects, *current_section_elements);


    printf("\nBook modified\n");
}

void displayBySection(book *books, section *sections, int current_book_elements, int current_section_elements) {
    char temp_sect_name[WORD_LENGTH_LIMIT];
    int i = 0, k = 0;

    printf("Enter section name:");
    fgets(temp_sect_name, WORD_LENGTH_LIMIT, stdin);
    temp_sect_name[strcspn(temp_sect_name, "\n")] = '\0';
    printf("\n");

    k = findSection(sections, current_section_elements, temp_sect_name);
    if (k == -1) {
        printf("Section not found\n");
        return;
    }

    while (i < current_book_elements) {
        if (!strcmp((books + i)->sect->name, temp_sect_name)) printBook(*(books + i));
        i++;
    }
}

void displayByTitle(book *books, int current_elements) {
    char temp_title[WORD_LENGTH_LIMIT];
    int i = 0;

    printf("Enter title:");
    fgets(temp_title, WORD_LENGTH_LIMIT, stdin);
    temp_title[strcspn(temp_title, "\n")] = '\0';
    printf("\n");

    while (i < current_elements) {
        if (!strcmp(temp_title, (books + i)->title)) printBook(*(books + i));
        i++;
    }
}

void displayByAuthor(book *books, int current_elements) {
    char temp_name[WORD_LENGTH_LIMIT];
    char temp_surname[WORD_LENGTH_LIMIT];
    int i = 0;

    printf("Enter author name:");
    scanf("%s", temp_name);
    clearBuffer();
    printf("\nEnter author surname");
    scanf("%s", temp_surname);
    clearBuffer();
    printf("\n");

    while (i < current_elements) {
        if (!strcmp((books + i)->author_name, temp_name) && !strcmp((books + i)->author_surname, temp_surname)) {
            printBook(*(books + i));
        }

        i++;
    }
}

void displayByYear(book *books, int current_elements) {
    int i = 0;
    int temp_year = 0;

    printf("Enter year:");
    if (!scanf("%d", &temp_year)) {
        printf("\nIncorrect input data\n");
        return;
    }
    clearBuffer();
    while (temp_year > CURRENT_YEAR) {
        printf("\nNo books could have been published in %d because it is still %d\n", temp_year, CURRENT_YEAR);
        printf("Enter new year:");
        if (!scanf("%d", &temp_year)) {
            printf("\nIncorrect input data\n");
            return;
        }
        clearBuffer();
        scanf("%d", &temp_year);
        clearBuffer();
    }

    while (i < current_elements) {
        if ((*(books + i)).year == temp_year) printBook(*(books + i));
        i++;
    }
}

void removeBook(book **books, int *current_elements, char sig[SIG_LENGTH_LIMIT]) {
    int i = 0, j = 0;
    book *newCollection;

    i = findBook(*books, *current_elements, sig);
    if (i == -1) {
        printf("Book not found\n");
        return;
    }

    newCollection = (book *) malloc((*current_elements - 1) * sizeof(book));
    if (!newCollection) {
        printf("removeBook: memory allocation error\n");
        exit(6);
    }

    while (j < *current_elements) {
        if (j != i) *(newCollection + j) = *(*books + j);
        else if (j == i && i != *current_elements) *(newCollection + j) = *(*books + j + 1);
        j++;
    }//while

    free(*books);
    *books = newCollection;
    *current_elements -= 1;
}

// returns -1 if not found
// returns index if found
int findBook(book *books, int current_elements, char sig[SIG_LENGTH_LIMIT]) {
    int i = 0;
    while (i < current_elements) {
        if (!strcmp((*(books + i)).signature, sig)) return i;
        i++;
    }

    return -1;
}

//maybe set section here?
void createBook(book **books, int *current_elements, section **sects, int *current_section_elements) {
    book *newBook;

    newBook = (book *) malloc(sizeof(book));

    if (!newBook) {
        printf("createBook: memory allocation error\n");
        exit(3);
    }

    setTitle(newBook);
    setAuthorName(newBook);
    setAuthorSurname(newBook);
    setYear(newBook);
    setSignature(newBook, *books, *current_elements);

    if (*current_section_elements == 0) {
        printf("There are currently no sections to set\n");
    }
    else {
        setSection(newBook, *sects, *current_section_elements);
    }

    reallocateBooks(books, current_elements);//incremenet CE

    *(*books + ((*current_elements) - 1)) = *(newBook);

    printf("Book\n");
    printBook(*newBook);
    printf("Created.\n");
}

//todo: test
int reallocateBooks(book **books, int *current_elements) {
    int i = 0;
    book *newCollection;
    newCollection = (book *) malloc((*current_elements + 1) * sizeof(book));
    if (!newCollection) {
        printf("reallocateBooks: memory allocation error\n");
        exit(1);
    }

    while (i < *current_elements) {
        *(newCollection + i) = *(*books + i);
        i++;
    }//while

    if (*books != NULL)
        free(*books);
    *books = newCollection;
    *current_elements += 1;
    return 0;
}

void printBook(book b1) {
    printf("%s %s %s %s %d %s\n", b1.title, b1.author_name, b1.author_surname, b1.signature, b1.year, b1.sect->name);
}

//WIP
void setSection(book *b1, section *sects, int current_section_elements) {
    char temp_name[WORD_LENGTH_LIMIT];
    int temp_index = 0;

    clearCharArray(temp_name, WORD_LENGTH_LIMIT);

    printf("What section does the book belong to?(enter name):");
    fgets(temp_name, WORD_LENGTH_LIMIT, stdin);
    temp_name[strcspn(temp_name, "\n")] = '\0';
    printf("temp_name: %s\n", temp_name);
    printf("\n");

    temp_index = findSection(sects, current_section_elements, temp_name);

    if (temp_index == -1) {
        printf("Section with that name does not exist\n");
        return;
    }
    else {
        b1->sect = (sects + temp_index);
    }

}

void setTitle(book *b1) {
    printf("\nEnter book title: ");
    fgets(b1->title, WORD_LENGTH_LIMIT, stdin);
    b1->title[strcspn(b1->title, "\n")] = '\0';
    printf("\n");
}

void setAuthorName(book *b1) {
    printf("\nEnter author name: ");
    scanf("%s", b1->author_name);
    clearBuffer();
    printf("\n");
}

void setAuthorSurname(book *b1) {
    printf("\nEnter author surname: ");
    scanf("%s", b1->author_surname);
    clearBuffer();
    printf("\n");
}

void setYear(book *b1) {
    while (validateYear(b1)) {
        printf("Please enter correct values\n");
    }
}

void setSignature(book *b1, book *books, int current_elements) {
    char temp_sig[SIG_LENGTH_LIMIT];
    printf("\nEnter signature(format AAAA0000):");
    scanf("%s", temp_sig);
    clearBuffer();
    while (validateSignature(temp_sig) || isSignatureUnique(temp_sig, books, current_elements)) {
        printf("\nSignature invalid(correct format AAAA0000) or entered signature already exists in the database\n");
        printf("Please reenter signature: ");
        scanf("%s", temp_sig);
        clearBuffer();
    }
    printf("\n");

    strcpy(b1->signature, temp_sig);
}

int isSignatureUnique(char sig[SIG_LENGTH_LIMIT], book *books, int current_elements) {
    int i = 0;

    //printf("%s\n", sig);

    while (i < current_elements) {
        if (!strcmp(sig, (*(books + i)).signature)) return 1;

        i++;
    }
    return 0;
}

// check if "looks similiar" to AAAA0000
int validateSignature(char sig[SIG_LENGTH_LIMIT]) {
    int i = 0;
    const int j = 4;

    while (i < j) {
        if (sig[i] > 'Z' || sig[i] < 'A') return 1;
        i++;
    }//while

    while (i < SIG_LENGTH_LIMIT - 1) {
        if (sig[i] > '9' || sig[i] < '0') return 1;
        i++;
    }

    return 0;
}

// czy na pewno if dobrze działa?
int validateYear(book *b1) {
    int temp_year = 0;
    printf("Enter publication year: ");
    if (!scanf("%d", &temp_year)) {
        printf("\nIncorrect input data.\n");
        clearBuffer();
        return 1;
    }
    else {
        if (temp_year > CURRENT_YEAR) {
            printf("Year has to be an integer <= CURRENT_YEAR(%d)\n", CURRENT_YEAR);
            return 1;
        }
    }

    clearBuffer();
    b1->year = temp_year;
    return 0;
}
