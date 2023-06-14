#include "FPSCounter.hpp"

namespace IExtreme::Engine::Ugr
{
	FPSCounter::FPSCounter(sf::Font* font)
	{
		this->frameCount = 0;
		this->fps = 0;
		this->text.setFont(*font);
		this->text.setCharacterSize(20);
		this->text.setFillColor(sf::Color::Red);
		this->text.setPosition(10.f, 10.f);
	}

	void FPSCounter::Update()
	{
		++frameCount;
		if (eTime.getElapsedTime().asSeconds() >= 1.f)
		{
			fps = frameCount;
			frameCount = 0;
			eTime.restart();
		}
		this->text.setString("FPS: " + std::to_string(this->fps));
	}

	void FPSCounter::SetFont(sf::Font* font)
	{
		this->text.setFont(*font);
	}

	void FPSCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->text);
	}
}