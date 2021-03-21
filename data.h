#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

typedef struct{
int day;
int month;
int year;
} Date;

typedef struct{
    int id;
    Date creatDate;
    char* title;
    int state;
    int priority;
    Date deadline;
} Card;


#endif // DATA_H_INCLUDED
// New push
