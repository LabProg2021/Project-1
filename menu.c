#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data.h"
#include "src.c"

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#define MAX_DESC 30
#define MAX_TASK 20

void insertMenu(List toDo) {
    char* description = (char*) calloc (MAX_DESC, sizeof (char));

    printf("\n Indique um nome para a tarefa: \n");
    printf(" > ");
    scanf("%[^\n]%*c", description);

    while(strcmp(description, "") == 0) {
        printf(" Não introduziu um nome válido. Por favor tente novamente:\n");
        printf(" > ");
        getchar();
        scanf("%[^\n]%*c", description);
    }

    short priority;

    printf(" Introduza a prioridade do cartão, de 1 a 10: \n");
    printf(" > ");
    int control = scanf("%hi", &priority);

    //controlo de input
    while(control!=1) {
        printf(" Prioridade invalida, por favor introduza um numero entre 1 e 10: \n");
        printf(" > ");
        getchar();
        control = scanf("%hi", &priority);
    }
    while(priority < 1 || priority > 10) {
        printf(" Prioridade invalida, por favor introduza um numero entre 1 e 10: \n");
        printf(" > ");
        scanf("%hi", &priority);
    }

    if(listSize(toDo) < MAX_TASK) {
        stringToUpper(description);
        insertNode(toDo, createCard(description, priority));
    } else {
        printf(" Limite máximo de tarefas atingido. \n\n");
        return;
    }

    printf("\n Tarefa adicionada com sucesso.\n");
    sleep(1.5);
    clrscr();
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
        //stringToUpper(newPerson);
        //CONTINUAR AQUI
        changePerson(listO, list->info, newPerson);

        printf("Atribua uma data limite de conclusão (dd mm aaaa): ");
        int control = scanf("%hd %hd %hd", &(list->info->deadline.day), &(list->info->deadline.month), &(list->info->deadline.year));
        
        //controlo de input
        while(control!=3) {
            printf("Indique uma data válida (dd mm aaaa): ");
            getchar();
            control = scanf("%hd %hd %hd", &(list->info->deadline.day), &(list->info->deadline.month), &(list->info->deadline.year));
        }
        while(compareDate(list->info->deadline, curDate) == (-1)) {
            printf("Indique uma data válida (dd mm aaaa): ");
            scanf("%hd %hd %hd", &(list->info->deadline.day), &(list->info->deadline.month), &(list->info->deadline.year));
        }

    } else if(listO->flag == 2) {
        if(listD->flag == 1) {
            list->info->deadline = createDate(0, 0, 0);
        } else {
            list->info->concluDate = curDate;
        }
    } else {
        Date nullDate = createDate(0, 0, 0);
        list->info->concluDate = nullDate;
        list->info->deadline = nullDate;
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
    clrscr();
    printf("--------------------------------\n");
    printf("\033[0;32m");
    printf("                   EDITAR TAREFA\n");
    printf("\033[0m");
    printf(" 1. Iniciar uma tarefa \n");
    printf(" 2. Colocar uma tarefa em pausa \n");
    printf(" 3. Alterar responsável duma \n    tarefa \n");
    printf(" 4. Concluir tarefa \n");
    printf(" 5. Reabrir tarefa \n");
    printf(" 0. Voltar ao menu inicial \n");
    printf("--------------------------------\n");
    printf(" > ");

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            moveMenu(toDo, doing);
            break;
        
        case 2:
            moveMenu(doing, toDo);
            break;

        case 3:
            changePersonMenu(doing);
            break;

        case 4:
            moveMenu(doing, done);
            break;
        
        case 5:
            moveMenu(done, toDo);
            break;
        
        case 0:
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
    clrscr();
    printf("--------------------------------\n");
    printf("\033[0;32m");
    printf("              VIZUALIZAR TAREFAS\n");
    printf("\033[0m");
    printf(" 1. Visualizar quadro \n");
    printf(" 2. Visualizar tarefas de uma \n    pessoa. \n");
    printf(" 3. Visualizar tarefas por \n    data de criação \n");
    printf(" 0. Voltar ao menu inicial \n");
    printf("--------------------------------\n");
    printf(" > ");

    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("                    Tarefas por fazer: \n");
            printList(toDo);

            printf("                    Tarefas a serem feitas (%d/%d): \n", listSize(doing), MAX_TASK / 2);
            printList(doing);
            printf("                    Tarefas concluídas: \n");
            printList(done);
            printf(" 0. Voltar ao menu inicial \n");
            printf(" > ");
            scanf("%d", &choice);
            break;

        case 2:
            printPerson(toDo, doing, done);
            break;

        case 3:
            printByDate(toDo, doing, done);
            break;

        case 0:
            break;
        
        default:
            printf("Opção inválida, tente novamente.\n"); 
            break;
    }
}

void homepage (List toDo, List doing, List done) {
    clrscr();
    printf("--------------------------------\n");
    printf("\033[0;32m");
    printf("                  MENU PRINCIPAL\n");
    printf("\033[0m");
    printf(" 1. Adicionar nova tarefa \n");
    printf(" 2. Editar tarefas \n");
    printf(" 3. Visualizar tarefas \n");
    printf(" 9. Sair \n");
    printf(" 0. Guardar e sair \n");
    printf("--------------------------------\n");
    printf(" > ");

    int choice;
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1:
            insertMenu(toDo);
            homepage(toDo, doing, done);
            break;

        case 2:
            editTask(toDo, doing, done);
            homepage(toDo, doing, done);
        break;

        case 3:
            printInfo(toDo, doing, done);
            homepage(toDo, doing, done);
            break;

        case 9:
            return;

        case 0:
            saveFile(toDo, doing, done);
            return;

        default:
            printf("Opção inválida, tente novamente.\n"); 
            break;
    }

    return;
}

