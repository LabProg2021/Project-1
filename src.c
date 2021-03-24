#include <stdio.h>
#include <stdlib.h>
#include "data.h"

List createList(void) {
    List aux;
    aux = (List) malloc (sizeof (List_node)); 
    if (aux != NULL) {
        aux -> card ;
        aux -> next = NULL; 
    }
return aux;
}