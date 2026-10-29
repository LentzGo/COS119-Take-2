#include "Game.h"
#include <iostream>

Game::Game(
    const std::string& title,
    const PlatformInfo& platform,
    bool hasCoverArt
)
    : title(title),
    platform(platform),
    coverArt(coverArt)
{
}

std::string Game::getTitle() const
{
    return title;
}

PlatformInfo Game::getPlatform() const
{
    return platform;
}

bool Game::getCoverArt() const
{
    return coverArt;
}

void Game::display() const
{
    std::cout << "Title: " << title << '\n';

    platform.display();

    std::cout << "Cover Art: "
        << (coverArt ? "Yes" : "No")
        << '\n';
}