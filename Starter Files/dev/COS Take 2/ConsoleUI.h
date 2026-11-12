#pragma once
#include "CollectionManager.h"

class ConsoleUI
{
private:
	CollectionManager& manager; 
	bool isRunning; 

	void displayMenu() const; 
	int getValidatedInt(int min, int max) const;
	void handleAddGame(); 
	void handleViewGames() const; 

public:
	ConsoleUI(CollectionManager& manager); 
	void run();
};

