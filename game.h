#include "player.h"
#include "file.h"
#include "print.h"

//This function simulates the lottery game
void option1(int* saveToFile);
//This function checks if the user wants to save last gave results and returns 1 for YES or 0 for NO
int askToContinue();
//This function presents last game results
void option2(int saveToFile);
//This function calculates matches between playersList and winningNumbers
void calcResults(PlayersList* playersList, int* winningNumbers);