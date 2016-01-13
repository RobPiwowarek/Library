#include "fileManager.h"
#include "helpers.h"
#include "book.h"
#include "section.h"

void loadSections(char filename[WORD_LENGTH_LIMIT], section **sections, int *current_elements) {
    FILE *file;
    char c;
    char temp_sect_name[WORD_LENGTH_LIMIT];
    int i = 0;

    clearCharArray(temp_sect_name, WORD_LENGTH_LIMIT);

    file = fopen(filename, "r");

    if (!file) {
        printf("Error: file %s not found or cannot be opened\n", filename);
        return;
    }

    do {
        c = fgetc(file);

        if (c == '\n') {
            if (!validateSection(*sections, temp_sect_name, *current_elements)) {
                reallocateSection(sections, current_elements);
//check if current elements has correct value everywhere (either start @ 0 or 1)
                strcpy((*sections + *current_elements)->name, temp_sect_name);
            }

            clearCharArray(temp_sect_name, i + 1);
            i = 0;
            continue;
        }

        temp_sect_name[i++] = c;
    } while (c != '\n' && c != EOF);

    if (fclose(file) == EOF) {
        printf("Failed to close file %s\n", filename);
        exit(118);
    }
}

//wip
void loadBooks(char filename[WORD_LENGTH_LIMIT], book **books, int *current_elements) {
    FILE *file;
    char readLine[WORD_LENGTH_LIMIT];
    char *token;
    const char s[2] = ";";
    char temp[WORD_LENGTH_LIMIT];
    file = fopen(filename, "r");

    clearCharArray(readLine, WORD_LENGTH_LIMIT);
    clearCharArray(temp, WORD_LENGTH_LIMIT);

    if (!file) {
        printf("Error: File %s not found or cannot be opened\n", filename);
        return;
    }

//moze nie dzialac ze wzgledu na wpakowywanie \n przez fgets
//mozna rozwiazac to jak w fileMngr()
    while (fgets(readLine, sizeof readLine, file) != NULL) {
        printf("%s\n", readLine);
        int inc = 0;
        book *temp_book = (book *) malloc(sizeof(book));

        token = strtok(readLine, s);

        while (token != NULL) {
            switch (inc) {
                case 0:
                    strcpy(temp_book->signature, token);
                    break;
                case 1:
                    strcpy(temp_book->title, token);
                    break;
                case 2:
                    strcpy(temp_book->author_name, token);
                    break;
                case 3:
                    strcpy(temp_book->author_surname, token);
                    break;
                case 4:
                    temp_book->year = atoi(token);
                    break;
                default:
                    printf("Unexpected error\n");
                    exit(666);
            }//switch

            inc++;
            printf("token: %s\n", token);
            strcpy(temp, strtok(NULL, s));
            strcpy(token, strndup(temp, strcspn(temp, "\n")));
            clearCharArray(temp, WORD_LENGTH_LIMIT);
            clearCharArray(token, WORD_LENGTH_LIMIT);
        }
        printf("tokenend: %s\n", token);
        insertBook(books, current_elements, temp_book);
    }

    if (fclose(file) == EOF) {
        printf("Failed to close file %s\n", filename);
        exit(110);
    }

}

//wip
void loadDatabase(char filename[WORD_LENGTH_LIMIT], book **books, section **sections, int *current_book_elements,
                  int *current_section_elements) {
    FILE *file;
    char readLine[1000];
    char *token;
    const char s[2] = ";";
    file = fopen(filename, "r");

    if (!file) {
        printf("Error: File %s not found or cannot be opened\n", filename);
        return;
    }

//jak dziala funkcja wyzej to zastosuje to samo rozwiazanie.
    while (fgets(readLine, sizeof readLine, file) != NULL) {
        printf("%s\n", readLine);
        int inc = 0;
        book *temp_book = (book *) malloc(sizeof(book));
//test if strtok works
        token = strtok(readLine, s);
//wywolaj funkcje dla niego
//counter/incrementator i odpowiednie przypisania.
        while (token != NULL) {
            switch (inc) {
                case 0:
                    strcpy(temp_book->signature, token);
                    break;
                case 1:
                    strcpy(temp_book->title, token);
                    break;
                case 2:
                    strcpy(temp_book->author_name, token);
                    break;
                case 3:
                    strcpy(temp_book->author_surname, token);
                    break;
                case 4:
                    temp_book->year = atoi(token);
                    break;
                case 5:
                    temp_book->sect = (section *) malloc(sizeof(section));
                    int temp_index = 0;
                    temp_index = findSection(*sections, *current_section_elements, token);
                    if (temp_index == -1) {
                        //create new section
                    }
                    else {
                        temp_book->sect = (*sections + temp_index);
                    }
                default:
                    printf("Unexpected error\n");
                    exit(666);
            }//switch

            inc++;
            printf("token: %s\n", token);
            token = strtok(NULL, s);
        }
        printf("tokenend: %s\n", token);
        insertBook(books, current_book_elements, temp_book);
    }

    if (fclose(file) == EOF) {
        printf("Failed to close file %s\n", filename);
        exit(110);
    }

}

void insertBook(book **books, int *current_elements, book *loadedBook) {
    if (!loadedBook) {
        printf("Error: Apparently book failed to load\n");
        return;
    }

    reallocateBooks(books, current_elements);
    (*books + *current_elements) = loadedBook;
}

//test
void saveSections(char filename[WORD_LENGTH_LIMIT], section **sections, int current_elements) {
    FILE *file;
    int i = 0;
    file = fopen(filename, "w"); //diff?
    if (!file) {
        printf("Error: failed to open file %s\n", filename);
        return;
    }

    while (i < current_elements) {
        fprintf(file, "%s\n", (*sections + i)->name);
        i++;
    }

    if (fclose(file) == EOF) {
        printf("Failed to close file %s\n", filename);
        exit(112);
    }
}

//test
void saveBooks(char filename[WORD_LENGTH_LIMIT], book **books, int current_elements) {
    FILE *file;
    int i = 0;
    file = fopen(filename, "w"); //different open mode?

    if (!file) {
        printf("Error: failed to fopen file %s\n", filename);
        return;
    }

    while (i < current_elements) {
        book *temp = (*books + i);
        fprintf(file, "%s;%s;%s;%s;%d\n", temp->signature, temp->title, temp->author_name, temp->author_surname,
                temp->year);
        i++;
    }

    if (fclose(file) == EOF) {
        printf("Failed to close file %s\n", filename);
        exit(111);
    }
}

void saveDatabase(char filename[WORD_LENGTH_LIMIT], book **books, int current_elements) {
    FILE *file;
    int i = 0;
    file = fopen(filename, "w"); //different open mode?

    if (!file) {
        printf("Error: failed to fopen file %s\n", filename);
        return;
    }

    while (i < current_elements) {
        book *temp = (*books + i);
//sprawdz czy NULLowe sekcje cos tu psuja
        fprintf(file, "%s;%s;%s;%s;%d;%s\n", temp->signature, temp->title, temp->author_name, temp->author_surname,
                temp->year, temp->sect->name);
        i++;
    }

    if (fclose(file) == EOF) {
        printf("Failed to close file %s\n", filename);
        exit(115);
    }
}
