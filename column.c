#include "column.h"

int countMatches(int* source, int* target) {
    int i, j, counter;

    i = j = 0;
    counter = 0;
    while (i < 6 && j < 6) {
        if (source[i] > target[j]) {
            j++;
        }
        else if (source[i] == target[j]) {
            counter++;
            i++;
            j++;
        }
        else {
            i++;
        }
    }

    return counter;
}

ColumnNode* sortedMerge(ColumnNode* a, ColumnNode* b) {
    ColumnNode* result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->matches >= b->matches) {
        result = a;
        result->next = sortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return (result);
}

void mergeSort(ColumnNode** headRef) {
    ColumnNode* head = *headRef;
    ColumnNode* a;
    ColumnNode* b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    FrontBackSplit(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
}

void FrontBackSplit(ColumnNode* source, ColumnNode** frontRef, ColumnNode** backRef) {
    ColumnNode* fast;
    ColumnNode* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void mergeSortColumnList(ColumnsList* columnsList) {
    ColumnNode* head;
    mergeSort(&(columnsList->head));

    for (head = columnsList->head; head->next != NULL; head = head->next);
    columnsList->tail = head;
}

ColumnsList* enterAutoColumns(int numOfCols) {
    ColumnNode* columnNode;
    ColumnsList* columnList = createColumnList();
    int* numbers;

    printf("Generating columns...");
    for (int i = 0; i < numOfCols; i++) {
        numbers = generateRandomNumbers();
        columnNode = createColumn(numbers);
        insertNodeToEndColumnList(columnList, columnNode);
        free(numbers);
    }
    return columnList;
}

ColumnNode* createColumn(int* numbers) {
    ColumnNode* res;
    res = (ColumnNode*)malloc(sizeof(ColumnNode));
    checkMemoryAllocation(res);
    for (int i = 0; i < 6; i++) {
        res->numbers[i] = numbers[i];
    }
    res->matches = 0;
    res->next = NULL;

    return res;
}

ColumnsList* createColumnList() {
    ColumnsList* columnList;
    columnList = (ColumnsList*)malloc(sizeof(ColumnsList));
    checkMemoryAllocation(columnList);
    columnList->head = NULL;
    columnList->tail = NULL;

    return columnList;
}

ColumnsList* enterManualColumns(int numOfCols) {
    int numbers[6], bucket[16], num, i, j, k, t, counter = 0;
    ColumnNode* columnNode;
    ColumnsList* columnList = createColumnList();

    for (i = 0; i < numOfCols; i++) {
        for (k = 0; k < 16; bucket[k] = 0, k++);
        printf("Please enter 6 numbers:");
        for (j = 0; j < 6; j++) {
            scanf("%d", &num);
            if (validateNumbers(num) == 0) {
                printf("Invalid number\nPlease enter again: ");
                j--;
            }
            else if (bucket[num] == 1) {
                printf("Number is already use\nPlease enter again: ");
                j--;
            }
            else {
                bucket[num] = 1;
            }
        }

        for (t = 0; t < 16; t++) {
            if (bucket[t] == 1) {
                numbers[counter] = t;
                counter++;
            }
        }
        counter = 0;
        columnNode = createColumn(numbers);
        insertNodeToEndColumnList(columnList, columnNode);
    }
    return columnList;
}

int* sumColumnsMatches(PlayersList* playersList) {
    PlayerNode* pPlayer;
    ColumnNode* pCol;
    int* bucket, i;

    bucket = (int*)malloc(sizeof(int) * 7);
    checkMemoryAllocation(bucket);
    for (i = 0; i < 7; i++) {
        bucket[i] = 0;
    }

    pPlayer = playersList->head;
    while (pPlayer != NULL) {
        pCol = pPlayer->columns->head;
        while (pCol != NULL) {
            bucket[pCol->matches]++;
            pCol = pCol->next;
        }
        pPlayer = pPlayer->next;
    }

    return bucket;
}

void insertNodeToEndColumnList(ColumnsList* lst, ColumnNode* newTail) {
    if (isEmptyCoulmnList(lst)) {
        lst->head = lst->tail = newTail;
    }
    else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void printColumn(int* numbers, int size) {
    int i;

    printf("[ ");
    for (i = 0; i < size - 1; i++) {
        printf("%d, ", numbers[i]);
    }
    printf("%d", numbers[i]);
    printf(" ]\n");
}

void printColumnsSummary(int* array) {
    int i;
    printf("--------------------------------------------------\n");
    printf("TOTAL MATCHES SUMMARY\n");
    printf("--------------------------------------------------\n");
    for (i = 6; i >= 0; i--) {
        printf("%d matches - %d\n", i, array[i]);
    }
    printf("--------------------------------------------------\n");
}

int isEmptyCoulmnList(ColumnsList* lst) {
    if (lst->head == NULL) {
        return 1;
    }
    return 0;
}

void freeColumnsList(ColumnsList* columnsList) {
    ColumnNode* pCol;

    for (pCol = columnsList->head; pCol != NULL; pCol = columnsList->head) {
        columnsList->head = columnsList->head->next;
        free(pCol);
    }
    free(columnsList);
}