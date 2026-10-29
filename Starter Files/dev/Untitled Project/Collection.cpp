#include "Collection.h"

#include <algorithm>
#include <iostream>

void Collection::addGame(const Game& game)
{
    games_.push_back(game);
}

bool Collection::removeGame(const std::string& title)
{
    const auto originalSize = games_.size();

    games_.erase(
        std::remove_if(
            games_.begin(),
            games_.end(),
            [&title](const Game& game)
            {
                return game.getTitle() == title;
            }
        ),
        games_.end()
    );

    return games_.size() < originalSize;
}

Game* Collection::findGame(const std::string& title)
{
    for (Game& game : games_)
    {
        if (game.getTitle() == title)
        {
            return &game;
        }
    }

    return nullptr;
}

const Game* Collection::findGame(const std::string& title) const
{
    for (const Game& game : games_)
    {
        if (game.getTitle() == title)
        {
            return &game;
        }
    }

    return nullptr;
}

bool Collection::containsGame(const std::string& title) const
{
    return findGame(title) != nullptr;
}

std::size_t Collection::getSize() const
{
    return games_.size();
}

bool Collection::isEmpty() const
{
    return games_.empty();
}

const std::vector<Game>& Collection::getGames() const
{
    return games_;
}

void Collection::display() const
{
    if (games_.empty())
    {
        std::cout << "The collection is empty.\n";
        return;
    }

    for (const Game& game : games_)
    {
        std::cout << "Title: "
            << game.getTitle()
            << '\n';

        std::cout << "Cover art: "
            << (game.getCoverArt() ? "Yes" : "No")
            << "\n\n";
    }
}
