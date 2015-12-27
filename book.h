#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include "section.h"
#include "helpers.h"

#define SIG_LENGTH_LIMIT 9
#define CURRENT_YEAR 2015

typedef struct Book{
char title[WORD_LENGTH_LIMIT];
char author_name[WORD_LENGTH_LIMIT];
char author_surname[WORD_LENGTH_LIMIT];
char signature[SIG_LENGTH_LIMIT];
section *sect;
int year; //when it got published
} book;

void createBook(book*, int *current_elements); //test
void removeBook(book*, int *current_elements, char sig[SIG_LENGTH_LIMIT]);
void printBook(book*);
void setTitle(book*);
void setAuthorName(book*);
void setAuthorSurname(book*);
void setYear(book*);
void setSection(book*, section*, int current_section_elements);//WiP
void setSignature(book*, book*, int current_elements);
int findBook(book*, int current_elements, char sig[SIG_LENGTH_LIMIT]);
int validateSignature(char sig[SIG_LENGTH_LIMIT]);
int isSignatureUnique(char sig[SIG_LENGTH_LIMIT], book*, int current_elements);
int validateYear(book*);
int reallocateBooks(book*, int *current_elements); //test

#endif