#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "src.c"

int main(int argc, char const *argv[]) {
    Card cartao0, cartao1, cartao2, cartao3, cartao4;
    List toDo = createList(1);
    List doing = createList(2);
    //List done = createList(3);

    cartao0.id = 0;
    cartao0.title = "Teste 0";
    cartao0.person = "Pedro";
    cartao0.state = 1;
    cartao0.priority = 4;
    cartao0.creatDate.day = 30;

    cartao1.id = 1;
    cartao1.title = "Teste 1";
    cartao1.person = "Manuel";
    cartao1.state = 1;
    cartao1.priority = 3;
    cartao1.creatDate.day = 30;

    cartao2.id = 2;
    cartao2.title = "Teste 2";
    cartao2.person = "António";
    cartao2.state = 1;
    cartao2.priority = 10;
    cartao2.creatDate.day = 30;

    cartao3.id = 3;
    cartao3.title = "Teste 3";
    cartao3.person = "Joaquim";
    cartao3.state = 1;
    cartao3.priority = 2;
    cartao3.creatDate.day = 30;

    cartao4.id = 4;
    cartao4.title = "Teste 4";
    cartao4.person = "José";
    cartao4.state = 1;
    cartao4.priority = 6;
    cartao4.creatDate.day = 30;

    insertOrderTask(toDo, cartao1);
    insertOrderTask(toDo, cartao0);
    insertOrderTask(toDo, cartao2);
    insertOrderTask(toDo, cartao4);
    insertOrderTask(toDo, cartao3);
    printTeste(toDo);
    moveToList(toDo, doing, 2);
    moveToList(toDo, doing, 3);
    moveToList(toDo, doing, 1);
    printTeste(toDo);
    printTeste(doing); //ordenação da lista doing ainda não está implementada
    moveToList(doing, toDo, 1);

    return 0;
}
