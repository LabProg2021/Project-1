#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct{
int day;
int month;
int year;
} Date;

typedef struct{
    int id;
    Date creatDate;
    char* title;
    char* person;
    int state;
    int priority;
    Date deadline;
    Date conclusion;
} Card;

typedef struct lnode* List; 

typedef struct lnode {
    Card info; //Para conseguirmos manobrar melhor as listas temos de retirar o * porque senão não conseguimos mudar os elementos
    List next;
    int flag;
} ListNode;



#endif // DATA_H_INCLUDED

// Função que cria uma lista
List createList(int f);

// Função que cria um cartão nulo
Card nullCard(void);

// Funcão para inserir item ordenado
void insertOrderTask(List list, Card card);

//Função que procura um cartão na lista
void listSearch(List list, Card card, List *prev, List *atual);

// Função para mover os cartões entre listas
void moveToList(List listO, List listD, int id);

// Função para eliminar elemento de uma lista
List deleteFromList(List list, int id);

// Função para alterar a pessoa responsável pela tarefa
void changePerson();

/*// Função para fechar a tarefa
void closeTask();*/

/*// Função para reabrir a tarefa
void reopenTask();*/

// Função para visualizar o quadro
void printBoard(List toDo, List doing, List done);

// Função para visualizar tarefas por ordem de criação
void printOrderedBoard(List toDo, List doing, List done);

//Função de teste para imprimir uma lista
void printTeste(List list);
