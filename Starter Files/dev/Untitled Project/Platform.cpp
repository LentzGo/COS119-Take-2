#include "Platform.h"
#include <iostream>


//Implent Validation to protect against Platform and PlatformVersion mismatch

PlatformInfo::PlatformInfo(
	Platform family,
	PlatformVersion version
)
	: family(family),
	version(version),
	valid(false)
{
	valid = isValidPlatform();
}

bool PlatformInfo::isValidPlatform() const
{
	switch (family)
	{
	case Platform::PC:
		return version == PlatformVersion::None;

	case Platform::PlayStation:
		return version == PlatformVersion::PS1 ||
			version == PlatformVersion::PS2 ||
			version == PlatformVersion::PS3 ||
			version == PlatformVersion::PS4 ||
			version == PlatformVersion::PS5 ||
			version == PlatformVersion::PSVita ||
			version == PlatformVersion::PSP;

	case Platform::Xbox:
		return version == PlatformVersion::Xbox ||
			version == PlatformVersion::Xbox360 ||
			version == PlatformVersion::XboxOne ||
			version == PlatformVersion::XboxSeries;

	case Platform::Nintendo:
		return version == PlatformVersion::NES ||
			version == PlatformVersion::SNES ||
			version == PlatformVersion::N64 ||
			version == PlatformVersion::GameCube ||
			version == PlatformVersion::Wii ||
			version == PlatformVersion::WiiU ||
			version == PlatformVersion::Switch ||
			version == PlatformVersion::Switch2 ||
			version == PlatformVersion::GameBoy ||
			version == PlatformVersion::GameBoyColor ||
			version == PlatformVersion::GameBoyAdvance ||
			version == PlatformVersion::DS ||
			version == PlatformVersion::ThreeDS;

	case Platform::Sega:
		return version == PlatformVersion::Genesis ||
			version == PlatformVersion::Dreamcast ||
			version == PlatformVersion::GameGear; 

	case Platform::Other:
		return version == PlatformVersion::Other;
	}

	return false;
}

bool PlatformInfo::isValid() const
{
	return valid;
}

Platform PlatformInfo::getFamily() const
{
	return family;
}

PlatformVersion PlatformInfo::getVersion() const
{
	return version;
}

void PlatformInfo::display() const
{
    switch (family)
    {
    case Platform::PC:
        std::cout << "Platform: PC\n";
        break;

    case Platform::PlayStation:
        std::cout << "Platform: PlayStation\n";
        break;

    case Platform::Xbox:
        std::cout << "Platform: Xbox\n";
        break;

    case Platform::Nintendo:
        std::cout << "Platform: Nintendo\n";
        break;

    case Platform::Sega:
        std::cout << "Platform: Sega\n";
        break;

    case Platform::Other:
        std::cout << "Platform: Other\n";
        break;
    }

    switch (version)
    {
    case PlatformVersion::None:
        break;

    case PlatformVersion::PS1:
        std::cout << "Version: PS1\n";
        break;

    case PlatformVersion::PS2:
        std::cout << "Version: PS2\n";
        break;

    case PlatformVersion::PS3:
        std::cout << "Version: PS3\n";
        break;

    case PlatformVersion::PS4:
        std::cout << "Version: PS4\n";
        break;

    case PlatformVersion::PS5:
        std::cout << "Version: PS5\n";
        break;

    case PlatformVersion::Xbox:
        std::cout << "Version: Xbox\n";
        break;

    case PlatformVersion::Xbox360:
        std::cout << "Version: Xbox 360\n";
        break;

    case PlatformVersion::XboxOne:
        std::cout << "Version: Xbox One\n";
        break;

    case PlatformVersion::XboxSeries:
        std::cout << "Version: Xbox Series\n";
        break;

    case PlatformVersion::NES:
        std::cout << "Version: NES\n";
        break;

    case PlatformVersion::SNES:
        std::cout << "Version: SNES\n";
        break;

    case PlatformVersion::N64:
        std::cout << "Version: Nintendo 64\n";
        break;

    case PlatformVersion::GameCube:
        std::cout << "Version: GameCube\n";
        break;

    case PlatformVersion::Wii:
        std::cout << "Version: Wii\n";
        break;

    case PlatformVersion::WiiU:
        std::cout << "Version: Wii U\n";
        break;

    case PlatformVersion::Switch:
        std::cout << "Version: Switch\n";
        break;

    case PlatformVersion::Switch2:
        std::cout << "Version: Switch 2\n";
        break;

    case PlatformVersion::GameBoy:
        std::cout << "Version: Game Boy\n";
        break;

    case PlatformVersion::GameBoyColor:
        std::cout << "Version: Game Boy Color\n";
        break;

    case PlatformVersion::GameBoyAdvance:
        std::cout << "Version: Game Boy Advance\n";
        break;

    case PlatformVersion::DS:
        std::cout << "Version: Nintendo DS\n";
        break;

    case PlatformVersion::ThreeDS:
        std::cout << "Version: Nintendo 3DS\n";
        break;

    case PlatformVersion::Genesis:
        std::cout << "Version: Genesis\n";
        break;

    case PlatformVersion::Dreamcast:
        std::cout << "Version: Dreamcast\n";
        break;

    case PlatformVersion::GameGear:
        std::cout << "Version: Game Gear\n";
        break;

    case PlatformVersion::Other:
        std::cout << "Version: Other\n";
        break;
    }
}