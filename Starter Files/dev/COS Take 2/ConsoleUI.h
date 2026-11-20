#pragma once
#include "CollectionManager.h"

class ConsoleUI {
private:
    CollectionManager& manager;
    bool isRunning;

    void displayMenu() const;
    int getValidatedInt(int min, int max) const; // <-- Make sure this line is in ConsoleUI.h
    std::string getValidatedString(const std::string& prompt) const;

    void handleAddGame();
    void handleViewGames() const;
    void handleSearchAndUpdate();
    void handleDeleteGame();

public:
    ConsoleUI(CollectionManager& manager);
    void run();
};