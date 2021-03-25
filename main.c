#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "src.c"

int main(int argc, char const *argv[])
{
    //List Done = createList();

    Card cartao;
    Card cartao2;
    Card cartao3;
    Card cartao4;
    List toDo = createList();
    List Doing = createList();

    cartao.id = 1;
    cartao.title = "Olá Mun";
    cartao.person = "Eu";
    cartao.state = 1;
    cartao.priority = 1;
    cartao.creatDate.day = 30;

    cartao2.id = 20;
    cartao2.title = "Olá Mundo";
    cartao2.person = "Eu";
    cartao2.state = 1;
    cartao2.priority = 1;
    cartao2.creatDate.day = 30;

    cartao3.id = 3;
    cartao3.title = "Olá World";
    cartao3.person = "Eu";
    cartao3.state = 1;
    cartao3.priority = 1;
    cartao3.creatDate.day = 30;

    cartao4.id = 40;
    cartao4.title = "Olá World";
    cartao4.person = "Eu";
    cartao4.state = 1;
    cartao4.priority = 1;
    cartao4.creatDate.day = 30;

    insertOrderTask(toDo, cartao);
    insertOrderTask(toDo, cartao2);
    insertOrderTask(toDo, cartao4);
    insertOrderTask(toDo, cartao3);
    moveDoing(toDo, Doing, 40);
    moveDoing(toDo, Doing, 3);
    printOrderedBoard(toDo);
    printOrderedBoard(Doing);
    return 0;
}
