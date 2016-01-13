#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "book.h"
#include "section.h"
#include "helpers.h"

void menu(book **, int *, section **, int *);

void fileMngr(book **, int *, section **, int *); //file manager options

void books(book **, int *, section **, int *); //book-related options

void sections(section **, int *); //section-related options

void about(); //author etc.

void bDisplayMenu(book **, int, section **, int); //book-display menu

#endif
