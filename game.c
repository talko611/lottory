#include "game.h"

void option1(int* saveToFile) {
    int i, subChoice, numOfPlayers, numOfCols, * winningNumbers, * matchesSummary;
    PlayersList* playersList;
    PlayerNode* player;
    char* playerName;

    playersList = createPlayerList();
    numOfPlayers = validateNumOfPlayers();

    for (i = 0; i < numOfPlayers; i++) {
        playerName = getPlayerName();
        player = createNewPlayerNode(playerName);
        subChoice = validateSubMenuInput();
        player->columnCounter = validateNumOfColumns();
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

        insertNodeToEndPlayerList(playersList, player);
    }
    printf("\nPlease wait, loading resutls...\n");

    winningNumbers = generateRandomNumbers();
    calcResults(playersList, winningNumbers);
    matchesSummary = sumColumnsMatches(playersList);
    printWinningNumbers(winningNumbers);
    printPlayersList(playersList);
    printColumnsSummary(matchesSummary);
    printPlayersWithMaxAvgMatch(playersList);

    if (askToContinue()) {
        writeToFile("data.bin", playersList, numOfPlayers, winningNumbers);
        *saveToFile = 1;
    }

    freePlayersList(playersList);
    free(winningNumbers);
    free(matchesSummary);
}

int askToContinue() {
    char ch;
    printf("\nWould you like to save game results(Y,N): ");
    getchar(); //Clean buffer
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
    int* winningNumbers, * matchesSummary;
    PlayersList* playersList;
    FILE* fp;

    if (saveToFile == 0) {
        printf("No saved data\n");
        return;
    }
    fp = fopen("data.bin", "rb");
    checkMemoryAllocation(fp);

    winningNumbers = (int*)malloc(sizeof(int) * 6);
    checkMemoryAllocation(winningNumbers);

    playersList = readLastGameResultsFromFile(fp, winningNumbers);
    calcResults(playersList, winningNumbers);
    printf("--------------------------------------------------\n");
    matchesSummary = sumColumnsMatches(playersList);
    printWinningNumbers(winningNumbers);
    printPlayersList(playersList);
    printColumnsSummary(matchesSummary);
    printPlayersWithMaxAvgMatch(playersList);
    freePlayersList(playersList);
    free(winningNumbers);
    free(matchesSummary);
}

void calcResults(PlayersList* playersList, int* winningNumbers) {
    PlayerNode* pPlayer;
    ColumnNode* pCol;
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