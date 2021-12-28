#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//Defines
#define COLUMN_LEN 6

//Structs
typedef struct columnNode {
    int numbers[COLUMN_LEN];
    int matches;
    struct columnNode *next;
} ColumnNode;

typedef struct columnsList {
    ColumnNode *head;
    ColumnNode *tail;
} ColumnsList;

typedef struct playerNode {
    char *name;
    double avgMatch;
    int columnCounter;
    ColumnsList *columns;
    struct playerNode *next;
} PlayerNode;

typedef struct playersList {
    PlayerNode *head;
    PlayerNode *tail;
} PlayersList;

void printMainMenu();

void printSubMenu();

PlayerNode *createNewPlayerNode(char *name);

void checkMemoryAllocation(void *p);

ColumnsList *enterManualColumns(int numOfCols);

ColumnNode *createColumn(int *numbers);

ColumnsList *createColumnList();

char *getPlayerName();

void printColumn(int *numbers, int size);

void printPlayer(PlayerNode *player);

PlayersList *createPlayerList();

void printPlayersList(PlayersList *playersList);

int *generateRandomNumbers();

ColumnsList *enterAutoColumns(int numOfCols);

int generateRandomNumber();

int countMatches(int *source, int *target);

void calcResults(PlayersList *playersList, int *winningNumbers);

void printWinningNumbers(int *winningNumbers);

void printColumnsSummary(int *array);

int *sumColumnsMatches(PlayersList *playersList);

void printPlayersWithMaxAvgMatch(PlayersList *playersList);

/* Merge Sort debug */
ColumnNode *merge(ColumnNode *right, ColumnNode *left);

void divide(ColumnNode *source,
            ColumnNode **frontRef, ColumnNode **backRef);

void mergeSort(ColumnNode **headRef);

void mergeSortColumnsList(ColumnsList *columnsList);

/* Merge Sort debug */
void writeToFile(char *fName, PlayersList *playersList, int numOfPlayers, int* winningNumbers);
void compressAndWrite(FILE *fp, int *numbers);

int main() {
    int choice, subChoice, numOfPlayers, numOfCols, *winningNumbers, *matchesSummary;
    PlayersList *playersList;
    PlayerNode *player;
    char *playerName;

    playersList = createPlayerList();
    printMainMenu();
    scanf("%d", &choice);//scan user choice from main menu

    while (choice != 3) {
        printf("Enter number of players\n");//scan number of players
        scanf("%d", &numOfPlayers);
        for (int i = 0; i < numOfPlayers; i++) {// for each player
            getchar();
            playerName = getPlayerName();
            player = createNewPlayerNode(playerName);
            printSubMenu();
            scanf("%d", &subChoice);
            printf("Please enter number of columns: ");
            scanf("%d", &numOfCols);
            player->columnCounter = numOfCols;
            switch (subChoice) {
                case 1:
                    player->columns = enterManualColumns(numOfCols);
                    break;
                case 2:
                    player->columns = enterAutoColumns(numOfCols);
                    break;
            }
            if (playersList->head == NULL) {
                playersList->head = player;
                playersList->tail = playersList->head;
            } else {
                playersList->tail->next = player;
                playersList->tail = player;
            }
        }
        winningNumbers = generateRandomNumbers();
        calcResults(playersList, winningNumbers);
        matchesSummary = sumColumnsMatches(playersList);
        printWinningNumbers(winningNumbers);
        printPlayersList(playersList);
        printColumnsSummary(matchesSummary);
        printPlayersWithMaxAvgMatch(playersList);
        printf("ToDo: Press any key\n");
        writeToFile("/Users/talkoren/sandbox/university/lottory/data.bin", playersList, numOfPlayers, winningNumbers);



//        printMainMenu();
//        scanf("%d", &choice);
    }
}

void printMainMenu() {
    int i;
    printf("--------------------------------------------------\n");
    printf("LOTTORY GAME\n");
    printf("--------------------------------------------------\n");
    printf("Please choose one of the following options\n");
    printf("1. Start New game\n");
    printf("2. Print last game results\n");
    printf("3. Exit\n");
    printf(">> ");
}

void printSubMenu() {
    printf("Please choose one of the options:\n");
    printf("1. Manual lotto mode\n");
    printf("2. Auto lotto mode\n");
    printf(">> ");
}

PlayerNode *createNewPlayerNode(char *name) {
    PlayerNode *res;
    res = (PlayerNode *) malloc(sizeof(PlayerNode));
    checkMemoryAllocation(res);

    res->name = name;
    res->avgMatch = 0;
    res->columnCounter = 0;
    res->columns = NULL;
    res->next = NULL;

    return res;
}

void checkMemoryAllocation(void *p) {
    if (p == NULL) {
        printf("Memory Allocation failed\n");
        exit(1);
    }
}

