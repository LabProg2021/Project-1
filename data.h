#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    short day;
    short month;
    short year;
} Date;

typedef struct{
    //Geral
    int id;
    Date creationDate;
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

//Função para criar uma data
Date createDate(short year, short month, short day);

// Função para criar um cartão
Card* createCard(char* description, short priority);

// Função para criar uma lista
List createList(short f);

// Função para eliminar uma lista
void deleteList(List trash);

//Função que compara datas, retorna -1 se x<y, 0 se forem iguais e 1 se x>y
int compareDate(Date x, Date y);

// Funcão para inserir item ordenado
void insertNode(List list, Card* card);

//Função que procura um cartão na lista
void listSearch(List list, Card* card, List* prev, List* atual);

// Função para mover os cartões entre listas
void moveToList(List listO, List listD, Card* card);

// Função para alterar a pessoa responsável pela tarefa
void changePerson(List list, Card* card, char* newPerson);

// Função para eliminar elemento de uma lista
void deleteFromList(List list, Card* Card);

//Função para visualizar tarefas de uma pessoa
void printByPerson(List list, char* person);

//Função para visualizar todas as tarefas por ordem de criação
void printByDate(List toDo, List doing, List done);

//Função para imprimir uma lista
void printList(List list);

// Função que retorna o tamanho de uma lista
int listSize(List list);

//Função para guardar alterações no ficheiro 
void saveFile(List toDo, List doing, List done);

//Função para ler dados do ficheiro
void readFile(List toDo, List doing, List done);

//Função para imprimir uma tarefa
void printTask(List task);

//Função que retorna uma string com todas as letras maiusculas
void stringToUpper(char* s);

//Funções para gerir o menu
void insertMenu(List toDo);
void editTask(List toDo, List doing, List done);
void printInfo(List toDo, List doing, List done);
void homepage (List toDo, List doing, List done);
