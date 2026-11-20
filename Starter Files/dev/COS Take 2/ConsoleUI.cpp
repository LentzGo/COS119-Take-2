#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>
#include <limits>

ConsoleUI::ConsoleUI(CollectionManager& manager, StorageService& storage)
    : manager(manager), storage(storage), isRunning(true), hasUnsavedChanges(false) {
}

void ConsoleUI::run() {
    int loadedCount = 0;
    if (storage.loadCollection(manager, loadedCount)) {
        std::cout << "[System] Loaded " << loadedCount << " game(s) from '" << storage.getFilePath() << "'.\n";
    }
    else {
        std::cout << "[System] No existing save file found. Starting a new collection!\n";
    }

    while (isRunning) {
        displayMenu();
        int choice = getValidatedInt(1, 9);

        switch (choice) {
        case 1: handleAddGame(); break;
        case 2: handleViewGames(); break;
        case 3: handleSearchAndUpdate(); break;
        case 4: handleDeleteGame(); break;
        case 5: handleFilterAndSort(); break;
        case 6: handleViewStats(); break;
        case 7: handleSaveData(); break;
        case 8: handleLoadData(); break;
        case 9: handleExit(); break;
        }
    }
}

void ConsoleUI::displayMenu() const {
    std::cout << "\n============================================\n";
    std::cout << "      GAME VAULT INVENTORY (v1.0 FINAL)     \n";
    std::cout << "============================================\n";
    std::cout << "1. Add a Video Game\n";
    std::cout << "2. View Full Collection\n";
    std::cout << "3. Search & Update Game (Status/Rating)\n";
    std::cout << "4. Remove a Video Game\n";
    std::cout << "5. Filter or Sort Collection\n";
    std::cout << "6. Collection Statistics\n";
    std::cout << "7. Save Collection to File\n";
    std::cout << "8. Load Collection from File\n";
    std::cout << "9. Exit\n";
    if (hasUnsavedChanges) {
        std::cout << "* You have unsaved changes *\n";
    }
    std::cout << "Select an option (1-9): ";
}

int ConsoleUI::getValidatedInt(int min, int max) const {
    int value;
    while (true) {
        if (std::cin >> value && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid input. Enter a number between " << min << " and " << max << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string ConsoleUI::getValidatedString(const std::string& prompt) const {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (input.find('|') != std::string::npos) {
            std::cout << "Input cannot contain the '|' character. Please try again.\n";
            continue;
        }

        if (input.find_first_not_of(" \t\n\r") != std::string::npos) {
            return input;
        }
        std::cout << "Input cannot be blank. Please try again.\n";
    }
}

void ConsoleUI::printGamesTable(const std::vector<VideoGame>& gameList, const std::string& header) const {
    if (gameList.empty()) {
        std::cout << "\nNo matching games found.\n";
        return;
    }

    std::cout << "\n--- " << header << " (" << gameList.size() << ") ---\n";
    std::cout << std::left
        << std::setw(26) << "TITLE"
        << std::setw(12) << "PLATFORM"
        << std::setw(14) << "GENRE"
        << std::setw(6) << "YEAR"
        << std::setw(12) << "STATUS"
        << "RATING\n";
    std::cout << std::string(78, '-') << "\n";

    for (const auto& g : gameList) {
        std::string ratingStr = (g.getRating() == 0) ? "Unrated" : std::to_string(g.getRating()) + "/10";
        std::string displayTitle = g.getTitle();
        if (displayTitle.length() > 24) {
            displayTitle = displayTitle.substr(0, 21) + "...";
        }

        std::cout << std::left
            << std::setw(26) << displayTitle
            << std::setw(12) << g.getPlatform()
            << std::setw(14) << g.getGenre()
            << std::setw(6) << g.getReleaseYear()
            << std::setw(12) << g.getStatus()
            << ratingStr << "\n";
    }
}

void ConsoleUI::handleAddGame() {
    std::cout << "\n--- Add New Game ---\n";
    std::string title = getValidatedString("Enter Title: ");

    if (manager.findGameByTitle(title) != nullptr) {
        std::cout << "A game with that title already exists in your collection!\n";
        return;
    }

    std::string platform = getValidatedString("Enter Platform (e.g., PC, PS5, Switch): ");
    std::string genre = getValidatedString("Enter Genre: ");
    std::cout << "Enter Release Year (1970-2030): ";
    int year = getValidatedInt(1970, 2030);

    manager.addGame(VideoGame(title, platform, genre, year));
    hasUnsavedChanges = true;
    std::cout << "Successfully added '" << title << "'!\n";
}

void ConsoleUI::handleViewGames() const {
    printGamesTable(manager.getAllGames(), "Full Video Game Collection");
}

