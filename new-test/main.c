#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "data.h"
//#include "menu.c"
#include "src.c"

#define MAX_DESCRIPTION 30

void testInsert(List toDo) {
    
    char* description = (char*) malloc (sizeof (char)*MAX_DESCRIPTION);

        printf("Introduza a descrição do cartao: \n");

        scanf("%[^\n]%*c", description);
        //puts(description);

        if(strcmp(description, "\n")) {
            printf("Não introduziu uma descricao. Por favor introduza uma descricao.\n");
            getchar();
            scanf("%[^\n]%*c", description);
        }

        short priority;

        printf("Introduza a prioridade do cartao: \n");
        scanf("%hu", &priority);

        if (priority < 1 || priority > 10)
        {
            printf("Prioridade invalida, por favor introduza um numero entre 1 e 10 \n");
            scanf("%hu", &priority);
        }

        insertNode(toDo, createCard(description, priority));


}

void testMain() {
    Card* cartao0, cartao1, cartao2, cartao3, cartao4, cartaoDone1, cartaoDone2, cartaoDone3;
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
}

int main(int argc, char *argv[]) {
    List toDo = createList(1);
    List doing = createList(2);
    List done = createList(3);


    newCard->id           = ID;
    newCard->creationDate = curDate;
    newCard->description  = description;
    newCard->priority     = priority;
    newCard->person       = nullName;
    newCard->deadline     = nullDate;
    newCard->concluDate   = nullDate;





    printf("1. Inserir nova tarefa \n");
    printf("2. Editar tarefas \n"); // Encontrar novo nome
    printf("3. Visualizar tarefas \n");
    printf("0. Sair \n");

    int choice;
    scanf("%d", &choice);
    getchar();

    switch (choice) {
    case 1:
        testInsert(toDo);

    break;

    case 2:
        /* Inserir código para caso 2 */
        break;

    case 3:
        /* Inserir código para caso 3 */
        break;

    case 0:
        // free(); /* O free pode ser dado apenas quando se termina o código */
        testMain();
    }

    return 0;
}

/*
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
*/