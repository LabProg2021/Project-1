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
    List l;
    List prev, subs;  //previous, subsequent
    l = (List) malloc (sizeof(ListNode));
    if(l!=NULL) {
        l -> info = card;
        listSearch(list, card, &prev, &subs);
        l -> next = prev -> next;
        l -> flag = prev -> flag;
        prev -> next = l;
    }
}

void listSearch(List list, Card* card, List *prev, List *subs) {
    *prev = list;
    *subs = list -> next;
    if(list->flag == 1) {             //se for a lista toDo, ordenar por prioridade, se fore igual ordenar por data de criação
        while((*subs) != NULL && (*subs)->info->priority < card->priority) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        // se a prioridade for igual:
        while((*subs) != NULL && (*subs)->info->priority == card->priority && (*subs)->info->creationDate.year > card->creationDate.year) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->priority == card->priority && (*subs)->info->creationDate.month > card->creationDate.month) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->priority == card->priority && (*subs)->info->creationDate.day > card->creationDate.day) {
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
            if((*subs) != NULL && (*subs)->info->person[i] == card->person[i]) i++;
            else break;
        }
    } else if(list->flag == 3) {                          //se for a lista done, ordenar pela data de conclusão
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
    } else{
         while((*subs) != NULL && (*subs)->info->creationDate.year > card->creationDate.year) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->creationDate.month > card->creationDate.month) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->creationDate.day > card->creationDate.day) {
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

void deleteList(List trash) {
    List subs;

    while(trash != NULL) {
        subs = trash->next;
        free(trash);
        trash = subs;
    }
}

void printByPerson(List toDo, List doing, List done, char* person) {
    List find = createList(1);
    ListNode temp = *(toDo);

    while((toDo->next) != NULL) {
        if(strcmp(toDo->next->info->person, person)==0) {
            insertNode(find, toDo->next->info);
        }
        toDo->next = toDo->next->next;
    }
    toDo->next = temp.next;

    temp = *(doing);
    while((doing->next) != NULL) {
        if(strcmp(doing->next->info->person, person)==0) {
            insertNode(find, doing->next->info);
        }
        doing->next = doing->next->next;
    }
    doing->next = temp.next;

    temp = *(done);
    while((done->next) != NULL) {
        if(strcmp(done->next->info->person, person)==0) {
            insertNode(find, done->next->info);
        }
        done->next = done->next->next;
    }
    done->next = temp.next;

    printTeste(find);
    deleteList(find);
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

void printDates(List toDo, List doing, List done) {
    List dates = createList(4);
    ListNode temp = *(toDo);
    while((toDo->next) != NULL) {
        insertNode(dates, toDo->next->info);
        toDo->next = toDo->next->next;
     }
    toDo->next = temp.next;
    temp = *(doing);
    while((doing->next) != NULL) {
        insertNode(dates, doing->next->info);
        doing->next = doing->next->next;
     }
    toDo->next = temp.next;
    temp = *(done);
    while((done->next) != NULL) {
        insertNode(dates, done->next->info);
        done->next = done->next->next;
     }
    done->next = temp.next;    
    printTeste(dates);
    deleteList(dates);
}