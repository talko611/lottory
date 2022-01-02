#include "utils.h"
#include "validation.h"
#include "random.h"

//This function counts the number of matches between source and target
int countMatches(int* source, int* target);
//Use inside merge sort connect the nodes of the link list
ColumnNode* sortedMerge(ColumnNode* a, ColumnNode* b);
//Merge sort to column list
void mergeSort(ColumnNode** headRef);
//Find the middle of link list and returns the nodes of left and right part
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
//This function prints a column
void printColumn(int* numbers, int size);
//This function prints a matches summary
void printColumnsSummary(int* array);
//This function checks if a given column list is empty
int isEmptyCoulmnList(ColumnsList* lst);
//This function frees a given column list
void freeColumnsList(ColumnsList* columnsList);