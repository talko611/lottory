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
            printf("` enter choice again: ");
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