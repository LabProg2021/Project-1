#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char* title;
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