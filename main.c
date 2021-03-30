#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "src.c"

int main(int argc, char const *argv[]) {
    Card cartao0, cartao1, cartao2, cartao3, cartao4, cartaoDone1, cartaoDone2, cartaoDone3;
    List toDo = createList(1);
    List doing = createList(2);
    List done = createList(3);

    Date date1 = createDate(2021, 4, 15);
    Date date2 = createDate(2021, 4, 10);
    Date date3 = createDate(2021, 3, 10);
    Date nullDate;

    cartao0 = createCard("Teste 1", 1, "Pedro", &date1, &nullDate);
    cartao1 = createCard("Teste 2", 4, "Manuel", &date1, &nullDate);
    cartao2 = createCard("Teste 3", 10, "António", &date1, &nullDate);
    cartao3 = createCard("Teste 4", 7, "Abc", &date1, &nullDate);
    cartao4 = createCard("Teste 5", 5, "Pedro", &date1, &nullDate);
    cartaoDone1 = createCard("Important Task", 10, "Hugo", &date1, &date3);
    cartaoDone2 = createCard("Important Task", 7, "Pedro", &date1, &date2);
    cartaoDone3 = createCard("Important Task", 8, "José", &date1, &date1);

    //printf("%d\n", cartao1.creationDate.year);

    insertNode(toDo, &cartao0);
    insertNode(toDo, &cartao1);
    insertNode(toDo, &cartao2);
    insertNode(toDo, &cartao3);
    insertNode(toDo, &cartao4);
    printf("toDo List:\n");
    printTeste(toDo);
    moveToList(toDo, doing, 2);
    moveToList(toDo, doing, 3);
    moveToList(toDo, doing, 1);
    insertNode(done, &cartaoDone1);
    insertNode(done, &cartaoDone2);
    insertNode(done, &cartaoDone3);
    printf("toDo List:\n");
    printTeste(toDo);
    printf("doing List:\n");
    printTeste(doing);
    //printf("%c\n", doing->next->info->person[0]);
    printf("done List:\n");
    printTeste(done);
    printf("Ordenado por pessoa: \n");
    printByPerson(toDo, doing, done, "Pedro");

    return 0;
}
