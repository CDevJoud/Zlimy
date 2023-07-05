#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
struct Evar
{
	sf::RenderTarget* target = nullptr;
	sf::Window* window = nullptr;
	std::map<std::string, sf::Font*> fonts;
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, IExtreme::Engine::Ugr::Entity::Animation*> animations;
};
