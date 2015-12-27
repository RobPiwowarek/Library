#ifndef SECTION_H_INCLUDED
#define SECTION_H_INCLUDED

#include "helpers.h"

typedef struct Section{
char name[WORD_LENGTH_LIMIT];
}section;

section* createSection(section *, int *current_elements); //test if working correctly after inc
void removeSection(section*, int *current_elements, char name[WORD_LENGTH_LIMIT]); //test if working correct after dec
int validateSection(section *, char name[WORD_LENGTH_LIMIT], int current_elements); 
int reallocateSection(section *, int *current_elements);//test if working correctly after inc
int findSection(section *, int current_elements, char name[WORD_LENGTH_LIMIT]);

#endif