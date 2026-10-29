#pragma once
#include "Platform.h"
#include <string>

//Represents one game title.

class Game
{
private:
	std::string title; 
	PlatformInfo platform;
	bool coverArt;

public:
	Game(
		const std::string& title,
		const PlatformInfo& platform,
		bool coverArt
	);

	std::string getTitle() const; 
	PlatformInfo getPlatform() const;
	bool getCoverArt() const;

	void display() const;
};

