#include "HitBox.h"
namespace IExtreme::Engine::Ugr
{
	HitBox::HitBox()
	{
		this->shape.setFillColor(sf::Color::Transparent);
	}
	HitBox::HitBox(sf::FloatRect prop)
	{
		this->shape.setFillColor(sf::Color::Transparent);
		this->shape.setSize(sf::Vector2f(prop.left, prop.top));
		this->shape.setPosition(prop.width, prop.height);
	}
	HitBox::HitBox(sf::Vector2f size, sf::Vector2f pos)
	{
		this->shape.setSize(size);
		this->shape.setFillColor(sf::Color::Transparent);
		this->shape.setPosition(pos);
	}
	void HitBox::SetHitBoxSize(float x, float y)
	{
		this->shape.setSize({ x, y });
	}
	void HitBox::SetHitBoxThickness(float thickness)
	{
		this->shape.setOutlineThickness(thickness);
	}
	float HitBox::GetHitBoxThickness() const
	{
		return this->shape.getOutlineThickness();
	}
	void HitBox::SetHitBoxDye(sf::Color dye)
	{
		this->shape.setOutlineColor(dye);
	}
	sf::Color HitBox::GetHitBoxDye() const
	{
		return this->shape.getOutlineColor();
	}
	void HitBox::SetPosition(float x, float y)
	{
		this->shape.setPosition(x, y);
	}
	void HitBox::UpdateRelativeTo(sf::Vector2f vec, const float& dt)
	{
		this->shape.move(vec.x * dt, vec.y * dt);
	}
	void HitBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
 		target.draw(shape);
	}
	void HitBox::Move(sf::Vector2f offset)
	{
		this->shape.move(offset);
	}
	void HitBox::Move(float offsetx, float offsety)
	{
		this->shape.move(offsetx, offsety);
	}
	bool HitBox::CheckIntersectionWith(HitBox* box)
	{
		return this->shape.getGlobalBounds().intersects(box->getGlobalBounds());
	}
	sf::FloatRect HitBox::getGlobalBounds() const
	{
		return this->shape.getGlobalBounds();
	}
}