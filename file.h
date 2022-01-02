#pragma once
#include "player.h"

//This function writes game results to a file
void writeToFile(char* fName, PlayersList* playersList, int numOfPlayers, int* winningNumbers);
//This function compresses a given column and writes it to a given file
void compressAndWrite(FILE* fp, int* numbers);
//This function converts compressed data into numbers
void convertCompressedData(unsigned char* compress, int* numbers);
//This function reads last game players list from a file and returning it
PlayersList* readLastGameResultsFromFile(FILE* fp, int* winningNumbers);