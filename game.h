#include "player.h"
#include "file.h"
#include "print.h"

//This function simulates the lottery game
void option1(int* saveToFile);
//This function checks if the user wants to save last gave results and returns 1 for YES or 0 for NO
int askToContinue();
//This function presents last game results
void option2(int saveToFile);
//This function scans an option (1 / 2 / 3) for main menu, validates it and returns it
int validateMainMenuInput();
//This function scans an option  (1 / 2) for sub menu, validates it and returns it
int validateSubMenuInput();