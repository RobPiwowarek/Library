#include "menu.h"

void menu(book** books, int* current_book_elements, section** sections, int* current_section_elements){
int choice = 0;

printf("Choose an option:\n");
printf("1) Manage books\n");
printf("2) Manage sections\n");
printf("3) Save/Load\n");
printf("I choose: ");

//idiotoodpornosc
scanf("%d", &choice);
printf("\n");

switch(choice){
case 1: books(books, current_book_elements, sections, current_section_elements); break;
case 2: sections(sections, current_section_elements); break;
case 3: fileMngr(); break;
default: printf("Error: menu -> something went wrong\n"); 
}
}

void books(book** books, int* current_book_elements, section** sections, int* current_section_elements){
int choice = 0;
while(1){
printf("Book Managment Menu\n");
printf("1) Create book\n2) Modify book\n3) Remove book\n4) Display\n5)Back\n");
printf("Choose an option: ");
scanf("%d", &choice);
printf("\n");
switch(choice){
case 1: createBook(books, current_book_elements); break;
case 2: modifyBook(*books, current_book_elements); break;
case 3: char sig[SIG_LENGTH_LIMIT];
        if (*current_book_elements == 0){
        printf("There are no books to remove\n");
        break;
        }
        clearCharArray(sig, SIG_LENGTH_LIMIT);
        printf("Enter signature of the book you want to remove\n")
        scanf("%s", sig);
        while (validateSignature(sig)){
        printf("Incorrect signature\n");
        printf("Please reenter\n");
        clearCharArray(sig, SIG_LENGTH_LIMIT);
        scanf("%s", sig);
        }
        removeBook(books, current_book_elements, sig);
        break;
case 4: bDisplayMenu(books, current_book_elements); break;
case 5: return;
default: printf("Incorrect input.\n");
}//switch

}//while
}

void about(){
printf("Program created by Robert Piwowarek for PRI laboratories\n");
printf("Group: 1I2\n");
printf("Library - save, load, create book records and group them by sections\n");
}
