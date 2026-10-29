#include <iostream>

#include "Game.h"
#include "Platform.h"

int main()
{
    // This is intentionally invalid:
    // PS5 does not belong to the Xbox platform family.
    PlatformInfo invalidPlatform(
        Platform::Xbox,
        PlatformVersion::PS5
    );

    if (!invalidPlatform.isValid())
    {
        std::cout << "Invalid platform combination detected.\n";
        return 0;
    }

    Game game(
        "Invalid Test Game",
        invalidPlatform,
        false
    );

    game.display();

    return 0;
}