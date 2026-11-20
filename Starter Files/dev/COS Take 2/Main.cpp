// COS Take 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CollectionManager.h"
#include "StorageService.h"
#include "ConsoleUI.h"

int main() {
    CollectionManager myCollection;
    StorageService saveStorage("game_vault_data.txt");
    ConsoleUI app(myCollection, saveStorage);

    app.run();
    return 0;
}

