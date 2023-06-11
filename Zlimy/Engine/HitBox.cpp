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
	bool HitBox::CheckIntersectionWith(HitBox* box, float pushStrength, const sf::Time& dt)
	{
		bool intersection = this->shape.getGlobalBounds().intersects(box->getGlobalBounds());

		sf::Vector2f tpos = this->shape.getPosition();
		sf::Vector2f thalfsize = this->shape.getSize() * 0.5f;
		sf::Vector2f opos = sf::Vector2f(box->getGlobalBounds().left, box->getGlobalBounds().top);
		sf::Vector2f ohalfsize = sf::Vector2f(box->getGlobalBounds().width, box->getGlobalBounds().height) * 0.5f;

		float dx = opos.x - tpos.x;
		float dy = opos.y - tpos.y;
		float inx = abs(dx) - (ohalfsize.x + thalfsize.x);
		float iny = abs(dy) - (ohalfsize.y + thalfsize.y);

		if (inx < 0.0f && iny < 0.0f)
		{
			if (inx > iny)
			{
				if (dx > 0.0f)
				{
					this->Move(inx * (1.0f - pushStrength), 0.0f);
					box->Move(-inx * pushStrength, 0.0f);
					this->IsCollidingFromLeft = true;
				}
				else
					this->IsCollidingFromLeft = false;
				if (dx < 0.0f)
				{
					this->Move(-inx * (1.0f - pushStrength), 0.0f);
					box->Move(inx * pushStrength, 0.0f);
					this->IsCollidingFromRight = true;
				}
				else
					this->IsCollidingFromRight = false;
			}
			else
			{
				if (dy > 0.0f)
				{
					Logger::Debug(std::to_string(pushStrength).c_str());
					/*this->Move(0.0f, iny * (1.0f - this->pushStrength));
					box->Move(0.0f, -iny * box->pushStrength);*/
					this->Move(0.0f, iny * 0.5);
					box->Move(0.0f, -iny * 0.5);
					this->IsCollidingFromTop = true;
				}
				else
 					this->IsCollidingFromTop = false;
				if(dy < 0.0f)
				{
					this->Move(0.0f, -iny * (1.0f - pushStrength));
					box->Move(0.0f, iny * pushStrength);
					this->IsCollidingFromBottom = true;
				}
				else
					this->IsCollidingFromBottom = false;
					
			}
		}


		Logger::Info(std::to_string(pushStrength).c_str());
		Logger::Error(std::to_string(box->pushStrength).c_str());
		return intersection;
	}
	sf::FloatRect HitBox::getGlobalBounds() const
	{
		return this->shape.getGlobalBounds();
	}
}