#include "validation.h"

int validateNumOfColumns() {
    int numOfCols;

    printf("Please enter number of columns: ");
    scanf("%d", &numOfCols);

    while (numOfCols <= 0) {
        printf("Invalid input\nPlease enter number again: ");
        scanf("%d", &numOfCols);
    }

    return numOfCols;
}

int validateNumOfPlayers() {
    int numOfPlayers;

    printf("\nEnter number of players: ");
    scanf("%d", &numOfPlayers);
    while (numOfPlayers <= 0) {
        printf("Invalid input\nPlease enter again:");
        scanf("%d", &numOfPlayers);
    }

    return numOfPlayers;
}

int validateNumbers(int number) {
    if (number >= 1 && number <= 15) {
        return 1;
    }
    return 0;
}

void checkMemoryAllocation(void* p) {
    if (p == NULL) {
        printf("Memory Allocation failed\n");
        exit(1);
    }
}