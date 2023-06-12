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
	HitBox::Collider HitBox::CheckIntersectionWith(HitBox* box1)
	{
		Collider tmp;
		auto& e1 = box1;
		auto e2 = this;
		sf::Vector2f boxpos1 = sf::Vector2f(box1->getGlobalBounds().left, box1->getGlobalBounds().top);
		sf::Vector2f boxpos2 = sf::Vector2f(this->getGlobalBounds().left, this->getGlobalBounds().top);

		sf::Vector2f boxsize1 = sf::Vector2f(box1->getGlobalBounds().width, box1->getGlobalBounds().height) * 0.5f;
		sf::Vector2f boxsize2 = sf::Vector2f(this->getGlobalBounds().width, this->getGlobalBounds().height) * 0.5f;

		float dx = boxpos1.x - boxpos2.x;
		float dy = boxpos1.y - boxpos2.y;

		float inx = abs(dx) - (boxsize1.x + boxsize2.x);
		float iny = abs(dy) - (boxsize1.y + boxsize2.y);

		if (inx < 0.0f && iny < 0.0f)
		{
			if (inx > iny)
			{
				if (dx < 0.0f)
				{
					tmp.IsCollidingFromLeft = true;
				}
				else
					tmp.IsCollidingFromLeft = false;

				if (dx > 0.0f)
				{
					tmp.IsCollidingFromRight = true;
				}
				else
					tmp.IsCollidingFromRight = false;
			}
			else
			{
				if (dy > 0.0f)
				{
					tmp.IsCollidingFromTop = true;
				}
				else
					tmp.IsCollidingFromTop = false;

				if (dy < 0.0f)
				{
					tmp.IsCollidingFromBottom = true;
				}
				else
					tmp.IsCollidingFromBottom = false;
			}
		}
		this->collider = tmp;
		return tmp;
	}
	sf::FloatRect HitBox::getGlobalBounds() const
	{
		return this->shape.getGlobalBounds();
	}
}