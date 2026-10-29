#pragma once

#include "Game.h"
#include <string>
#include <vector>

//Manages the games in the user's collection.

class Collection
{
public:
	void addGame(const Game& game); 
	bool removeGame(const std::string& title);

	Game* findGame(const std::string& title);
	const Game* findGame(const std::string& title)const; 

	bool containsGame(const std::string& title)const;

	std::size_t getSize() const;
	bool isEmpty() const;

	const std::vector<Game>& getGames() const;

	void display() const; 

private:
	std::vector<Game> games_;
};