void ConsoleUI::handleSearchAndUpdate() {
    if (manager.getGameCount() == 0) {
        std::cout << "\nYour collection is empty. Add a game first!\n";
        return;
    }

    std::string searchTitle = getValidatedString("\nEnter exact title to search: ");
    VideoGame* gamePtr = manager.findGameByTitle(searchTitle);

    if (gamePtr == nullptr) {
        std::cout << "Game '" << searchTitle << "' was not found.\n";
        return;
    }

    std::cout << "\nFound: " << gamePtr->getTitle() << " (" << gamePtr->getPlatform() << ")\n";
    std::cout << "Current Status: " << gamePtr->getStatus()
        << " | Current Rating: " << gamePtr->getRating() << "/10\n";

    std::cout << "\nWhat would you like to update?\n";
    std::cout << "1. Update Completion Status\n";
    std::cout << "2. Update User Rating (1-10)\n";
    std::cout << "3. Cancel\n";
    std::cout << "Choice: ";
    int choice = getValidatedInt(1, 3);

    if (choice == 1) {
        std::cout << "Select New Status:\n";
        std::cout << "1. Backlog\n2. Playing\n3. Completed\n4. Dropped\nChoice: ";
        int statusChoice = getValidatedInt(1, 4);
        switch (statusChoice) {
        case 1: gamePtr->setStatus("Backlog"); break;
        case 2: gamePtr->setStatus("Playing"); break;
        case 3: gamePtr->setStatus("Completed"); break;
        case 4: gamePtr->setStatus("Dropped"); break;
        }
        hasUnsavedChanges = true;
        std::cout << "Status updated to '" << gamePtr->getStatus() << "'!\n";
    }
    else if (choice == 2) {
        std::cout << "Enter new rating (1-10): ";
        int newRating = getValidatedInt(1, 10);
        gamePtr->setRating(newRating);
        hasUnsavedChanges = true;
        std::cout << "Rating updated to " << gamePtr->getRating() << "/10!\n";
    }
}

void ConsoleUI::handleDeleteGame() {
    if (manager.getGameCount() == 0) {
        std::cout << "\nYour collection is empty.\n";
        return;
    }

    std::string title = getValidatedString("\nEnter the title of the game to remove: ");
    VideoGame* gamePtr = manager.findGameByTitle(title);

    if (gamePtr == nullptr) {
        std::cout << "Game '" << title << "' not found.\n";
        return;
    }

    std::string confirm = getValidatedString("Are you sure you want to delete '" + gamePtr->getTitle() + "'? (y/n): ");
    if (confirm == "y" || confirm == "Y") {
        manager.removeGameByTitle(title);
        hasUnsavedChanges = true;
        std::cout << "Game removed from collection.\n";
    }
    else {
        std::cout << "Deletion canceled.\n";
    }
}

void ConsoleUI::handleFilterAndSort() {
    if (manager.getGameCount() == 0) {
        std::cout << "\nYour collection is empty.\n";
        return;
    }

    std::cout << "\n--- Filter & Sort ---\n";
    std::cout << "1. Filter by Platform\n";
    std::cout << "2. Filter by Completion Status\n";
    std::cout << "3. Sort Collection by Title (A-Z)\n";
    std::cout << "4. Sort Collection by Release Year (Newest First)\n";
    std::cout << "5. Sort Collection by User Rating (Highest First)\n";
    std::cout << "6. Back to Main Menu\n";
    std::cout << "Choice: ";
    int choice = getValidatedInt(1, 6);

    switch (choice) {
    case 1: {
        std::string platform = getValidatedString("Enter Platform to filter by: ");
        printGamesTable(manager.filterByPlatform(platform), "Games on " + platform);
        break;
    }
    case 2: {
        std::cout << "1. Backlog  2. Playing  3. Completed  4. Dropped\nChoice: ";
        int s = getValidatedInt(1, 4);
        std::string status = (s == 1) ? "Backlog" : (s == 2) ? "Playing" : (s == 3) ? "Completed" : "Dropped";
        printGamesTable(manager.filterByStatus(status), "Status: " + status);
        break;
    }
    case 3:
        manager.sortByTitle();
        hasUnsavedChanges = true;
        std::cout << "Collection sorted alphabetically by Title.\n";
        handleViewGames();
        break;
    case 4:
        manager.sortByYear();
        hasUnsavedChanges = true;
        std::cout << "Collection sorted by Release Year.\n";
        handleViewGames();
        break;
    case 5:
        manager.sortByRating();
        hasUnsavedChanges = true;
        std::cout << "Collection sorted by Rating.\n";
        handleViewGames();
        break;
    case 6:
        break;
    }
}

void ConsoleUI::handleViewStats() const {
    size_t total = manager.getGameCount();
    if (total == 0) {
        std::cout << "\nAdd some games first to view collection statistics!\n";
        return;
    }

    int completed = manager.countByStatus("Completed");
    int playing = manager.countByStatus("Playing");
    int backlog = manager.countByStatus("Backlog");
    int dropped = manager.countByStatus("Dropped");
}

void ConsoleUI::handleSaveData() {
    if (storage.saveCollection(manager)) {
        hasUnsavedChanges = false;
        std::cout << "Collection successfully saved to '" << storage.getFilePath() << "'!\n";
    }
    else {
        std::cout << "Error: Could not write to '" << storage.getFilePath() << "'.\n";
    }
}

void ConsoleUI::handleLoadData() {
    if (hasUnsavedChanges) {
        std::string confirm = getValidatedString("You have unsaved changes that will be overwritten. Continue? (y/n): ");
        if (confirm != "y" && confirm != "Y") {
            std::cout << "Load canceled.\n";
            return;
        }
    }

    int loadedCount = 0;
    if (storage.loadCollection(manager, loadedCount)) {
        hasUnsavedChanges = false;
        std::cout << "Successfully loaded " << loadedCount << " game(s) from '" << storage.getFilePath() << "'!\n";
    }
    else {
        std::cout << "No save file found at '" << storage.getFilePath() << "'. Save your collection first!\n";
    }
}

void ConsoleUI::handleExit() {
    if (hasUnsavedChanges) {
        std::string savePrompt = getValidatedString("\nYou have unsaved changes. Save before exiting? (y/n): ");
        if (savePrompt == "y" || savePrompt == "Y") {
            handleSaveData();
        }
    }
    isRunning = false;
    std::cout << "Exiting Game Vault. Goodbye!\n";
}