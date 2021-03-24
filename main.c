#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "src.c"

int main(int argc, char const *argv[])
{
    List toDo = createList();
    List Doing = createList();
    List Done = createList();

    Card cartao;
    cartao.id = 1;
    cartao.title = "Olá Mundo";
    cartao.person = "Eu";
    cartao.state = 1;
    cartao.priority = 1;
    cartao.creatDate.day = 30;

    insertOrderTask(toDo, cartao);
    
    printf("%d", cartao.id);
    return 0;
}
