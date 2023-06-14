#pragma once
#include <SFML/Graphics.hpp>
struct Evar
{
	sf::RenderTarget* target = nullptr;
	sf::Window* window = nullptr;
	std::map<std::string, sf::Font*> fonts;
};
