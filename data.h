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
    //Geral
    int id;
    Date creatDate;
    char* description;

    //toDo list
    short priority;

    //doing list
    char* person;
    Date deadline;

    //done list
    Date concluDate;
} Card;

typedef struct lnode* List; 

typedef struct lnode {
    Card* info;
    List next;
    short flag;
} ListNode;

#endif // DATA_H_INCLUDED

// Função para criar um cartão
Card* createCard(char* description, short priority, char* person);

// Função para criar uma lista
List createList(short f);

// Funcão para inserir item ordenado
void insertNode(List list, Card* card);

//Função que procura um cartão na lista
void listSearch(List list, Card* card, List *prev, List *atual);

// Função para mover os cartões entre listas
void moveToList(List listO, List listD, int id);

// Função para eliminar elemento de uma lista
void deleteFromList(List list, int id);

// Função para alterar a pessoa responsável pela tarefa
void changePerson();

// Função para visualizar o quadro
void printBoard(List toDo, List doing, List done);

// Função para visualizar tarefas por ordem de criação
void printOrderedBoard(List toDo, List doing, List done);

//Função de teste para imprimir uma lista
void printTeste(List list);

//Função para procurar tarefas por pessoa
void printPerson(List toDo, List doing, List done, char* person);