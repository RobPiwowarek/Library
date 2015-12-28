#include "helpers.h"
#include "book.h"
#include "section.h"

int main(void){
book* library = NULL;
section* sections = NULL;
int lib_elements = 0, sect_elements = 0;


for (int i = 0; i < 5; i++)
createBook(&library, &lib_elements);
printBook(*library);
printf("%d\n", lib_elements);



return 0;
}
