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

VideoGame* CollectionManager::findGameByTitle(const std::string& title) {
    std::string target = toLower(title);
    for (auto& game : games) {
        if (toLower(game.getTitle()) == target) {
            return &game;
        }
    }
    return nullptr;
}

const std::vector<VideoGame>& CollectionManager::getAllGames() const {
    return games;
}

size_t CollectionManager::getGameCount() const {
    return games.size();
}