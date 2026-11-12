#include "ConsoleUI.h"
#include <iostream>
#include <limits>

ConsoleUI::ConsoleUI(CollectionManager& manager) : manager(manager), isRunning(true) {}

void ConsoleUI::run()
{
	while (isRunning)
	{
		displayMenu(); 
		int choice = getValidatedInt(1, 4);

		switch (choice)
		{
		case 1: handleAddGame(); break; 
		case 2: handleViewGames(); break; 
		case 3: std::cout << "Search & Update Coming Soon!\n";
		case 4: 
			isRunning = false;
			std::cout << "Sealing the Vault. Goodby!\n"; 
			break; 
		}
	}
}

void ConsoleUI::displayMenu() const
{
	std::cout << "\n==============================\n";
	std::cout << "    GAME VAULT INVENTORY      \n";
	std::cout << "==============================\n";
	std::cout << "1. Add a Video Game\n";
	std::cout << "2. View Collection\n";
	std::cout << "3. Search / Update Game\n";
	std::cout << "4. Exit\n";
	std::cout << "Select an option (1-4): ";
}

int ConsoleUI::getValidatedInt(int min, int max) const
{
	int value; 
	while (true)
	{
		if (std::cin >> value && value >= min && value <= max)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			return value; 
		}
		std::cout << "Invalid Input. Enter a Number Between " << min << " and " << max << ": "; 
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void ConsoleUI::handleAddGame()
{
	std::string title, platform, genre; 
	int year; 

	std::cout << "Enter Title: "; 
	std::getline(std::cin, title); 
	std::cout << "Enter Platform (e.g. PC, PS5, XBX, Switch): "; 
	std::getline(std::cin, platform); 
	std::cout << "Enter Genre: "; 
	std::getline(std::cin, genre); 
	std::cout << "Enter Release Year (1970-2030): "; 
	year = getValidatedInt(1970, 2030); 

	manager.addGame(VideoGame(title, platform, genre, year));
	std::cout << "Added '" << title << "' to your collection!\n";
}

void ConsoleUI::handleViewGames() const
{
	const auto& games = manager.getAllGames(); 
	if (games.empty())
	{
		std::cout << "\nYour Collection is Currently Empty.\n";
		return; 
	}

	std::cout << "\n--- Your Video Game Collection (" << games.size() << ") ---\n";
	for (const auto& g : games)
	{
		std::cout << "- " << g.getTitle() << " (" << g.getReleaseYear() << ") | "
			<< g.getPlatform() << " | " << g.getGenre()
			<< " | Status: " << g.getStatus() << "\n"; 
	}
}