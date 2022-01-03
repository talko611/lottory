//Adi Veiszman: 206820045
//Tal Koren: 312498520

#include "game.h"

int main() {
    int choice, saveToFile = 0;

    choice = validateMainMenuInput();
    while (choice != 3) {

        switch (choice) {
            case 1:
                option1(&saveToFile);
                break;
            case 2:
                option2(saveToFile);
                break;
            default:
                break;
        }

        choice = validateMainMenuInput();
    }
}