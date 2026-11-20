#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>
#include <limits>

ConsoleUI::ConsoleUI(CollectionManager& manager) : manager(manager), isRunning(true) {}

void ConsoleUI::run() {
    while (isRunning) {
        displayMenu();
        int choice = getValidatedInt(1, 5);

        switch (choice) {
        case 1: handleAddGame(); break;
        case 2: handleViewGames(); break;
        case 3: handleSearchAndUpdate(); break;
        case 4: handleDeleteGame(); break;
        case 5:
            isRunning = false;
            std::cout << "Exiting Game Vault. Goodbye!\n";
            break;
        }
    }
}

void ConsoleUI::displayMenu() const {
    std::cout << "\n========================================\n";
    std::cout << "       GAME VAULT INVENTORY (v0.2)      \n";
    std::cout << "========================================\n";
    std::cout << "1. Add a Video Game\n";
    std::cout << "2. View Full Collection\n";
    std::cout << "3. Search & Update Game (Status/Rating)\n";
    std::cout << "4. Remove a Video Game\n";
    std::cout << "5. Exit\n";
    std::cout << "Select an option (1-5): ";
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

        // Check that string isn't empty or only whitespace
        if (input.find_first_not_of(" \t\n\r") != std::string::npos) {
            return input;
        }
        std::cout << "Input cannot be blank. Please try again.\n";
    }
}

void ConsoleUI::handleAddGame() {
    std::cout << "\n--- Add New Game ---\n";
    std::string title = getValidatedString("Enter Title: ");

    // Prevent duplicate titles
    if (manager.findGameByTitle(title) != nullptr) {
        std::cout << "A game with that title already exists in your collection!\n";
        return;
    }

    std::string platform = getValidatedString("Enter Platform (e.g., PC, PS5, Switch): ");
    std::string genre = getValidatedString("Enter Genre: ");
    std::cout << "Enter Release Year (1970-2030): ";
    int year = getValidatedInt(1970, 2030);

    manager.addGame(VideoGame(title, platform, genre, year));
    std::cout << "Successfully added '" << title << "'!\n";
}

void ConsoleUI::handleViewGames() const {
    const auto& games = manager.getAllGames();
    if (games.empty()) {
        std::cout << "\nYour collection is currently empty.\n";
        return;
    }

    std::cout << "\n--- Video Game Collection (" << games.size() << " Total) ---\n";
    std::cout << std::left
        << std::setw(26) << "TITLE"
        << std::setw(12) << "PLATFORM"
        << std::setw(14) << "GENRE"
        << std::setw(6) << "YEAR"
        << std::setw(12) << "STATUS"
        << "RATING\n";
    std::cout << std::string(78, '-') << "\n";

    for (const auto& g : games) {
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
        std::cout << "Status updated to '" << gamePtr->getStatus() << "'!\n";
    }
    else if (choice == 2) {
        std::cout << "Enter new rating (1-10): ";
        int newRating = getValidatedInt(1, 10);
        gamePtr->setRating(newRating);
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
        std::cout << "Game removed from collection.\n";
    }
    else {
        std::cout << "Deletion canceled.\n";
    }
}