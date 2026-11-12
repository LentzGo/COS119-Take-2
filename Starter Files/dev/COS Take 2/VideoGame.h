#pragma once
#include <string>

class VideoGame
{
private:
	std::string title; 
	std::string platform; 
	std::string genre; 
	int releaseYear; 
	std::string status; //backlog, playing, completed, borrowed
	int rating; // 0-10 - 0 being unrated

public: 
	VideoGame(std::string title, std::string platform, std::string genre, int releaseYear); 

	//Getters 
	std::string getTitle() const; 
	std::string getPlatform() const;
	std::string getGenre() const; 
	int getReleaseYear() const; 
	std::string getStatus() const; 
	int getRating() const; 

	//Setters
	void setStatus(const std::string& newStatus); 
	void setRating(int newRating);
};

