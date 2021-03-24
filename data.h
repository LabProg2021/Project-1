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
} ListNode;



#endif // DATA_H_INCLUDED

// Função para criar lista
List createList(void);//Feito

// Funcão para inserir item ordenado
void insertOrderTask(List lista, Card info);//Feito

//Função para procurar na lista
void list_search(List lista, Card info, List *prev, List *atual);

// Função para mover os cartões de To Do para Doing
void moveDoing();

// Função para alterar a pessoa responsável pela tarefa
void changePerson();

// Função para fechar a tarefa
void closeTask();

// Função para reabrir a tarefa
void reopenTask();

// Função para visualizar o quadro
void printBoard();

// Função para visualizar tarefas por ordem de criação
void printOrderedBoard(List lista);

