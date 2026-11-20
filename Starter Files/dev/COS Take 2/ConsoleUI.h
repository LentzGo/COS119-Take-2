#pragma once
#include <string>
#include <vector>
#include "CollectionManager.h"
#include "StorageService.h"

class ConsoleUI {
private:
    CollectionManager& manager;
    StorageService& storage;
    bool isRunning;
    bool hasUnsavedChanges;

    void displayMenu() const;
    int getValidatedInt(int min, int max) const;
    std::string getValidatedString(const std::string& prompt) const;
    void printGamesTable(const std::vector<VideoGame>& gameList, const std::string& header) const;

    // Core Handlers
    void handleAddGame();
    void handleViewGames() const;
    void handleSearchAndUpdate();
    void handleDeleteGame();
    void handleFilterAndSort();
    void handleViewStats() const;
    void handleSaveData();
    void handleLoadData();
    void handleExit();

public:
    ConsoleUI(CollectionManager& manager, StorageService& storage);
    void run();
};
