#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "data.h"

int ID = 0;

Date createDate(short year, short month, short day) {
    Date newDate;

    newDate.year  = year;
    newDate.month = month;
    newDate.day   = day;

    return newDate;
}

Card createCard(char* description, short priority, char* person, Date* deadline, Date* concluDate) {
    Card newCard;

    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    Date curDate = createDate(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday); //Cria data autal

    newCard.id           = ID;
    newCard.creationDate = curDate;
    newCard.description  = description;
    newCard.priority     = priority;
    newCard.person       = person;
    newCard.deadline     = *deadline;
    newCard.concluDate   = *concluDate;

    ID++;
    return newCard;
}

List createList(short f) {
    Card card;
    List aux;
    aux = (List) malloc (sizeof (ListNode)); 
    if (aux != NULL) {
        aux -> info = &card; 
        aux -> next = NULL;
        aux -> flag = f;
    }
    return aux;
}

void insertNode(List list, Card* card) {
    List no;
    List prev, subs;
    no = (List) malloc (sizeof(ListNode));
    if(no!=NULL) {
        no -> info = card;
        listSearch(list, card, &prev, &subs);
        no -> next = prev -> next;
        no -> flag = prev -> flag;
        prev -> next = no;
    }
}

void listSearch(List list, Card* card, List *prev, List *subs) {
    *prev = list;
    *subs = list -> next;
    if(list->flag == 1) {             //se for a lista toDo, ordenar por prioridade
        while((*subs) != NULL && (*subs)->info->priority < card->priority) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
    } else if(list->flag == 2) {      //se for a lista doing, ordenar pela pessoa responsável
        int i = 0;
        while((*subs) != NULL && (*subs)->info->person[i] != '\0') {
            while((*subs) != NULL && (*subs)->info->person[i] < card->person[i]) {
                *prev = *subs;
                *subs = (*subs)->next;
            }
            if((*prev)->info->person[i] == card->person[i]) i++;
            else break;
        }
    } else {                          //se for a lista done, ordenar pela data de conclusão
        while((*subs) != NULL && (*subs)->info->concluDate.year > card->concluDate.year) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->concluDate.month > card->concluDate.month) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->concluDate.day > card->concluDate.day) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
    }
    
}

void moveToList(List listO, List listD, int id) {
    List temp = listO -> next;

    while((temp) != NULL && temp->info->id != id) {
        temp = temp -> next;
    }
    /*if((temp) != NULL && temp->info.id != id) {
        temp = NULL; //elemento não encontrado
    }*/

    insertNode(listD, temp->info); //Insere elemento na lista de destino
    deleteFromList(listO, id);     //Remove elemento da lista de origem
}

void deleteFromList(List prev, int id) {
    List subs = prev -> next;

    while((subs) != NULL && subs->info->id != id) {
        prev = subs;
        subs = subs -> next;
    }

    if(subs == NULL) return;   //Se o cartão não estiver na lista retorna NULL

    prev -> next = subs -> next;

    free(subs);               //Liberta a memória do elemento eliminado
}

void printByPerson(List toDo, List doing, List done, char* person) {
    List find = createList(1);

    while((toDo->next) != NULL) {
        if(strcmp(toDo->next->info->person, person)==0) {
            insertNode(find, toDo->next->info);
        }
        toDo->next = toDo->next->next;
    }

    while((doing->next) != NULL) {
        if(strcmp(doing->next->info->person, person)==0) {
            insertNode(find, doing->next->info);
        }
        doing->next = doing->next->next;
    }

    while((done->next) != NULL) {
        if(strcmp(done->next->info->person, person)==0) {
            insertNode(find, done->next->info);
        }
        done->next = done->next->next;
    }
    printTeste(find);
}

void printTeste(List list) {
    List printID = list -> next;
    printf("ID: ");
    while(printID) {
        printf("%d ", printID->info->id);
        printID = printID -> next;
    }
    printf("\n");
    printf("\n");
}