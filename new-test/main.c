#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "src.c"

int main(int argc, char const *argv[])
{
    Card* cardA = createCard(1);
    cardA->title = "This is the first card";

    Card* cardB = createCard(2);
    cardB->title = "This is the second card";

    Card* cardC = createCard(3);
    cardC->title = "This is the third card";

    List* listA = createList();
    insertNode(listA, cardA);
    insertNode(listA, cardB);
    insertNode(listA, cardC);
    printList(listA);
 
    /*
    insertOrderTask(toDo, cartao);
    insertOrderTask(toDo, cartao2);
    insertOrderTask(toDo, cartao4);
    insertOrderTask(toDo, cartao3);
    moveDoing(toDo, Doing, 40);
    moveDoing(toDo, Doing, 3);
    printOrderedBoard(toDo);
    printOrderedBoard(Doing);
    */
    return 0;
}
