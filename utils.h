# pragma once
#define _CRT_SECURE_NO_WARNINGS
#define COLUMN_LEN 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct columnNode {
    int numbers[COLUMN_LEN]; //A column
    int matches;             //Matches count
    struct columnNode* next;
} ColumnNode;

typedef struct columnsList {
    ColumnNode* head;
    ColumnNode* tail;
} ColumnsList;

typedef struct playerNode {
    char* name;              //Player name
    double avgMatch;         //Matches avarage
    int columnCounter;       //Number of columns
    ColumnsList* columns;    //Columns list
    struct playerNode* next;
} PlayerNode;

typedef struct playersList {
    PlayerNode* head;
    PlayerNode* tail;
} PlayersList;