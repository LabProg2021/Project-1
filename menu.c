#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
#include "src.c"

#define MAX_DESC 30
#define MAX_TASK 20

void insertMenu(List toDo) {
    char* description = (char*) calloc (MAX_DESC, sizeof (char));

    printf("Introduza a descrição do cartao: \n");
    scanf("%[^\n]%*c", description);

    while(strcmp(description, "") == 0) {
        printf("Não introduziu uma descricao. Por favor introduza uma descricao.\n");
        getchar();
        scanf("%[^\n]%*c", description);
    }

    short priority;

    printf("Introduza a prioridade do cartão entre 1 e 10: \n");
    scanf("%hi", &priority);

    // Este ciclo está a permitir a injeção de código (caso se introduza uma string)
    while(priority < 1 || priority > 10) {
        printf("Prioridade invalida, por favor introduza um numero entre 1 e 10 \n");
        scanf("%hi", &priority);
        continue;
    }

    if(listSize(toDo) < MAX_TASK) {
        insertNode(toDo, createCard(description, priority));
    }
}

void moveMenu(List listO, List listD) {
    List list = listO;
    ListNode temp = *(list);
    list = list->next;
    int i = 1;
    while(list) {
        printf("%i. ", i);
        printTask(list);
        list = list->next;
        i++;
    }
    list = temp.next;

    int choice;
    printf("Selecione tarefa a mover: ");
    scanf("%d", &choice);
    
    for(int i=1; i<choice; i++) {
        list = list->next;
    }

    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    Date curDate = createDate(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday);

    if(listO->flag == 1) {
        char* newPerson = (char*) malloc (sizeof (char)*MAX_DESC);
        printf("Atribua um responsável: ");
        scanf("%s", newPerson);
        changePerson(listO, list->info, newPerson);

        printf("Atribua uma data limite de conclusão (dd mm aaaa): ");
        scanf("%hd %hd %hd", &(list->info->deadline.day), &(list->info->deadline.month), &(list->info->deadline.year));
        
        //controlo de input
        if(list->info->deadline.year < curDate.year) {
            printf("Atribua uma data limite de conclusão válida (dd mm aaaa): ");
            scanf("%hd %hd %hd", &(list->info->deadline.day), &(list->info->deadline.month), &(list->info->deadline.year));
        } //INCOMPLETO

    } else if(listO->flag == 2) {
        list->info->concluDate = curDate;
    } else {
        Date nullDate = createDate(0, 0, 0);
        list->info->concluDate = nullDate;
    }

    moveToList(listO, listD, list->info);
}

void changePersonMenu(List doing) {
    List list = doing;
    ListNode temp = *(list);
    list = list->next;
    int i = 1;
    while(list) {
        printf("%i. ", i);
        printTask(list);
        list = list->next;
        i++;
    }
    list = temp.next;

    int choice;
    printf("Selecione tarefa onde quer alterar o responsável: ");
    scanf("%d", &choice);

    char* newPerson = (char*) malloc (sizeof (char)*MAX_DESC);

    printf("Introduza o nome do novo responsável: ");
    scanf("%s", newPerson);
    changePerson(doing, list->info, newPerson);
}

void editTask(List toDo, List doing, List done) {
    printf("1. Começar a executar a tarefa. \n");
    printf("2. Colocar a tarefa em pausa. \n");
    printf("3. Alterar responsável pela tarefa. \n");
    printf("4. Concluir tarefa. \n");
    printf("5. Reabrir tarefa. \n");
    printf("0. Voltar ao menu inicial. \n");

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("--------------------------\n");
            moveMenu(toDo, doing);
            break;
        
        case 2:
            printf("--------------------------\n");
            moveMenu(doing, toDo);
            break;

        case 3:
            printf("--------------------------\n");
            changePersonMenu(doing);
            break;

        case 4:
            printf("--------------------------\n");
            moveMenu(doing, done);
            break;
        
        case 5:
            printf("--------------------------\n");
            moveMenu(done, toDo);
            break;
        
        case 0:
            printf("--------------------------\n");
            homepage(toDo, doing, done);
            break;

         default:
            printf("--------------------------\n");
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
    printf("0. Voltar ao menu inicial. \n");

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("--------------------------\n");
            printf("                    Tarefas por fazer: \n");
            printList(toDo);

            printf("                    Tarefas a serem feitas (%d/%d): \n", listSize(doing), MAX_TASK / 2);
            printList(doing);
            printf("                    Tarefas concluídas: \n");
            printList(done);
            break;

        case 2:
            printf("--------------------------\n");
            printPerson(toDo, doing, done);
            break;

        case 3:
            printf("--------------------------\n");
            printByDate(toDo, doing, done);
            break;

        case 0:
            printf("--------------------------\n");
            homepage(toDo, doing, done);
            break;
        
        default:
            printf("--------------------------\n");
            printf("Opção inválida, tente novamente.\n"); 
            break;
    }
}

void homepage (List toDo, List doing, List done) {
    printf("1. Inserir nova tarefa \n");
    printf("2. Editar tarefas \n");
    printf("3. Visualizar tarefas \n");
    printf("9. Sair \n");
    printf("0. Guardar e sair \n");

    int choice;
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1:
            printf("--------------------------\n");
            insertMenu(toDo);
            break;

        case 2:
            printf("--------------------------\n");
            editTask(toDo, doing, done);
        break;

        case 3:
            printf("--------------------------\n");
            printInfo(toDo, doing, done);
            break;

        case 9:
            printf("--------------------------\n");
            return;

        case 0:
            printf("--------------------------\n");
            saveFile(toDo, doing, done);
            return;

        default:
            printf("Opção inválida, tente novamente.\n"); 
            break;
    }

    return;
}

