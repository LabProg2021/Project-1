#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int ID = 1;

void incrementID(int* IDPointer) {
    *IDPointer = *IDPointer + 1; 
}

Card* createCard(char* description, short* priority) {
    Card* newCard = (Card*)malloc(sizeof(Card));
    newCard->id          = ID;
    newCard->description = description;
    newCard->creation    = NULL;
    newCard->priority    = priority;
    newCard->responsable = NULL;
    newCard->deadline    = NULL;
    newCard->finish      = NULL;

    incrementID(&ID);

    return newCard;
}

Node* createNode(Card* c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = c;
    newNode->nextNode = NULL;
    return newNode;
}

List* createList(void) {
    List* newList = (List*)malloc(sizeof(List));
    newList->firstNode = NULL;
    return newList;
}

void insertNode(List* l, Card* c) {
    Node* newNode = createNode(c);

    if (l->firstNode == NULL) { l->firstNode = newNode; }

    else {
        Node* currentNode = l->firstNode;

        while (currentNode->nextNode != NULL) {
            currentNode = currentNode->nextNode;
        }

        currentNode->nextNode = newNode;
    }
}

void printList(List* l) {
    Node* currentNode = l->firstNode;

    while (currentNode != NULL) {
        printf("%d ", currentNode->data->id);
        currentNode = currentNode->nextNode;
    }

    printf("\n");
}

void sortList(List* l, int option) {

}