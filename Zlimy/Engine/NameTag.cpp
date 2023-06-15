#include "NameTag.hpp"

namespace IExtreme::Engine::Ugr
{
	NameTag::NameTag()
	{
		this->title = new sf::Text;
	}
	NameTag::NameTag(sf::Font* font)
	{
		this->title->setFont(*font);
	}
	sf::Text* NameTag::operator->() const
	{
		return this->title;
	}
	void NameTag::SetFont(sf::Font* font)
	{
		this->title->setFont(*font);
	}
	void NameTag::SetTitle(std::string title)
	{
		this->title->setString(title);
	}
	void NameTag::Clean()
	{
		delete this->title;
	}
	void NameTag::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*this->title);
	}
}

