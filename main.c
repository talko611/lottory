#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

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


int *generateRandomNumbers();

int generateRandomNumber();

int countMatches(int *source, int *target);

void printMainMenu();

void printSubMenu();

void printColumn(int *numbers, int size);

void printPlayer(PlayerNode *player);

void printPlayersList(PlayersList *playersList);

void printWinningNumbers(int *winningNumbers);

void printColumnsSummary(int *array);

void printPlayersWithMaxAvgMatch(PlayersList *playersList);

int validateMainMenuInput();

void checkMemoryAllocation(void *p);

void checkFileAllocation(void *p);

PlayerNode *createNewPlayerNode(char *name);

ColumnsList *enterManualColumns(int numOfCols);

ColumnNode *createColumn(int *numbers);

ColumnsList *createColumnList();

char *getPlayerName();

PlayersList *createPlayerList();

ColumnsList *enterAutoColumns(int numOfCols);

void calcResults(PlayersList *playersList, int *winningNumbers);

int *sumColumnsMatches(PlayersList *playersList);

ColumnNode *SortedMerge(ColumnNode *a, ColumnNode *b);

void FrontBackSplit(ColumnNode *source,
                    ColumnNode **frontRef, ColumnNode **backRef);

void MergeSort(ColumnNode **headRef);

void mergeSortColumnList(ColumnsList *columnsList);


void writeToFile(char *fName, PlayersList *playersList, int numOfPlayers, int *winningNumbers);

void compressAndWrite(FILE *fp, int *numbers);

int *convertCompressedData(unsigned char *compress);// insert to main

PlayersList *readLastGameResultsFromFile(FILE *fp, int **winningNumbers);

void freeColumnsList(ColumnsList *columnsList);

void freePlayersList(PlayersList *playersList);

void option1(int *saveToFile);

void option2(int saveToFile);

int validateSubMenuInput();

int validateNumOfColumns();

int validateNumbers(int number);

int validateNumOfPlayers();

int askToContinue();

int main() {
    int choice, saveToFile = 0;

    choice = validateMainMenuInput();
    while (choice != 3) {

        switch (choice) {
            case 1:
                option1(&saveToFile);

                break;
            case 2:
                option2(saveToFile);
                break;
            default:
                break;
        }

        choice = validateMainMenuInput();
    }
}

void option1(int *saveToFile) {
    int subChoice, numOfPlayers, numOfCols, *winningNumbers, *matchesSummary;
    PlayersList *playersList;
    PlayerNode *player;
    char *playerName;

    playersList = createPlayerList();
    numOfPlayers = validateNumOfPlayers();
    for (int i = 0; i < numOfPlayers; i++) {// for each player
        getchar();
        playerName = getPlayerName();
        player = createNewPlayerNode(playerName);
        subChoice = validateSubMenuInput();
        player->columnCounter = validateNumOfColumns();;
        switch (subChoice) {
            case 1:
                player->columns = enterManualColumns(player->columnCounter);
                break;
            case 2:
                player->columns = enterAutoColumns(player->columnCounter);
                break;
            default:
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
    if (askToContinue()) {
        writeToFile("/Users/talkoren/sandbox/university/lottory/data.bin", playersList, numOfPlayers, winningNumbers);
        *saveToFile = 1;
    }
    freePlayersList(playersList);
    free(winningNumbers);
    free(matchesSummary);
}

int askToContinue() {
    char ch;
    printf("Would you like to save game results(Y,N): ");
    getchar();//Clean buffer
    while (1) {
        ch = getchar();
        ch = tolower(ch);
        switch (ch) {
            case 'y':
                return 1;
            case 'n':
                return 0;
            default:
                printf("Invalid input\n");
                printf("Please enter choice again: ");
        }
    }
}

void option2(int saveToFile) {
    int *winningNumbers, *matchesSummary;
    PlayersList *playersList;
    FILE *fp;

    if (saveToFile == 0) {
        printf("No saved data\n");
        return;
    }
    fp = fopen("/Users/talkoren/sandbox/university/lottory/data.bin", "rb");
    checkFileAllocation(fp);

    playersList = readLastGameResultsFromFile(fp, &winningNumbers);
    calcResults(playersList, winningNumbers);
    printf("--------------------------------------------------\n");
    printf("AFTER READING\n");
    matchesSummary = sumColumnsMatches(playersList);
    printWinningNumbers(winningNumbers);
    printPlayersList(playersList);
    printColumnsSummary(matchesSummary);
    printPlayersWithMaxAvgMatch(playersList);
    freePlayersList(playersList);
    free(winningNumbers);
    free(matchesSummary);
}

int validateNumOfPlayers() {
    int numOfPlayers;

    printf("Enter number of players: ");//scan number of players
    scanf("%d", &numOfPlayers);
    while (numOfPlayers <= 0) {
        printf("Invalid input\n please enter again:");
        scanf("%d", &numOfPlayers);
    }

    return numOfPlayers;
}

int validateNumOfColumns() {
    int numOfCols;
    printf("Please enter number of columns: ");
    scanf("%d", &numOfCols);

    while (numOfCols <= 0) {
        printf("Invalid input\n please enter number again: ");
        scanf("%d", &numOfCols);
    }

    return numOfCols;
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

int validateMainMenuInput() {
    int choice;

    printMainMenu();
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            case 2:
            case 3:
                return choice;
            default:
                printf("Invalid input\n");
                printf("Please enter choice again: ");
        }
    }
}

void printSubMenu() {
    printf("Please choose one of the options:\n");
    printf("1. Manual lotto mode\n");
    printf("2. Auto lotto mode\n");
    printf(">> ");
}

int validateSubMenuInput() {
    int choice;

    printSubMenu();
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            case 2:
                return choice;
            default:
                printf("Invalid input\n");
                printf("Please enter choice again: ");
        }
    }
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

