#pragma once
#include "utils.h"
#include "random.h"

//This function counts the number of matches between source and target
int countMatches(int* source, int* target);
//This function connects the nodes of the link list (used in mergeSort)
ColumnNode* sortedMerge(ColumnNode* a, ColumnNode* b);
//This function is a merge sort for a column list
void mergeSort(ColumnNode** headRef);
//This function finds the middle of a linked list and returns the nodes of left and right parts
void FrontBackSplit(ColumnNode* source, ColumnNode** frontRef, ColumnNode** backRef);
//This function sorts a given column list
void mergeSortColumnList(ColumnsList* columnsList);
//This function generates auto columns and returns it
ColumnsList* enterAutoColumns(int numOfCols);
//This function creates a column
ColumnNode* createColumn(int* numbers);
//This function creates a column list
ColumnsList* createColumnList();
//This function creates manual columns and returns it
ColumnsList* enterManualColumns(int numOfCols);
//This function sums the matches for a player
int* sumColumnsMatches(PlayersList* playersList);
//This function validates numbers of columns
int validateNumOfColumns();
//This function inserts a newTail to the end of lst
void insertNodeToEndColumnList(ColumnsList* lst, ColumnNode* newTail);
//This function checks if a given column list is empty
int isEmptyCoulmnList(ColumnsList* lst);
//This function prints a column
void printColumn(int* numbers, int size);
//This function prints a matches summary
void printColumnsSummary(int* array);
//This function frees a given column list
void freeColumnsList(ColumnsList* columnsList);