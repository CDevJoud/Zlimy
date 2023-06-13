#pragma once
#include <SFML/Graphics.hpp>
#include "Font.hpp"
class FPSCounter : public sf::Drawable
{
public:
	FPSCounter();

	void Update(const sf::Time& dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	int frameCount;
	int fps;
	sf::Time eTime;
	sf::Text text;
};