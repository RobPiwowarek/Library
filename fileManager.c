#include "fileManager.h"
#include "helpers.h"
#include "book.h"

//wip
void loadBooks(char filename[WORD_LENGTH_LIMIT], book** books, int *current_elements){
FILE * file;
char readLine[1000];
char *token;
const char s[2] = ";";
file = fopen(filename, 	"r");

if (!file){
printf("Error: File %s not found or cannot be opened\n", filename);
return;
}

//todo:
//wczytaj linie, rodziel na tokeny, wczytaj do books, 
while(fgets(line, sizeof line, file) != NULL){
printf("%s\n", line);
int inc = 0;
book* temp_book = (book*)malloc(sizeof(book));
//test if strtok works
token = strtok(line, s);
//wywolaj funkcje dla niego
//counter/incrementator i odpowiednie przypisania.
while (token != NULL){
switch(i){
case 0:  strcpy(temp_book->signature, token); break;
case 1: strcpy(temp_book->title, token); break;
case 2: strcpy(temp_book->author_name, token); break;
case 3: strcpy(temp_book->author_surname, token); break;
case 4: temp_book->year = atoi(token);
default: printf("Unexpected error\n"); exit(666);
}//switch

i++;
printf("token: %s\n", token);
token = strtok(NULL, s);
}
printf("tokenend: %s\n", token);
insertBook(books, current_elements, temp_book);
}

if (fclose(file) == EOF) {
printf("Failed to close file %s\n", filename);
exit(110);
}

}

void insertBook(book** books, int *current_elements, book* loadedBook){
if (!loadedBook){
printf("Error: Apparently book failed to load\n");
return;
}

reallocateBooks(books, current_elements);
(*books+i) = loadedBook;
}

//test
void saveSections(char filename[WORD_LENGTH_LIMIT], section** sections, int current_elements){
FILE * file;
int i = 0;
file = fopen(filename, "w"); //diff?
if (!file){
printf("Error: failed to open file %s\n", filename);
return;
}

while (i < current_elements){
fprintf(file, "%s\n", (*sections+i)->name);
i++;
}

if (fclose(file)==EOF){
printf("Failed to close file %s\n", filename);
exit(112);
}
}
//test
void saveBooks(char filename[WORD_LENGTH_LIMIT], book** books, int current_elements){
FILE * file;
int i = 0;
file = fopen(filename, "w"); //different open mode?

if (!file){
printf("Error: failed to fopen file %s\n", filename);
return;
}

while (i < current_elements){
book* temp = (*books+i);
fprintf(file, "%s;%s;%s;%s;%d\n", temp->signature, temp->title, temp->author_name, temp->author_surname, temp->year);
i++;
}

if (fclose(file)==EOF){
printf("Failed to close file %s\n", filename);
exit(111);
}
}
