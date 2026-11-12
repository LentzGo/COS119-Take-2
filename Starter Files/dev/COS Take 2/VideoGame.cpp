#include "VideoGame.h"

VideoGame::VideoGame(std::string title, std::string platform, std::string genre, int releaseYear)
	: title(title), platform(platform), genre(genre), releaseYear(releaseYear), status("Backlog"), rating(0) {}

std::string VideoGame::getTitle() const { return title; }
std::string VideoGame::getPlatform() const { return platform; }
std::string VideoGame::getGenre() const { return genre; }
int VideoGame::getReleaseYear() const { return releaseYear; }
std::string VideoGame::getStatus() const { return status; }
int VideoGame::getRating() const { return rating; }

void VideoGame::setStatus(const std::string& newStatus) { status = newStatus; }
void VideoGame::setRating(int newRating)
{
	if (newRating >= 0 && newRating <= 10)
	{
		rating = newRating;
	}
}