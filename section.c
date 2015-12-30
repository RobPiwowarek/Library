#include "section.h"

void renameSection(section* sections, int current_elements, char name[WORD_LENGTH_LIMIT]){
int i = 0;
char new_name[WORD_LENGTH_LIMIT];

i = findSection(sections, current_elements, name);
if (i == -1){
printf("Section not found\n");
return;
}

printf("Enter new name:");
scanf("%s", new_name);
while(validateSection(sections, new_name, current_elements)){
printf("\nName already exists. Enter new one:");
scanf("%s", new_name);
}
printf("\n");

strcpy((*(sections+i)).name, new_name);
}

void removeSection(section** sections, int *current_elements, char name[WORD_LENGTH_LIMIT]){
int i = 0, j = 0;
section *newCollection;

i = findSection(*sections, *current_elements, name);
if (i == -1) { 
printf("Section not found\n");
return;
}

newCollection = (section*)malloc((*current_elements-1)*sizeof(section));
if (!newCollection){ printf("removeSection: memory allocation error\n"); exit(4); }

// co jesli j == i == ostatni element?
while (j < *current_elements-1){
if (j != i)
*(newCollection+j) = *(*sections+j);
else if(j == i && j != *current_elements){
*(newCollection+j) = *(*sections+j+1);
}
j++;
}//while

free(*sections);
*sections = newCollection;
*current_elements -= 1;
}

//if section found, returns index
//else returns -1
int findSection(section* sections, int current_elements, char name[WORD_LENGTH_LIMIT]){
int i = 0;

while (i < current_elements){
if (!strcmp((*(sections+i)).name, name)) return i;
i++;
}

return -1;
}

int validateSection(section * sections, char name[WORD_LENGTH_LIMIT], int current_elements){
int i = 0;

while (i < current_elements){
if (strcmp((*(sections+i)).name, name) == 0) return 1;
i++;
}

return 0;
}

int reallocateSection(section** sections, int *current_elements){
section* newCollection;
int i = 0;

newCollection = (section*)malloc((*current_elements+1)*sizeof(section));

if (!newCollection){
printf("reallocateSection: memory allocation error\n");
exit(2);
}

while(i < *current_elements){
*(newCollection+i) = *(*sections+i);
i++;
}

free(*sections);
*sections = newCollection;
*current_elements += 1;
return 0;
}

//increment occurs in reallocateSection
section* createSection(section* sections, int *current_elements){
char temp_name[WORD_LENGTH_LIMIT];
section* new_section;
new_section = (section*)malloc(sizeof(section));

printf("Enter section name: ");
scanf("%s", temp_name);
while (validateSection(sections, temp_name, *current_elements)){
printf("\nSection already exists, please enter a different name:");
scanf("%s", temp_name);
}
printf("\n");
strcpy((*new_section).name, temp_name);

reallocateSection(&sections, current_elements); //increment CE
*(sections+*current_elements) = *new_section;
return new_section;
}
