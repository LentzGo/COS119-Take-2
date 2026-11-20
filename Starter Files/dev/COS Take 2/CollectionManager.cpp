#include "CollectionManager.h"
#include <algorithm>
#include <cctype>

std::string CollectionManager::toLower(const std::string& str) const {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

void CollectionManager::addGame(const VideoGame& game) {
    games.push_back(game);
}

bool CollectionManager::removeGameByTitle(const std::string& title) {
    std::string target = toLower(title);
    for (size_t i = 0; i < games.size(); ++i) {
        if (toLower(games[i].getTitle()) == target) {
            games.erase(games.begin() + i);
            return true;
        }
    }
    return false;
}

void CollectionManager::clearCollection() {
    games.clear();
}

VideoGame* CollectionManager::findGameByTitle(const std::string& title) {
    std::string target = toLower(title);
    for (auto& game : games) {
        if (toLower(game.getTitle()) == target) {
            return &game;
        }
    }
    return nullptr;
}

std::vector<VideoGame> CollectionManager::filterByPlatform(const std::string& platform) const {
    std::vector<VideoGame> results;
    std::string target = toLower(platform);
    for (const auto& game : games) {
        if (toLower(game.getPlatform()) == target) {
            results.push_back(game);
        }
    }
    return results;
}

std::vector<VideoGame> CollectionManager::filterByStatus(const std::string& status) const {
    std::vector<VideoGame> results;
    std::string target = toLower(status);
    for (const auto& game : games) {
        if (toLower(game.getStatus()) == target) {
            results.push_back(game);
        }
    }
    return results;
}

void CollectionManager::sortByTitle() {
    std::sort(games.begin(), games.end(), [this](const VideoGame& a, const VideoGame& b) {
        return toLower(a.getTitle()) < toLower(b.getTitle());
        });
}

void CollectionManager::sortByYear() {
    std::sort(games.begin(), games.end(), [](const VideoGame& a, const VideoGame& b) {
        return a.getReleaseYear() > b.getReleaseYear();
        });
}

void CollectionManager::sortByRating() {
    std::sort(games.begin(), games.end(), [](const VideoGame& a, const VideoGame& b) {
        return a.getRating() > b.getRating();
        });
}

const std::vector<VideoGame>& CollectionManager::getAllGames() const {
    return games;
}

size_t CollectionManager::getGameCount() const {
    return games.size();
}

double CollectionManager::getAverageRating() const {
    int ratedCount = 0;
    int totalScore = 0;
    for (const auto& game : games) {
        if (game.getRating() > 0) {
            totalScore += game.getRating();
            ratedCount++;
        }
    }
    return (ratedCount == 0) ? 0.0 : static_cast<double>(totalScore) / ratedCount;
}

int CollectionManager::countByStatus(const std::string& status) const {
    int count = 0;
    std::string target = toLower(status);
    for (const auto& game : games) {
        if (toLower(game.getStatus()) == target) {
            count++;
        }
    }
    return count;
}
