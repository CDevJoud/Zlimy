#pragma once
#include <SFML/Graphics.hpp>
#include "Font.hpp"
namespace IExtreme::Engine::Ugr
{
	class FPSCounter : public sf::Drawable
	{
	public:
		FPSCounter() 
		{
			this->frameCount = 0;
			this->fps = 0;
			this->text.setCharacterSize(20);
			this->text.setFillColor(sf::Color::Red);
			this->text.setPosition(10.f, 10.f);
		}
		FPSCounter(sf::Font* font);

		void Update();
		void SetFont(sf::Font* font);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		int frameCount;
		int fps;
		sf::Clock eTime;
		sf::Text text;
		
	};
}