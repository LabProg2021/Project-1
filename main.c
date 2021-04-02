#include <stdio.h>
#include <stdlib.h>
#include "data.h"
//#include "src.c"
#include "menu.c"

int main(int argc, char const *argv[]) {
    List toDo = createList(1);
    List doing = createList(2);
    List done = createList(3);

    int var = 1;
    while(var == 1) {
        var = homepage(toDo, doing, done);
    }

    return 0;
}

/*
int main(int argc, char const *argv[]) {
    Card *cartao0, *cartao1, *cartao2, *cartao3, *cartao4, *cartaoDone1, *cartaoDone2, *cartaoDone3;
    List toDo = createList(1);
    List doing = createList(2);
    List done = createList(3);

    cartao0 = createCard("Teste 1", 10);
    cartao1 = createCard("Teste 2", 5);
    cartao2 = createCard("Teste 3", 2);
    cartao3 = createCard("Teste 4", 5);
    cartao4 = createCard("Teste 5", 5);
    cartaoDone1 = createCard("Important Task", 10);
    cartaoDone2 = createCard("Important Task", 7);
    cartaoDone3 = createCard("Important Task", 8);

    insertNode(toDo, cartao0);
    insertNode(toDo, cartao1);
    insertNode(toDo, cartao2);
    insertNode(toDo, cartao3);
    insertNode(toDo, cartao4);
    printf("toDo List:\n");
    printTeste(toDo);
    changePerson(toDo, cartao1, "António");
    changePerson(toDo, cartao2, "Pedro");
    changePerson(toDo, cartao3, "Pedro");
    moveToList(toDo, doing, cartao2);
    moveToList(toDo, doing, cartao3);
    moveToList(toDo, doing, cartao1);
    insertNode(done, cartaoDone1);
    insertNode(done, cartaoDone2);
    insertNode(done, cartaoDone3);
    printf("toDo List:\n");
    printTeste(toDo);
    printf("doing List:\n");
    printTeste(doing);
    printf("done List:\n");
    printTeste(done);
    printf("Cartões byPerson: \n");
    printByPerson(toDo, doing, done, "Pedro");
    printf("Listas byDates: \n");
    printByDate(toDo, doing, done);
    printf("toDo List:\n");
    printTeste(toDo);
    printf("done List:\n");
    printTeste(done);
    printf("doing List:\n");
    printTeste(doing);
    printf("%s -> ", cartao1->person);
    changePerson(doing, cartao1, "Ana");
    printf("%s\n", cartao1->person);
    printf("doing List:\n");
    printTeste(doing);
    saveFile(toDo, doing, done);
    changePerson(doing, cartao1, "Edgar");
    saveFile(toDo, doing, done);
    return 0;
}
*/