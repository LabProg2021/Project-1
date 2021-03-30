#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "data.h"

int ID = 0;

Card* createCard(char* description, short priority, char* person) {
    Card* newCard = (Card*) malloc(sizeof(Card));

    newCard->id          = ID;
    //newCard->createDate  = createDate;
    newCard->description = description;
    newCard->priority    = priority;
    newCard->person      = person;
    //newCard->deadline    = deadline;
    //newCard->concluDate  = concluDate;

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
    if(list->flag == 1) {
        while((*subs) != NULL && (*subs)->info->id < card->id) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        /*if((*subs) != NULL && (*subs)->info->id != card.id) {
            *subs = NULL; //elemento não encontrado
            printf("teste");
        }*/
    } else if(list->flag == 2) {
        //ordenar por person
    } else {
        //ordenar por conclusion
    }
    
}   

void printTeste(List list) {
    List print = list -> next;
    while(print) {
        printf("%d ", print->info->id);
        print = print -> next;
    }
    printf("\n");
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

void printPerson(List toDo, List doing, List done, char* person) {
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