void checkFileAllocation(void *p) {
    if (p == NULL) {
        printf("File open failed\n");
        exit(1);
    }
}

ColumnsList *enterManualColumns(int numOfCols) {
    int numbers[6], bucket[16] = {0};
    ColumnNode *columnNode;
    ColumnsList *columnList = createColumnList();

    for (int i = 0; i < numOfCols; i++) {//for each column
        printf("please enter 6 numbers:");
        for (int j = 0; j < 6; j++) {//get 6 numbers
            scanf("%d", &numbers[j]);
            if (validateNumbers(numbers[j]) == 0) {
                printf("Invalid number\n please enter again: ");
                j--;
            } else if (bucket[numbers[j]] == 1) {
                printf("number is already use\n please enter again: ");
                j--;
            } else {
                bucket[numbers[j]] = 1;
            }
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

int validateNumbers(int number) {
    if (number < 1 || number > 15) {
        return 1;
    }
    return 0;
}

ColumnsList *enterAutoColumns(int numOfCols) {
    ColumnNode *columnNode;
    ColumnsList *columnList = createColumnList();
    int *numbers;

    for (int i = 0; i < numOfCols; i++) {//for each column
        numbers = generateRandomNumbers();
        columnNode = createColumn(numbers);
        if (columnList->head == NULL) {
            columnList->head = columnNode;
            columnList->tail = columnList->head;
        } else {
            columnList->tail->next = columnNode;
            columnList->tail = columnNode;
        }
        free(numbers);
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
        mergeSortColumnList(pPlayer->columns);
        pPlayer = pPlayer->next;
    }
}

void printWinningNumbers(int *winningNumbers) {
    printf("--------------------------------------------------\n");
    printf("WINNING NUMBERS:\n");
    printf("--------------------------------------------------\n");
    printColumn(winningNumbers, 6);
    printf("--------------------------------------------------\n");
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
    printf("--------------------------------------------------\n");
    printf("TOTAL MATCHES SUMMARY\n");
    printf("--------------------------------------------------\n");
    for (i = 6; i >= 0; i--) {
        printf("%d matches - %d\n", i, array[i]);
    }
    printf("--------------------------------------------------\n");
}

void printPlayersWithMaxAvgMatch(PlayersList *playersList) {
    double max;
    PlayerNode *pPlayer;


    for (pPlayer = playersList->head, max = 0; pPlayer != NULL; pPlayer = pPlayer->next) {
        if (pPlayer->avgMatch > max) {
            max = pPlayer->avgMatch;
        }
    }
    printf("--------------------------------------------------\n");
    printf("The players with the highest average:\n");
    for (pPlayer = playersList->head; pPlayer != NULL; pPlayer = pPlayer->next) {
        if (pPlayer->avgMatch == max) {
            printf("%s\n", pPlayer->name);
        }
    }
    printf("--------------------------------------------------\n");
}

void writeToFile(char *fName, PlayersList *playersList, int numOfPlayers, int *winningNumbers) {
    PlayerNode *pPlayer;
    ColumnNode *pCol;
    int nameLen;
    FILE *fp = fopen(fName, "wb");
    checkFileAllocation(fp);

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
    unsigned char mask = 0;

    for (i = 0, j = 0; i < 3; i++, j += 2) {
        compress[i] = compress[i] | (char) numbers[j];
        compress[i] = compress[i] << 4;
        compress[i] = compress[i] | (char) numbers[j + 1];
//        compress[i] = ~mask;
    }

    fwrite(compress, sizeof(char), 3, fp);
}

PlayersList *readLastGameResultsFromFile(FILE *fp, int **winningNumbers) {
    PlayersList *playersList;
    PlayerNode *pPlayer;
    ColumnsList *pColList;
    ColumnNode *pCol;
    char *playerName;
    unsigned char compress[3];
    int numOfPlayers, i, j, nameLen;

    fread(&numOfPlayers, sizeof(int), 1, fp);
    playersList = createPlayerList();
    for (i = 0; i < numOfPlayers; i++) {
        fread(&nameLen, sizeof(int), 1, fp);
        playerName = (char *) malloc(sizeof(char) * (nameLen + 1));
        checkMemoryAllocation(playerName);
        fread(playerName, sizeof(char), nameLen, fp);
        playerName[nameLen] = '\0';
        pPlayer = createNewPlayerNode(playerName);
        fread(&pPlayer->columnCounter, sizeof(int), 1, fp);
        pColList = createColumnList();
        for (j = 0; j < pPlayer->columnCounter; j++) {
            fread(compress, sizeof(unsigned char), 3, fp);
            pCol = createColumn(convertCompressedData(compress));
            if (pColList->head == NULL) {
                pColList->head = pColList->tail = pCol;
            } else {
                pColList->tail->next = pCol;
                pColList->tail = pCol;
            }
        }
        pPlayer->columns = pColList;
        if (playersList->head == NULL) {
            playersList->head = playersList->tail = pPlayer;
        } else {
            playersList->tail->next = pPlayer;
            playersList->tail = pPlayer;
        }
    }
    fread(compress, sizeof(unsigned char), 3, fp);
    *winningNumbers = convertCompressedData(compress);
    fclose(fp);

    return playersList;
}

int *convertCompressedData(unsigned char *compress) {
    int temp, i, j, *numbers;
    unsigned char mask1, mask2;

    numbers = (int *) malloc(sizeof(int) * 6);
    checkMemoryAllocation(numbers);

    //11111111
    //11110000
    //----------
    //1111----
    mask2 = 0xF;//(00001111)
    mask1 = mask2 << 4;//(11110000)

    for (i = 0, j = 0; i < 3; i++, j += 2) {
        numbers[j] = (int) ((compress[i] & mask1) >> 4);
        numbers[j + 1] = (int) (compress[i] & mask2);
    }

    return numbers;
}

void freePlayersList(PlayersList *playersList) {
    PlayerNode *pPlayer;

    for (pPlayer = playersList->head; pPlayer != NULL; pPlayer = playersList->head) {
        free(pPlayer->name);
        freeColumnsList(pPlayer->columns);
        playersList->head = playersList->head->next;
        free(pPlayer);
    }
    free(playersList);
}

void freeColumnsList(ColumnsList *columnsList) {
    ColumnNode *pCol;

    for (pCol = columnsList->head; pCol != NULL; pCol = columnsList->head) {
        free(pCol);
        columnsList->head = columnsList->head->next;
    }
    free(columnsList);
}

ColumnNode *SortedMerge(ColumnNode *a, ColumnNode *b) {
    ColumnNode *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->matches >= b->matches) {
        result = a;
        result->next = SortedMerge(a->next, b);
    } else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

void MergeSort(ColumnNode **headRef) {
    ColumnNode *head = *headRef;
    ColumnNode *a;
    ColumnNode *b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    FrontBackSplit(head, &a, &b);

    MergeSort(&a);
    MergeSort(&b);

    *headRef = SortedMerge(a, b);
}

void FrontBackSplit(ColumnNode *source,
                    ColumnNode **frontRef, ColumnNode **backRef) {
    ColumnNode *fast;
    ColumnNode *slow;
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

void mergeSortColumnList(ColumnsList *columnsList) {
    ColumnNode *head;
    MergeSort(&(columnsList->head));

    for (head = columnsList->head; head->next != NULL; head = head->next);
    columnsList->tail = head;
}



/*To do:
 - read from file - done
 - merge sort - done
 - free data - done
 - validation
 - clean code
 - split to files
 - calculate data after reading  -done
 - refactor prints
 */


