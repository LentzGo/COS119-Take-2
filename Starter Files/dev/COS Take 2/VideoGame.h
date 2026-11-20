#pragma once
#include <string>

class VideoGame {
private:
    std::string title;
    std::string platform;
    std::string genre;
    int releaseYear;
    std::string status; // "Backlog", "Playing", "Completed", "Dropped"
    int rating;         // 0 (Unrated) to 10

public:
    VideoGame(std::string title, std::string platform, std::string genre,
        int releaseYear, std::string status = "Backlog", int rating = 0);

    // Getters
    std::string getTitle() const;
    std::string getPlatform() const;
    std::string getGenre() const;
    int getReleaseYear() const;
    std::string getStatus() const;
    int getRating() const;

    // Setters
    void setStatus(const std::string& newStatus);
    void setRating(int newRating);
};