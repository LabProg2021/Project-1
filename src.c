#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "data.h"

#define MAX_DESC 30

int ID = 0;

Date createDate(short year, short month, short day) {
    Date newDate;

    newDate.year  = year;
    newDate.month = month;
    newDate.day   = day;

    return newDate;
}

Card* createCard(char* description, short priority) {
    Card* newCard = (Card*)malloc(sizeof(Card));

    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    Date curDate = createDate(time.tm_year + 1900, time.tm_mon + 1, time.tm_mday); //Cria data autal
    Date nullDate = createDate(0, 0, 0);
    char* nullName = "NULL";

    newCard->id           = ID;
    newCard->creationDate = curDate;
    newCard->description  = description;
    newCard->priority     = priority;
    newCard->person       = nullName;
    newCard->deadline     = nullDate;
    newCard->concluDate   = nullDate;

    ID++;
    return newCard;
}

List createList(short f) {
    Card card;
    List aux;
    aux = (List) malloc (sizeof (ListNode)); 
    if (aux != NULL) {
        aux -> info = &card; 
        aux -> next = NULL;
        aux -> flag = f;
    }
    return aux;
}

void insertNode(List list, Card* card) {
    List l;
    List prev, subs;  //previous, subsequent
    l = (List) malloc (sizeof(ListNode));
    if(l!=NULL) {
        l -> info = card;
        listSearch(list, card, &prev, &subs);
        l -> next = prev -> next;
        l -> flag = prev -> flag;
        prev -> next = l;
    }
}

void listSearch(List list, Card* card, List *prev, List *subs) {
    *prev = list;
    *subs = list -> next;
    if(list->flag == 1) {             //se for a lista toDo, ordenar por prioridade, se fore igual ordenar por data de criação
        while((*subs) != NULL && (*subs)->info->priority > card->priority) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        // se a prioridade for igual:
        while((*subs) != NULL && (*subs)->info->priority == card->priority && (*subs)->info->creationDate.year > card->creationDate.year) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->priority == card->priority && (*subs)->info->creationDate.month > card->creationDate.month) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->priority == card->priority && (*subs)->info->creationDate.day > card->creationDate.day) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
    } else if(list->flag == 2) {    //se for a lista doing, ordenar pela pessoa responsável
        int i = 0;
        while((*subs) != NULL && (*subs)->info->person[i] != '\0') {
            while((*subs) != NULL && (*subs)->info->person[i] < card->person[i]) {
                *prev = *subs;
                *subs = (*subs)->next;
            }
            if((*subs) != NULL && (*subs)->info->person[i] == card->person[i]) i++;
            else break;
        }
    } else if(list->flag == 3) {    //se for a lista done, ordenar pela data de conclusão
        while((*subs) != NULL && (*subs)->info->concluDate.year > card->concluDate.year) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->concluDate.month > card->concluDate.month) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->concluDate.day > card->concluDate.day) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
    } else {                        //se dor a lista byPerson, ordenar pela data de criação
        while((*subs) != NULL && (*subs)->info->creationDate.year > card->creationDate.year) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->creationDate.month > card->creationDate.month) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
        while((*subs) != NULL && (*subs)->info->creationDate.day > card->creationDate.day) {
            *prev = *subs;
            *subs = (*subs)->next;
        }
    } 
}

void moveToList(List listO, List listD, Card* card) {
    List temp = listO -> next;

    while((temp) != NULL && temp->info->id != card->id) {
        temp = temp -> next;
    }

    insertNode(listD, temp->info);  //Insere elemento na lista de destino
    deleteFromList(listO, card);    //Remove elemento da lista de origem
}

void changePerson(List list, Card* card, char* newPerson) {
    deleteFromList(list, card);
    card->person = newPerson;
    insertNode(list, card);
}

void deleteFromList(List prev, Card* card) {
    List subs = prev -> next;

    while((subs) != NULL && subs->info->id != card->id) {
        prev = subs;
        subs = subs -> next;
    }

    if(subs == NULL) return;   //Se o cartão não estiver na lista retorna NULL

    prev -> next = subs -> next;

    free(subs);                //Liberta a memória do nó eliminado
}

void deleteList(List trash) {
    List subs;

    while(trash != NULL) {
        subs = trash->next;
        free(trash);
        trash = subs;
    }
}

