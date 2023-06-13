#include "FPSCounter.hpp"

FPSCounter::FPSCounter()
{
	this->frameCount = 0;
	this->fps = 0;
	this->eTime = sf::Time::Zero;
	this->text.setFont(sysDefaultFont);
	this->text.setCharacterSize(20);
	this->text.setFillColor(sf::Color::Red);
	this->text.setPosition(10.f, 10.f);
}

void FPSCounter::Update(const sf::Time& dt)
{
	this->eTime += dt;
	this->frameCount++;
	if (this->eTime >= sf::seconds(1.0f))
	{
		this->fps = this->frameCount;
		this->frameCount = 0;
		this->eTime -= sf::seconds(1.0f);
		this->text.setString("FPS: " + std::to_string(this->fps));
	}
}

void FPSCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->text);
}
