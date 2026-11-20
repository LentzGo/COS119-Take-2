#pragma once
#include <vector>
#include <string>
#include "VideoGame.h"

class CollectionManager {
private:
    std::vector<VideoGame> games;
    std::string toLower(const std::string& str) const;

public:
    void addGame(const VideoGame& game);
    bool removeGameByTitle(const std::string& title);
    void clearCollection();

    // Pointer-based lookup for direct modification
    VideoGame* findGameByTitle(const std::string& title);

    // Filtering & Sorting
    std::vector<VideoGame> filterByPlatform(const std::string& platform) const;
    std::vector<VideoGame> filterByStatus(const std::string& status) const;
    void sortByTitle();
    void sortByYear();
    void sortByRating();

    // Accessors & Analytics
    const std::vector<VideoGame>& getAllGames() const;
    size_t getGameCount() const;
    double getAverageRating() const;
    int countByStatus(const std::string& status) const;
};


