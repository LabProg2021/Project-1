#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
#include "src.c"

#define MAX_DESC 30

void insertMenu(List toDo) {
    int loop = 0;
    char* description = (char*) calloc (MAX_DESC, sizeof (char));
    
    printf("Introduza a descrição do cartao: \n");
    scanf("%[^\n]%*c", description);

    // puts(description);

    while(loop == 0) {
        if(strcmp(description, "") == 0) {
            printf("Não introduziu uma descricao. Por favor introduza uma descricao.\n");
            getchar();
            scanf("%[^\n]%*c", description);
        }

        else {
            loop = 1;
        }
    }

    loop = 0;
    short priority;

    printf("Introduza a prioridade do cartão entre 1 e 10: \n");
    
    scanf("%hi", &priority);

    while(loop == 0) {              // Este ciclo está a permitir a injeção de código (caso se introduza uma string)
        if (priority < 1 || priority > 10) {
            printf("Prioridade invalida, por favor introduza um numero entre 1 e 10 \n");
            scanf("%hi", &priority);
            continue;
        }

        else {
            loop = 1;
        }
    }

    insertNode(toDo, createCard(description, priority));
}

void moveMenu(List toDo, List doing) {

}



void editTask(List toDo, List doing, List done) {
    printf("1. Começar a executar a tarefa. \n");
    printf("2. Colocar a tarefa em pausa. \n");
    printf("3. Alterar responsável pela tarefa. \n");
    printf("4. Fechar a tarefa. \n");
    printf("5. Reabrir tarefa. \n");
    printf("0. Voltar ao menu inicial. \n");

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            moveMenu(List toDo, List doing);
            break;
        
        case 2:
            moveMenu(List doing, List toDo);
            break;

        case 3:

            break;

        case 4:

            break;
        
        case 5:

            break;
        
        case 0:
            homepage(toDo, doing, done);
            break;

         default:
            printf("Opção inválida, tente novamente.\n"); 
            break;
    }
}


void printPerson(List toDo, List doing, List done) {
    int loop = 0;
    char* personName = (char*) malloc (sizeof (char)*MAX_DESC);
    
    printf("Introduza o nome da pessoa: \n");
    getchar();
    scanf("%[^\n]%*c", personName);

    while(loop == 0) {
        if(strcmp(personName, "") == 0) {
            printf("Não introduziu um nome. Por favor introduza um nome.\n");
            getchar();
            scanf("%[^\n]%*c", personName);
        }

        else {
            loop = 1;
        }
    }
    printf("                    Tarefas por fazer: \n");
    printByPerson(toDo, personName);
    printf("                    Tarefas a serem feitas: \n");
    printByPerson(doing, personName);
    printf("                    Tarefas concluídas: \n");
    printByPerson(done, personName);
}

void printInfo(List toDo, List doing, List done) {
    printf("1. Visualizar o quadro. \n");
    printf("2. Visualizar todas as tarefas de uma pessoa. \n");
    printf("3. Visualizar todas as tarefas ordenadas por data de criação. \n");
    printf("0. Voltar ao menu inicial. \n")

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("                    Tarefas por fazer: \n");
            printTeste(toDo);

            printf("                    Tarefas a serem feitas: \n");
            printTeste(doing);
            printf("                    Tarefas concluídas: \n");
            printTeste(done);
            break;

        case 2:
            printPerson(toDo, doing, done);
            break;

        case 3:
            printByDate(toDo, doing, done);
            break;

        case 0:
            homepage(toDo, doing, done);
            break;
        
        default:
            printf("Opção inválida, tente novamente.\n"); 
            break;
    }
}

void testMain() {
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
        //printf("toDo List:\n");
        //printTeste(toDo);
        changePerson(toDo, cartao1, "António");
        changePerson(toDo, cartao2, "Pedro");
        changePerson(toDo, cartao3, "Pedro");
        moveToList(toDo, doing, cartao2);
        moveToList(toDo, doing, cartao3);
        moveToList(toDo, doing, cartao1);
        insertNode(done, cartaoDone1);
        insertNode(done, cartaoDone2);
        insertNode(done, cartaoDone3);
        //printf("toDo List:\n");
        //printTeste(toDo);
        //printf("doing List:\n");
       // printTeste(doing);
        //printf("done List:\n");
       // printTeste(done);
        printf("Cartões byPerson: \n");
        printByPerson(toDo, "Pedro");
        printByPerson(doing, "Pedro");
        printByPerson(done, "Pedro");
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
}

int homepage (List toDo, List doing, List done) {
    printf("1. Inserir nova tarefa \n");
    printf("2. Editar tarefas \n");
    printf("3. Visualizar tarefas \n");
    printf("0. Sair \n");

    int choice;
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1:
            insertMenu(toDo);
            break;

        case 2:
            editTask(toDo, doing, done);
        break;

        case 3:
            printInfo(toDo, doing, done);
            break;

        case 0:
            testMain();
            return 0;

        default:
            printf("Opção inválida, tente novamente.\n"); 
            break;
    }

    return 1;
}