void printByPerson(List list, char* person) {
    List byPerson = createList(1);
    ListNode temp = *(list);

    while((list->next) != NULL) {
        if(strcmp(list->next->info->person, person) == 0) {
            insertNode(byPerson, list->next->info);
        }
        list->next = list->next->next;
    }

    list->next = temp.next;

    printTeste(byPerson);
    deleteList(byPerson);
}

void printByDate(List toDo, List doing, List done) {
    List dates = createList(4);
    ListNode temp = *(toDo);
    while((toDo->next) != NULL) {
        insertNode(dates, toDo->next->info);
        toDo->next = toDo->next->next;
     }
    toDo->next = temp.next;
    temp = *(doing);
    while((doing->next) != NULL) {
        insertNode(dates, doing->next->info);
        doing->next = doing->next->next;
     }
    doing->next = temp.next;
    temp = *(done);
    while((done->next) != NULL) {
        insertNode(dates, done->next->info);
        done->next = done->next->next;
     }
    done->next = temp.next;    
    printTeste(dates);
    deleteList(dates);
}

void printTeste(List list) {
    List printCard = list -> next;
    while(printCard) {
        printf("--------------------------------------- \n");
        printf("ID: %d \n", printCard->info->id);
        printf("Data de criação: %hu/%hu/%hu \n", printCard->info->creationDate.day, printCard->info->creationDate.month, printCard->info->creationDate.year);
        printf("Descrição: %s \n", printCard->info->description);
        printf("Prioridade: %hu \n", printCard->info->priority);
        printf("Responsável: %s \n", printCard->info->person);
        printf("Data Limite: %hu/%hu/%hu \n", printCard->info->deadline.day, printCard->info->deadline.month, printCard->info->deadline.year);
        printf("Data de conclusão: %hu/%hu/%hu \n", printCard->info->concluDate.day, printCard->info->concluDate.month, printCard->info->concluDate.year);
        printCard = printCard -> next;
    }
    printf("\n");
    printf("\n");
}

void printTask(List task) {
    if(task->flag == 1) {
        printf("%s ", task->info->description);
        printf("(%hd) ", task->info->priority);
        printf("   id_%d\n", task->info->id);
    } else if(task->flag == 2) {
        printf("%s ", task->info->description);
        printf("'%s' ", task->info->person);
        printf("   id_%d\n", task->info->id);
    } else {
        printf("%s ", task->info->description);
        printf("(%hd_%hd_%hd) ", task->info->concluDate.day, task->info->concluDate.month, task->info->concluDate.year);
        printf("   id_%d\n", task->info->id);
    }
}

void saveFile(List toDo, List doing, List done) {
    FILE *fp;
    remove("cartoes.txt");
    fp = fopen("cartoes.txt", "w+");
    if(fp==NULL) {printf("Ficheiro não encontrado\n");
    }
    else {
        ListNode temp = *(toDo);
        while(toDo->next != NULL) {
            fprintf(fp, "%s\n", toDo->next->info->description);
            fprintf(fp, "%s\n", toDo->next->info->person);
            fprintf(fp, "%d\n", toDo->next->info->id);
            fprintf(fp, "%d %d %d\n", toDo->next->info->creationDate.day,toDo->next->info->creationDate.month, toDo->next->info->creationDate.year);
            fprintf(fp, "%d\n", toDo->next->info->priority);
            fprintf(fp, "%d %d %d\n", toDo->next->info->deadline.day,toDo->next->info->deadline.month, toDo->next->info->deadline.year);
            fprintf(fp, "%d %d %d\n", toDo->next->info->concluDate.day,toDo->next->info->concluDate.month, toDo->next->info->concluDate.year);
            fprintf(fp, "%d\n", toDo->flag);
            //fprintf(fp, "\n");
            toDo->next = toDo->next->next;
        }
        toDo->next = temp.next;
        temp = *(doing);
        while(doing->next != NULL) {
            fprintf(fp, "%s\n", doing->next->info->description);
            fprintf(fp, "%s\n", doing->next->info->person);
            fprintf(fp, "%d\n", doing->next->info->id);
            fprintf(fp, "%d %d %d\n", doing->next->info->creationDate.day,doing->next->info->creationDate.month, doing->next->info->creationDate.year);
            fprintf(fp, "%d\n", doing->next->info->priority);
            fprintf(fp, "%d %d %d\n", doing->next->info->deadline.day, doing->next->info->deadline.month, doing->next->info->deadline.year);
            fprintf(fp, "%d %d %d\n", doing->next->info->concluDate.day,doing->next->info->concluDate.month, doing->next->info->concluDate.year);
            fprintf(fp, "%d\n", doing->flag);
            //fprintf(fp, "\n");
            doing->next = doing->next->next;
        }
        doing->next = temp.next;
        temp = *(done);
        while(done->next != NULL) {
            fprintf(fp, "%s\n", done->next->info->description);
            fprintf(fp, "%s\n", done->next->info->person);
            fprintf(fp, "%d\n", done->next->info->id);
            fprintf(fp, "%d %d %d\n", done->next->info->creationDate.day, done->next->info->creationDate.month, done->next->info->creationDate.year);
            fprintf(fp, "%d\n", done->next->info->priority);
            fprintf(fp, "%d %d %d\n", done->next->info->deadline.day, done->next->info->deadline.month, done->next->info->deadline.year);
            fprintf(fp, "%d %d %d\n", done->next->info->concluDate.day,done->next->info->concluDate.month, done->next->info->concluDate.year);
            fprintf(fp, "%d\n", doing->flag);
            //fprintf(fp, "\n");
            done->next = done->next->next;
        }
        done->next = temp.next;
    }
    fclose(fp);
}

