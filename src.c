#include <stdio.h>
#include <stdlib.h>
#include "data.h"

List createList(void) {
    List aux;
    aux = (List) malloc (sizeof (ListNode)); 
    if (aux != NULL) {
        aux -> card;
        aux -> next = NULL; 
    }
return aux;
}

void insertOrderTask(List lista, Card cartao) { //Falta Flag e o metódo search
    List no;
    List prev, next;
    no = (List) malloc (sizeof(ListNode));
    if(no!=NULL) {
        no -> card = &cartao;
        list_search(lista, cartao, &prev, &next);
        no -> next = prev -> next;
        prev -> next = no;
    }
}