ColumnsList *enterManualColumns(int numOfCols) {
    int numbers[6];
    ColumnNode *columnNode;
    ColumnsList *columnList = createColumnList();

    for (int i = 0; i < numOfCols; i++) {//for each column
        printf("please enter 6 numbers:");
        for (int j = 0; j < 6; j++) {//get 6 numbers
            scanf("%d", &numbers[j]);
            //validate number

        }
        columnNode = createColumn(numbers);
        if (columnList->head == NULL) {
            columnList->head = columnNode;
            columnList->tail = columnList->head;
        } else {
            columnList->tail->next = columnNode;
            columnList->tail = columnNode;
        }
    }
    return columnList;
}

ColumnsList *enterAutoColumns(int numOfCols) {
    ColumnNode *columnNode;
    ColumnsList *columnList = createColumnList();

    for (int i = 0; i < numOfCols; i++) {//for each column
        columnNode = createColumn(generateRandomNumbers());
        if (columnList->head == NULL) {
            columnList->head = columnNode;
            columnList->tail = columnList->head;
        } else {
            columnList->tail->next = columnNode;
            columnList->tail = columnNode;
        }
    }
    return columnList;
}

ColumnNode *createColumn(int *numbers) {
    ColumnNode *res;
    res = (ColumnNode *) malloc(sizeof(ColumnNode));
    checkMemoryAllocation(res);
    for (int i = 0; i < 6; i++) {
        res->numbers[i] = numbers[i];
    }
    res->matches = 0;
    res->next = NULL;

    return res;
}

ColumnsList *createColumnList() {
    ColumnsList *columnList;
    columnList = (ColumnsList *) malloc(sizeof(ColumnsList));
    checkMemoryAllocation(columnList);
    columnList->head = NULL;
    columnList->tail = NULL;

    return columnList;
}

char *getPlayerName() {
    char *name, ch;
    int phySize = 1, logSize = 0;

    name = (char *) malloc(sizeof(char) * phySize);
    checkMemoryAllocation(name);

    printf("Please enter your name: ");
    ch = getchar();

    while (ch != '\n') {
        if (logSize == phySize) {
            phySize *= 2;
            name = (char *) realloc(name, sizeof(char) * phySize);
            checkMemoryAllocation(name);
        }
        name[logSize] = ch;
        logSize++;
        ch = getchar();
    }
    name = (char *) realloc(name, sizeof(char) * (logSize + 1));
    checkMemoryAllocation(name);
    name[logSize] = '\0';

    return name;

}

void printPlayer(PlayerNode *player) {
    int i;
    ColumnNode *temp = player->columns->head;
    printf("--------------------------------------------------\n");
    printf("Name: %s\n", player->name);
    while (temp != NULL) {
        printf("(%d) ", temp->matches);
        printColumn(temp->numbers, 6);
        temp = temp->next;
    }
    printf("Average match: %f\n", player->avgMatch);
}

void printColumn(int *numbers, int size) {
    int i;

    printf("[ ");
    for (i = 0; i < size - 1; i++) {
        printf("%d, ", numbers[i]);
    }
    printf("%d", numbers[i]);
    printf(" ]\n");
}

PlayersList *createPlayerList() {
    PlayersList *res;

    res = (PlayersList *) malloc(sizeof(PlayersList));
    checkMemoryAllocation(res);

    res->head = NULL;
    res->tail = NULL;

    return res;
}

void printPlayersList(PlayersList *playersList) {
    PlayerNode *temp = playersList->head;

    while (temp != NULL) {
        printPlayer(temp);
        temp = temp->next;
    }
}

int generateRandomNumber() {
    int num;

    srand(time(NULL));
    num = 1 + rand() % 16;

    return num;
}

int *generateRandomNumbers() {
    int *numbers, i, j, bucket[16] = {0}, counter, num;

    numbers = (int *) malloc(sizeof(int) * 6);
    checkMemoryAllocation(numbers);

    counter = 0;
    while (counter <= 6) {
        num = generateRandomNumber();
        if (bucket[num] == 0) {
            counter++;
            bucket[num] = 1;
        }
    }
    for (i = 0, j = 0; i < 16; i++) {
        if (bucket[i] == 1) {
            numbers[j++] = i;
        }
    }
    //Array is already sorted using the bucket list
    return numbers;
}

int countMatches(int *source, int *target) {
    int i, j, counter;

    i = j = 0;
    counter = 0;
    while (i < 6 && j < 6) {
        if (source[i] > target[j]) {
            j++;
        } else if (source[i] == target[j]) {
            counter++;
            i++;
            j++;
        } else {
            i++;
        }
    }

    return counter;
}

