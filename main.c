#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "src.c"

int main(int argc, char const *argv[]) {
    Card cartao0, cartao1, cartao2, cartao3, cartao4;
    List toDo = createList(1);
    List doing = createList(2);
    List done = createList(3);

    cartao0 = *(createCard("Teste 1", 1, "Pedro"));
    cartao1 = *(createCard("Teste 2", 4, "Manuel"));
    cartao2 = *(createCard("Teste 3", 10, "Pedro"));
    cartao3 = *(createCard("Teste 4", 7, "Joaquim"));
    cartao4 = *(createCard("Teste 5", 5, "José"));

    insertNode(toDo, &cartao1);
    insertNode(toDo, &cartao0);
    insertNode(toDo, &cartao2);
    insertNode(toDo, &cartao4);
    insertNode(toDo, &cartao3);
    //printTeste(toDo);
    moveToList(toDo, doing, 2);
    moveToList(toDo, doing, 3);
    moveToList(toDo, doing, 1);
    moveToList(toDo, done, 0);
    printTeste(toDo);
    printTeste(doing);
    printTeste(done);
    moveToList(doing, toDo, 1);
    printPerson(toDo, doing, done, "Pedro");

    return 0;
}
