#include "file.h"

void writeToFile(char* fName, PlayersList* playersList, int numOfPlayers, int* winningNumbers) {
    PlayerNode* pPlayer;
    ColumnNode* pCol;
    int nameLen;
    FILE* fp = fopen(fName, "wb");
    checkMemoryAllocation(fp);

    fwrite(&numOfPlayers, sizeof(int), 1, fp);
    for (pPlayer = playersList->head; pPlayer != NULL; pPlayer = pPlayer->next) {
        nameLen = strlen(pPlayer->name);
        fwrite(&nameLen, sizeof(int), 1, fp);
        fwrite(pPlayer->name, sizeof(char), nameLen, fp);
        fwrite(&pPlayer->columnCounter, sizeof(int), 1, fp);

        for (pCol = pPlayer->columns->head; pCol != NULL; pCol = pCol->next) {
            compressAndWrite(fp, pCol->numbers);
        }

    }
    compressAndWrite(fp, winningNumbers);
    fclose(fp);
}

void compressAndWrite(FILE* fp, int* numbers) {
    unsigned char compress[3] = { 0 };
    int i, j;

    for (i = 0, j = 0; i < 3; i++, j += 2) {
        compress[i] = compress[i] | (char)numbers[j];
        compress[i] = compress[i] << 4;
        compress[i] = compress[i] | (char)numbers[j + 1];
    }

    fwrite(compress, sizeof(char), 3, fp);
}

void convertCompressedData(unsigned char* compress, int* numbers) {
    int temp, i, j;
    unsigned char mask1, mask2;

    mask2 = 0xF; //(00001111)
    mask1 = mask2 << 4; //(11110000)

    for (i = 0, j = 0; i < 3; i++, j += 2) {
        numbers[j] = (int)((compress[i] & mask1) >> 4);
        numbers[j + 1] = (int)(compress[i] & mask2);
    }
}

PlayersList* readLastGameResultsFromFile(FILE* fp, int* winningNumbers) {
    PlayersList* playersList;
    PlayerNode* pPlayer;
    ColumnsList* pColList;
    ColumnNode* pCol;
    char* playerName;
    unsigned char compress[3];
    int numOfPlayers, i, j, nameLen, numbers[6];

    fread(&numOfPlayers, sizeof(int), 1, fp);
    playersList = createPlayerList();

    for (i = 0; i < numOfPlayers; i++) {
        fread(&nameLen, sizeof(int), 1, fp);
        playerName = (char*)malloc(sizeof(char) * (nameLen + 1));
        checkMemoryAllocation(playerName);
        fread(playerName, sizeof(char), nameLen, fp);
        playerName[nameLen] = '\0';
        pPlayer = createNewPlayerNode(playerName);
        fread(&pPlayer->columnCounter, sizeof(int), 1, fp);
        pColList = createColumnList();

        for (j = 0; j < pPlayer->columnCounter; j++) {
            fread(compress, sizeof(unsigned char), 3, fp);
            convertCompressedData(compress, numbers);
            pCol = createColumn(numbers);
            insertNodeToEndColumnList(pColList, pCol);
        }

        pPlayer->columns = pColList;
        insertNodeToEndPlayerList(playersList, pPlayer);
    }

    fread(compress, sizeof(unsigned char), 3, fp);
    convertCompressedData(compress, winningNumbers);
    fclose(fp);

    return playersList;
}