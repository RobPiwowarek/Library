#include "book.h"

void removeBook(book* books, int *current_elements, char sig[SIG_LENGTH_LIMIT]){
int i = 0, j = 0;
book *newCollection;

i = findBook(books, *current_elements, sig);
if (i == -1) {
printf("Book not found\n");
return;
}

newCollection = (book*)malloc((*current_elements-1)*sizeof(book));
if (!newCollection){
printf("removeBook: memory allocation error\n");
exit(6);
}

while (j < *current_elements){
if(j!=i) *(newCollection+j)=*(books+j);
else if(j == i && i != *current_elements) *(newCollection+j)=*(books+j+1);
j++;
}//while

free(books);
books = newCollection;
*current_elements -= 1;
}

// returns -1 if not found
// returns index if found
int findBook(book* books, int current_elements, char sig[SIG_LENGTH_LIMIT]){
int i = 0;
while (i < current_elements){
if (!strcmp((*(books+i)).signature, sig)) return i;
i++;
}

return -1;
}

//maybe set section here?
void createBook(book* books, int *current_elements){
book* newBook;

newBook = (book*)malloc(sizeof(book));

if(!newBook){
printf("createBook: memory allocation error\n");
exit(3);
}

setTitle(newBook);
setAuthorName(newBook);
setAuthorSurname(newBook);
setYear(newBook);
setSignature(newBook, books, *current_elements);

reallocateBooks(books, current_elements);//incremenet CE
*(books+*current_elements) = *(newBook);

printf("Book\n");
printBook(newBook);
printf("Created.\n");
}

//todo: test
int reallocateBooks(book* books, int *current_elements){
int i = 0;
book* newCollection;
newCollection = (book*)malloc((*current_elements+1)*sizeof(book));
if (!newCollection) {
printf("reallocateBooks: memory allocation error\n");
exit(1);
}

while (i < *current_elements){
*(newCollection+i)=*(books+i);
i++;
}//while

free(books);
books = newCollection;
*current_elements += 1;
return 0;
}

void printBook(book *b1){
printf("%s %s %s %s %d %s\n", b1->title, b1->author_name, b1->author_surname, b1->signature, b1->year, b1->sect->name);
}

//WIP
void setSection(book *b1, section *sects, int current_section_elements){
//char choice; //incase of creating new sections?
char temp_name[WORD_LENGTH_LIMIT];
int temp_index = 0;

printf("What section does the book belong to?(enter name):");
scanf("%s", temp_name);
printf("\n");

//room for improvement, if sect doesnt exist maybe create a new one?
//maybe change all CE to pointers for easier manipulation?
if (validateSection(sects, temp_name, current_section_elements)){
printf("Section with that name does not exist\n");
return;
}
else {
//set the section?
//different function to look for section index?
temp_index = findSection(sects, current_section_elements, temp_name);
b1->sect = (sects+temp_index);
}
}

void setTitle(book *b1){
printf("\nEnter book title: ");
scanf("%s", b1->title);
printf("\n");
}

void setAuthorName(book *b1){
printf("\nEnter author name: ");
scanf("%s", b1->author_name);
printf("\n");
}

void setAuthorSurname(book *b1){
printf("\nEnter author surname: ");
scanf("%s", b1->author_surname);
printf("\n");
}

void setYear(book *b1){
while (validateYear(b1)){
printf("Please enter correct values\n");
}
}

void setSignature(book *b1, book *books, int current_elements){
char temp_sig[SIG_LENGTH_LIMIT];
printf("\nEnter signature(format AAAA0000):");
scanf("%s", temp_sig);
while (validateSignature(temp_sig) || isSignatureUnique(temp_sig, books, current_elements)){
printf("\nSignature invalid(correct format AAAA0000) or entered signature already exists in the database\n");
printf("Please reenter signature: ");
scanf("%s", temp_sig);
}
printf("\n");
strcpy(b1->signature, temp_sig);
}

int isSignatureUnique(char sig[SIG_LENGTH_LIMIT], book *books, int current_elements){
int i = 0;
while (i < current_elements){
if (!strcmp(sig, (*(books+i)).signature)) return 1;
}
return 0;
}

// check if "looks similiar" to AAAA0000
int validateSignature(char sig[SIG_LENGTH_LIMIT]){
int i = 0, j = 4;
while (i < SIG_LENGTH_LIMIT){
if (i-j < 0){
if (sig[i] < 'A' || sig[i] > 'Z') return 1;
}//if 
else {
if (sig[i] < '0' || sig[i] > '9') return 1;
}//else

i++;
}//while

return 0;
}

// czy na pewno if dobrze działa?
int validateYear(book *b1){
int temp_year = 0;
printf("Enter publication year: ");
if (!scanf("%d", &temp_year)){
printf("\nIncorrect input data.\n");
return 1;
}
else {
if (temp_year > CURRENT_YEAR) {
printf("Year has to be an integer <= CURRENT_YEAR(%d)\n", CURRENT_YEAR);
return 1;
}
}

b1->year = temp_year;
return 0;
}
