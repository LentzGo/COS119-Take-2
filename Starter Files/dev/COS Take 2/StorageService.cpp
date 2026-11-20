#include "StorageService.h"
#include <fstream>
#include <sstream>

StorageService::StorageService(const std::string& filePath) : filePath(filePath) {}

std::string StorageService::getFilePath() const {
    return filePath;
}

bool StorageService::saveCollection(const CollectionManager& manager) const {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        return false;
    }

    for (const auto& game : manager.getAllGames()) {
        outFile << game.getTitle() << "|"
            << game.getPlatform() << "|"
            << game.getGenre() << "|"
            << game.getReleaseYear() << "|"
            << game.getStatus() << "|"
            << game.getRating() << "\n";
    }

    outFile.close();
    return true;
}

bool StorageService::loadCollection(CollectionManager& manager, int& loadedCount) const {
    loadedCount = 0;
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        return false;
    }

    manager.clearCollection();
    std::string line;

    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string title, platform, genre, yearStr, status, ratingStr;

        if (std::getline(ss, title, '|') &&
            std::getline(ss, platform, '|') &&
            std::getline(ss, genre, '|') &&
            std::getline(ss, yearStr, '|') &&
            std::getline(ss, status, '|') &&
            std::getline(ss, ratingStr, '|')) {
            try {
                int year = std::stoi(yearStr);
                int rating = std::stoi(ratingStr);
                manager.addGame(VideoGame(title, platform, genre, year, status, rating));
                loadedCount++;
            }
            catch (...) {
                continue;
            }
        }
    }

    inFile.close();
    return true;
}

