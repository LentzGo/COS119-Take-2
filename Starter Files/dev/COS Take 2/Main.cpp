// COS Take 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CollectionManager.h"
#include "ConsoleUI.h"

int main() {
    CollectionManager myCollection;
    ConsoleUI app(myCollection);
    app.run();
    return 0;
}

