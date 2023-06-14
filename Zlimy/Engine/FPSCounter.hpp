#pragma once
#include <SFML/Graphics.hpp>
#include "Font.hpp"
namespace IExtreme::Engine::Ugr
{
	class FPSCounter : public sf::Drawable
	{
	public:
		FPSCounter();

		void Update();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		int frameCount;
		int fps;
		sf::Clock eTime;
		sf::Text text;
	};
}
