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

    cartao0 = createCard("Teste 1", 10, "António", &date1, &nullDate);
    cartao1 = createCard("Teste 2", 5, "Manuel", &date2, &nullDate);
    cartao2 = createCard("Teste 3", 2, "Pedro", &date1, &nullDate);
    cartao3 = createCard("Teste 4", 5, "Abc", &date1, &nullDate);
    cartao4 = createCard("Teste 5", 5, "Pedro", &date3, &nullDate);
    cartaoDone1 = createCard("Important Task", 10, "Hugo", &date1, &date3);
    cartaoDone2 = createCard("Important Task", 7, "Pedro", &date1, &date2);
    cartaoDone3 = createCard("Important Task", 8, "José", &date1, &date1);

    insertNode(toDo, &cartao0);
    insertNode(toDo, &cartao1);
    insertNode(toDo, &cartao2);
    insertNode(toDo, &cartao3);
    insertNode(toDo, &cartao4);
    printf("toDo List:\n");
    printTeste(toDo);
    moveToList(toDo, doing, &cartao2);
    moveToList(toDo, doing, &cartao3);
    moveToList(toDo, doing, &cartao1);
    insertNode(done, &cartaoDone1);
    insertNode(done, &cartaoDone2);
    insertNode(done, &cartaoDone3);
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
    printf("%s -> ", cartao1.person);
    changePerson(doing, &cartao1, "Ana");
    printf("%s\n", cartao1.person);
    printf("doing List:\n");
    printTeste(doing);
    
    return 0;
}
