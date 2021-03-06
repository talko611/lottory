#pragma once
#include "column.h"
#include "validation.h"

//This function prints a player's results
void printPlayer(PlayerNode* player);
//This function creates player list and returns it
PlayersList* createPlayerList();
//This function prints a players list results
void printPlayersList(PlayersList* playersList);
//This function prints the player name with the max matches average
void printPlayersWithMaxAvgMatch(PlayersList* playersList);
//This function scans a player name
char* getPlayerName();
//This function creates a new player node
PlayerNode* createNewPlayerNode(char* name);
//This function inserts player node to end of player list
void insertNodeToEndPlayerList(PlayersList* lst, PlayerNode* newTail);
//This function frees a player list
void freePlayersList(PlayersList* playersList);
//This function checks if a given player is empty
int isEmptyPlayerList(PlayersList* lst);