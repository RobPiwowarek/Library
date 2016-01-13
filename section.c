#include "section.h"

void displaySections(section *sections, int current_elements) {
    int i = 0;
    while (i < current_elements) {
        printf("%s\n", (sections + i)->name);
        i++;
    }//while
}

void renameSection(section *sections, int current_elements, char name[WORD_LENGTH_LIMIT]) {
    int i = 0;
    char new_name[WORD_LENGTH_LIMIT];

    i = findSection(sections, current_elements, name);
    if (i == -1) {
        printf("Section not found\n");
        return;
    }

    printf("Enter new name:");
    fgets(new_name, WORD_LENGTH_LIMIT, stdin);
    new_name[strcspn(new_name, "\n")] = '\0';

    while (validateSection(sections, new_name, current_elements)) {
        printf("\nName already exists. Enter new one:");
        fgets(new_name, WORD_LENGTH_LIMIT, stdin);
        new_name[strcspn(new_name, "\n")] = '\0';

    }
    printf("\n");

    strcpy((*(sections + i)).name, new_name);
}

void removeSection(section **sections, int *current_elements, char name[WORD_LENGTH_LIMIT]) {
    int i = 0, j = 0;
    section *newCollection;

    i = findSection(*sections, *current_elements, name);
    if (i == -1) {
        printf("Section not found\n");
        return;
    }

    newCollection = (section *) malloc((*current_elements - 1) * sizeof(section));
    if (!newCollection) {
        printf("removeSection: memory allocation error\n");
        exit(4);
    }

    while (j < *current_elements - 1) {
        if (j != i)
            *(newCollection + j) = *(*sections + j);
        else if (j == i && j != *current_elements) {
            *(newCollection + j) = *(*sections + j + 1);
        }
        j++;
    }//while

    free(*sections);
    *sections = newCollection;
    *current_elements -= 1;
}

//if section found, returns index
//else returns -1
int findSection(section *sections, int current_elements, char name[WORD_LENGTH_LIMIT]) {
    int i = 0;

    while (i < current_elements) {
        printf("porownanie: %s z %s \n", (*(sections + i)).name, name);
        if (!strcmp((*(sections + i)).name, name)) return i;
        i++;
    }

    return -1;
}

int validateSection(section *sections, char name[WORD_LENGTH_LIMIT], int current_elements) {
    int i = 0;

    while (i < current_elements) {
        if (strcmp((*(sections + i)).name, name) == 0) return 1;
        i++;
    }

    return 0;
}

int reallocateSection(section **sections, int *current_elements) {
    section *newCollection;
    int i = 0;

    newCollection = (section *) malloc((*current_elements + 1) * sizeof(section));

    if (!newCollection) {
        printf("reallocateSection: memory allocation error\n");
        exit(2);
    }

    while (i < *current_elements) {
        *(newCollection + i) = *(*sections + i);
        i++;
    }

    if (*sections != NULL)
        free(*sections);

    *sections = newCollection;

    *current_elements += 1;
    return 0;
}

//increment occurs in reallocateSection
void createSection(section **sections, int *current_elements) {
    char temp_name[WORD_LENGTH_LIMIT];
    section *new_section;
    new_section = (section *) malloc(sizeof(section));

    clearCharArray(temp_name, WORD_LENGTH_LIMIT);

    if (!new_section) {
        printf("createSection: memory allocation error\n");
        exit(7);
    }

    printf("Enter section name: ");
    fgets(temp_name, WORD_LENGTH_LIMIT, stdin);
    temp_name[strcspn(temp_name, "\n")] = '\0';
    printf("create: %s\n", temp_name);

    while (validateSection(*sections, temp_name, *current_elements)) {
        printf("\nSection already exists, please enter a different name:");
        fgets(temp_name, WORD_LENGTH_LIMIT, stdin);
        temp_name[strcspn(temp_name, "\n")] = '\0';
    }
    printf("\n");
    strcpy(new_section->name, temp_name);

    reallocateSection(sections, current_elements); //increment CE
    *(*sections + (*current_elements - 1)) = *new_section;
}
