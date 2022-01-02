#include "player.h"

void printPlayer(PlayerNode* player) {
    int i;
    ColumnNode* temp = player->columns->head;
    printf("--------------------------------------------------\n");
    printf("Name: %s\n", player->name);
    while (temp != NULL) {
        printf("(Matches: %d) ", temp->matches);
        printColumn(temp->numbers, 6);
        temp = temp->next;
    }
    printf("Average match: %f\n", player->avgMatch);
}

PlayersList* createPlayerList() {
    PlayersList* res;

    res = (PlayersList*)malloc(sizeof(PlayersList));
    checkMemoryAllocation(res);

    res->head = NULL;
    res->tail = NULL;

    return res;
}

void printPlayersList(PlayersList* playersList) {
    PlayerNode* temp = playersList->head;

    while (temp != NULL) {
        printPlayer(temp);
        temp = temp->next;
    }
}

void printPlayersWithMaxAvgMatch(PlayersList* playersList) {
    double max;
    PlayerNode* pPlayer;


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

char* getPlayerName() {
    char* name, ch;
    int phySize = 1, logSize = 0;

    name = (char*)malloc(sizeof(char) * phySize);
    checkMemoryAllocation(name);

    printf("\nPlease enter a name: ");
    getchar(); //Clean buffer
    ch = getchar();

    while (ch != '\n') {
        if (logSize == phySize) {
            phySize *= 2;
            name = (char*)realloc(name, sizeof(char) * phySize);
            checkMemoryAllocation(name);
        }
        name[logSize] = ch;
        logSize++;
        ch = getchar();
    }
    name = (char*)realloc(name, sizeof(char) * (logSize + 1));
    checkMemoryAllocation(name);
    name[logSize] = '\0';

    return name;
}

PlayerNode* createNewPlayerNode(char* name) {
    PlayerNode* res;
    res = (PlayerNode*)malloc(sizeof(PlayerNode));
    checkMemoryAllocation(res);

    res->name = name;
    res->avgMatch = 0;
    res->columnCounter = 0;
    res->columns = NULL;
    res->next = NULL;

    return res;
}

void insertNodeToEndPlayerList(PlayersList* lst, PlayerNode* newTail) {
    if (isEmptyPlayerList(lst)) {
        lst->head = lst->tail = newTail;
    }
    else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

int isEmptyPlayerList(PlayersList* lst) {
    if (lst->head == NULL) {
        return 1;
    }
    return 0;
}

void freePlayersList(PlayersList* playersList) {
    PlayerNode* pPlayer;

    for (pPlayer = playersList->head; pPlayer != NULL; pPlayer = playersList->head) {
        free(pPlayer->name);
        freeColumnsList(pPlayer->columns);
        playersList->head = playersList->head->next;
        free(pPlayer);
    }
    free(playersList);
}