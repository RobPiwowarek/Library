#include "menu.h"

void menu(){
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
case 1: books(); break;
case 2: sections(); break;
case 3: fileMngr(); break;
default: printf("Error: menu -> something went wrong\n"); 
}
}
