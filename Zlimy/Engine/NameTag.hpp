#pragma once
#include <SFML/Graphics.hpp>

namespace IExtreme::Engine::Ugr
{
	class NameTag : public sf::Drawable 
	{
	public:
		NameTag();
		NameTag(sf::Font* font);

		sf::Text* operator->() const;

		void SetFont(sf::Font* font);
		void SetTitle(std::string title);
		void Clean();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		sf::Text* title;
	};
}