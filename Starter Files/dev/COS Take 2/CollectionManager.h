#pragma once
#include <vector>
#include <string>
#include "VideoGame.h"

class CollectionManager {
private:
    std::vector<VideoGame> games;

    // Helper for case-insensitive title matching
    std::string toLower(const std::string& str) const;

public:
    void addGame(const VideoGame& game);
    bool removeGameByTitle(const std::string& title);

    // Returns a pointer to allow direct editing, or nullptr if not found
    VideoGame* findGameByTitle(const std::string& title);

    // Returns a const reference to avoid copying the whole vector
    const std::vector<VideoGame>& getAllGames() const;
    size_t getGameCount() const;
};

