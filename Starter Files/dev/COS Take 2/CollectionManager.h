#pragma once
#include <vector>
#include <string>
#include "VideoGame.h"

class CollectionManager
{
private: 
	std::vector<VideoGame> games; 

public:
	void addGame(const VideoGame& game); 
	bool removeGameByTitle(const std::string& title); 

	//returns a pointer to allow direct editing, or nullptr if not found
	VideoGame* findGameByTitle(const std::string& title); 

	//returns a const reference to avoid copying the whole vector
	const std::vector<VideoGame>& getAllGames() const; 
};

