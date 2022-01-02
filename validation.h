#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//This function scans number of columns for a player and validates it
int validateNumOfColumns();
//This function scans number of players and validates it
int validateNumOfPlayers();
//This function scans an option (1 / 2 / 3) for main menu, validates it and returns it
int validateMainMenuInput();
//This function scans an option (1 / 2) for sub menu, validates it and returns it
int validateSubMenuInput();
//This function validates a number is between 1 and 15
int validateNumbers(int number);
//This function checks memory allocation
void checkMemoryAllocation(void* p);