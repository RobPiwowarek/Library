#ifndef FILEMANAGER_INCLUDED
#define FILEMANAGER_INCLUDED

#include "helpers.h"
#include "book.h"
#include "section.h"

//save and load from 3 files only katalog.txt, pozycje.txt, baza.txt
void loadDatabase(char filename[WORD_LENGTH_LIMIT], book **, section **, int *current_book_elements,
                  int *current_section_elements); //todo
void loadSections(char filename[WORD_LENGTH_LIMIT], section **, int *current_elements); //todo
void loadBooks(char filename[WORD_LENGTH_LIMIT], book **, int *current_elements);

//todo save headers, need to think
void saveSections(char filename[WORD_LENGTH_LIMIT], section **, int current_elements);

void saveBooks(char filename[WORD_LENGTH_LIMIT], book **, int current_elements);

void saveDatabase(char filename[WORD_LENGTH_LIMIT], book **, int current_elements);

void insertBook(book **books, int *current_elements, book *loadedBook);
