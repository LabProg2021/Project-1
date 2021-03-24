#include <stdio.h>
#include <stdlib.h>
#include "data.h"

List createList(void) {
    List aux;
    aux = (List) malloc (sizeof (ListNode)); 
    if (aux != NULL) {
        aux -> info; 
        aux -> next = NULL; 
    }
return aux;
}

void insertOrderTask(List lista, Card card) { //Falta Flag e o metódo search
    List no;
    List prev, atual;
    no = (List) malloc (sizeof(ListNode));
    if(no!=NULL) {
        no -> info = card;
        list_search(lista, card, &prev, &atual);
        no -> next = prev -> next;
        prev -> next = no;
    }
}

void list_search(List lista, Card card, List *prev, List *atual) {
    *prev = lista;
    *atual = lista -> next;
    while((*atual) != NULL && (*atual)->info.id < card.id) {
        *prev = *atual;
        *atual = (*atual)->next;
    }
    if((*atual) != NULL && (*atual)->info.id != card.id) {
        *atual = NULL; //element not found;
    }
}   

void printOrderedBoard(List lista) {
    List print = lista -> next;
    while(print) {
        printf("%d ", print->info.id);
        print = print -> next;
    }
}
