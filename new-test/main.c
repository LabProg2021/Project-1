#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "src.c"

int main(int argc, char const *argv[])
{
    short xA = 1;  
    short* yA = &xA;
    Card* cardA = createCard("This is cardA", yA);

    short xB = 1;
    short* yB = &xB;
    Card* cardB = createCard("This is cardB", yB);

    short xC = 1;
    short* yC = &xC;
    Card* cardC = createCard("This is cardC", yC);

    List* listA = createList();
    insertNode(listA, cardA);
    insertNode(listA, cardB);
    insertNode(listA, cardC);
    printList(listA);

    return 0;
}
