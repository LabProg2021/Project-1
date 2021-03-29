#include <stdio.h>
#include <stdlib.h>
#include "data.h"

List createList(int f) {
    List aux;
    aux = (List) malloc (sizeof (ListNode)); 
    if (aux != NULL) {
        aux -> info = nullCard(); 
        aux -> next = NULL;
        aux -> flag = f;
    }
    return aux;
}

Card nullCard(void) {
    Card card;
    card.id = -1;
    card.title = "";
    card.person = "";
    card.state = 0;
    card.priority = 0;
    card.creatDate.day = 0;
    return card;
}

void insertOrderTask(List list, Card card) {
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

void listSearch(List list, Card card, List *prev, List *subs) {
    *prev = list;
    *subs = list -> next;
    if(list->flag == 1) {
        while((*subs) != NULL && (*subs)->info.id < card.id) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        /*if((*subs) != NULL && (*subs)->info.id != card.id) {
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
        printf("%d ", print->info.id);
        print = print -> next;
    }
    printf("\n");
}

void moveToList(List listO, List listD, int id) {
    List temp = listO -> next;

    while((temp) != NULL && temp->info.id != id) {
        temp = temp -> next;
    }
    /*if((temp) != NULL && temp->info.id != id) {
        temp = NULL; //elemento não encontrado
    }*/

    insertOrderTask(listD, temp->info);     //Insere elemento na lista de destino
    deleteFromList(listO, id);              //Remove elemento da lista de origem
}

void deleteFromList(List prev, int id) {
    List subs = prev -> next;

    while((subs) != NULL && subs->info.id != id) {
        prev = subs;
        subs = subs -> next;
    }

    if(subs == NULL) return;   //Se o cartão não estiver na lista retorna NULL

    prev -> next = subs -> next;

    free(subs);               //Liberta a memória do elemento eliminado
}