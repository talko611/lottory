#include "print.h"

void printMainMenu() {
    int i;
    printf("--------------------------------------------------\n");
    printf("LOTTERY GAME\n");
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

void printWinningNumbers(int* winningNumbers) {
    printf("\n--------------------------------------------------\n");
    printf("WINNING NUMBERS:\n");
    printf("--------------------------------------------------\n");
    printColumn(winningNumbers, 6);
    printf("--------------------------------------------------\n");
}
