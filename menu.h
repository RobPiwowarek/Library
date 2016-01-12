#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "book.h"
#include "section.h"
#include "helpers.h"

void menu(book**, int*, section**, int*);
void fileMngr(book**, int, section**, int); //file manager options
void books(book**, int, section**, int); 
void sections(section**, int);
void about(); //author etc.
void bDisplayMenu(book**, int*);

#endif