void readFile(List toDo, List doing, List done) {
    FILE *fp = fopen("cartoes.txt", "r+"); //Criação do cartão para adicionar a lista
    while(!feof(fp)) {
        int flag = 0;
        Card *temp = createCard(NULL, 0);
        ID--;
        char *description = (char *)malloc(sizeof(char) * MAX_DESC); //Váriavel para guardar a descrição lida
        char *person = (char *)malloc(sizeof(char) * MAX_DESC);      // Váriavel para guardar a pessoa lida
        fscanf(fp, "%[^\n]", description);
        fgetc(fp); //Retirar o \n para permitir o próximo scan;
        fscanf(fp, "%[^\n]", person);
        fscanf(fp, "%d", &temp->id);
        //printf("A: %d\n", ID);
        //printf("tmp: %d\n", temp->id);
        //printf("%s\n", description);
        //printf("%s\n", person);
        if(temp->id >= ID) ID = (temp->id) + 1; //atualiza o ID
        //printf("D: %d\n", ID);
        fscanf(fp, "%hd %hd %hd", &temp->creationDate.day, &temp->creationDate.month, &temp->creationDate.year);
        fscanf(fp, "%hd", &temp->priority);
        fscanf(fp, "%hd %hd %hd", &temp->deadline.day, &temp->deadline.month, &temp->deadline.year);
        fscanf(fp, "%hd %hd %hd", &temp->concluDate.day, &temp->concluDate.month, &temp->concluDate.year);
        fscanf(fp, "%d", &flag);
        fgetc(fp); //Retirar o /n a seguir ao último parametro de cada cartão para permitir a leitura do próximo
        temp->description = description;
        temp->person = person;
        if(flag == 1) {
            insertNode(toDo, temp);
        }
        else if(flag == 2) {
            insertNode(doing, temp);
        }
        else if(flag == 3) {
            insertNode(done, temp);
        }
    }
    ID--;
    fseek(fp, 0, SEEK_SET);
    fclose(fp);
    /*printf("To Do :\n");
    printTeste(toDo);
    printf("Doing :\n");
    printTeste(doing);
    printf("Done :\n");
    printTeste(done);*/
}

/*
void printMenuIndex(List list) {
    List printCard = list->next;

    int i = 1;

    while(printCard) {
        printf("%d. ", i);
        printf("ID da tarefa: %d \n", printCard->info->id);
        printf("Data de criação: %hu/%hu/%hu \n", printCard->info->creationDate.day, printCard->info->creationDate.month, printCard->info->creationDate.year);
        printf("Descrição: %s \n", printCard->info->description);
        printf("Prioridade: %hu \n", printCard->info->priority);
        printf("\n");
        i++;
        printCard = printCard -> next;
    }
}
*/