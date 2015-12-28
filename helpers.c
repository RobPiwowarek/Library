#include "helpers.h"

void clearCharArray(char *array, int size){
int i = 0;
while (i < size){
*(array+i) = '\0';
i++;
}
}

void clearBuffer(){
while(getchar()!='\n'){}
}
