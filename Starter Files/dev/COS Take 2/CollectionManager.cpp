#include "CollectionManager.h"

void CollectionManager::addGame(const VideoGame& game)
{
	games.push_back(game);
}

bool CollectionManager::removeGameByTitle(const std::string& title)
{
	for (size_t i = 0; i < games.size(); ++i)
	{
		if (games[i].getTitle() == title)
		{
			games.erase(games.begin() + i);
			return true;
		}
	}
	return false;
}

VideoGame* CollectionManager::findGameByTitle(const std::string& title)
{
	for (auto& games : games)
	{
		if (games.getTitle() == title)
		{
			return &games; 
		}
	}
	return nullptr;
}

const std::vector<VideoGame>& CollectionManager::getAllGames() const
{
	return games;
}