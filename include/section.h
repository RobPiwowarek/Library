#ifndef SECTION_H_INCLUDED
#define SECTION_H_INCLUDED

#include "helpers.h"

typedef struct Section {
    char name[WORD_LENGTH_LIMIT];
} section;

void renameSection(section *, int current_elements, char name[WORD_LENGTH_LIMIT]);

void displaySections(section *, int current_elements);

void createSection(section **, int *current_elements);

void removeSection(section **, int *current_elements, char name[WORD_LENGTH_LIMIT]);

int validateSection(section *, char name[WORD_LENGTH_LIMIT], int current_elements);

int reallocateSection(section **, int *current_elements);

int findSection(section *, int current_elements, char name[WORD_LENGTH_LIMIT]);

#endif
