#include "random.h"

int generateRandomNumber() {
    int num;

    srand(time(NULL));
    num = 1 + rand() % 16;

    return num;
}

int* generateRandomNumbers() {
    int* numbers, i, j, bucket[16] = { 0 }, counter, num;

    numbers = (int*)malloc(sizeof(int) * 6);
    checkMemoryAllocation(numbers);

    counter = 0;
    while (counter < 6) {
        num = generateRandomNumber();
        if (bucket[num] == 0) {
            counter++;
            bucket[num] = 1;
        }
    }
    for (i = 0, j = 0; i < 16; i++) {
        if (bucket[i] == 1) {
            numbers[j++] = i;
        }
    }

    return numbers;
}