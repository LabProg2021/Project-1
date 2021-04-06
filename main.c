#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "menu.c"

int main(int argc, char const *argv[]) {
    List toDo = createList(1);
    List doing = createList(2);
    List done = createList(3);

    readFile(toDo, doing, done);
    
    homepage(toDo, doing, done);


    return 0;
}