void calcResults(PlayersList *playersList, int *winningNumbers) {
    PlayerNode *pPlayer;
    ColumnNode *pCol;
    double totalMatches;

    pPlayer = playersList->head;
    while (pPlayer != NULL) {
        pCol = pPlayer->columns->head;
        totalMatches = 0;
        while (pCol != NULL) {
            pCol->matches = countMatches(winningNumbers, pCol->numbers);
            totalMatches += pCol->matches;
            pCol = pCol->next;
        }
        pPlayer->avgMatch = totalMatches / pPlayer->columnCounter;
//        mergeSortColumnsList(pPlayer->columns);
        pPlayer = pPlayer->next;
    }
}

void printWinningNumbers(int *winningNumbers) {
    printf("--------------------------------\n");
    printf("WINNING NUMBERS:\n");
    printf("--------------------------------\n");
    printColumn(winningNumbers, 6);
    printf("--------------------------------\n");
}

ColumnNode *merge(ColumnNode *right, ColumnNode *left) {
    ColumnNode *result = NULL;

    /* Base cases */
    if (left == NULL)
        return (right);
    else if (right == NULL)
        return (left);

    /* Pick either a or b, and recur */
    if (left->matches >= right->matches) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return (result);
}

void divide(ColumnNode *source,
            ColumnNode **frontRef, ColumnNode **backRef) {
    ColumnNode *fast;
    ColumnNode *slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
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

void mergeSort(ColumnNode **headRef) {
    ColumnNode *head = *headRef;
    ColumnNode *left;
    ColumnNode *right;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }


    divide(head, &left, &right);

    mergeSort(&left);
    mergeSort(&right);

    /* answer = merge the two sorted lists together */
    *headRef = merge(left, right);
}

void mergeSortColumnsList(ColumnsList *columnsList) {
    ColumnNode *head = columnsList->head;
    mergeSort(&head);
    for (; head->next != NULL; head = head->next);
    columnsList->tail = head;
}

int *sumColumnsMatches(PlayersList *playersList) {
    PlayerNode *pPlayer;
    ColumnNode *pCol;
    int *bucket, i;

    bucket = (int *) malloc(sizeof(int) * 7);
    checkMemoryAllocation(bucket);
    for (i = 0; i < 7; i++, bucket[i] = 0);

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

void printColumnsSummary(int *array) {
    int i;
    printf("----------------------------\n");
    printf("TOTAL MATCHES SUMMARY\n");
    printf("----------------------------\n");
    for (i = 6; i >= 0; i--) {
        printf("%d matches - %d\n", i, array[i]);
    }
    printf("----------------------------\n");
}

void printPlayersWithMaxAvgMatch(PlayersList *playersList) {
    double max;
    PlayerNode *pPlayer;


    for (pPlayer = playersList->head, max = 0; pPlayer != NULL; pPlayer = pPlayer->next) {
        if (pPlayer->avgMatch > max) {
            max = pPlayer->avgMatch;
        }
    }
    printf("----------------------------\n");
    printf("The players with the highest average:\n");
    for (pPlayer = playersList->head; pPlayer != NULL; pPlayer = pPlayer->next) {
        if (pPlayer->avgMatch == max) {
            printf("%s\n", pPlayer->name);
        }
    }
    printf("----------------------------\n");
}

void writeToFile(char *fName, PlayersList *playersList, int numOfPlayers, int* winningNumbers) {
    PlayerNode *pPlayer;
    ColumnNode *pCol;
    int nameLen;
    FILE *fp = fopen(fName, "wb");
    //ToDo: Add validation for open file

    fwrite(&numOfPlayers, sizeof(int), 1, fp);
    for (pPlayer = playersList->head; pPlayer != NULL; pPlayer = pPlayer->next) {
        nameLen = strlen(pPlayer->name);
        fwrite(&nameLen, sizeof(int), 1, fp);
        fwrite(pPlayer->name, sizeof(char), nameLen, fp);
        fwrite(&pPlayer->columnCounter, sizeof(int), 1, fp);


        for (pCol = pPlayer->columns->head; pCol != NULL; pCol = pCol->next) {
            compressAndWrite(fp, pCol->numbers);
        }

    }
    compressAndWrite(fp, winningNumbers);
    fclose(fp);
}

void compressAndWrite(FILE *fp, int *numbers) {
    unsigned char compress[3] = {0};
    int i, j;

    for(i = 0, j = 0; i < 3; i++, j+=2) {
        compress[i] = compress[i] | (char)numbers[j];
        compress[i] << 4;
        compress[i] = compress[i] | (char)numbers[j+1];
    }

    fwrite(compress, sizeof(char), 3, fp);
}


void readFromFile(){

}

/*To do:
 1. read from file
 2. merge sort
 3. free data
 4. validation
 5. clean code
 6. split to files
 */


