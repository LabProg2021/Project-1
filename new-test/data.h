#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    short day;
    short month;
    short year;
} Date;

typedef struct {
    // General: 
    int id;
    char* description;
    Date* creation;

    // toDoList Only
    short* priority;
    
    // doingList Only
    char* responsable;
    Date* deadline;
    
    //doneList Only
    Date* finish;
} Card;

typedef struct node Node;

typedef struct node {
    Card* data;
    Node* nextNode;
} Node;

typedef struct {
    Node* firstNode;
} List;


#endif // DATA_H_INCLUDED

List* createList(void);

void insertNode(List* l, Card* c);

void printList(List* l);