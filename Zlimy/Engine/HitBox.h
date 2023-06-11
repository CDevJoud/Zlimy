#pragma once
#include <SFML/Graphics.hpp>
namespace IExtreme::Engine::Ugr
{
	class HitBox : public sf::Drawable
	{
	public:
		HitBox();
		HitBox(sf::FloatRect prop);
		HitBox(sf::Vector2f size, sf::Vector2f pos);

		void SetHitBoxSize(float x, float y);

		void SetHitBoxThickness(float thickness);
		float GetHitBoxThickness() const;

		void SetHitBoxDye(sf::Color dye);
		sf::Color GetHitBoxDye() const;

		void SetPosition(float x, float y);
		void UpdateRelativeTo(sf::Vector2f vec, const float& dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void Move(sf::Vector2f offset);
		void Move(float offsetx, float offsety);

		bool CheckIntersectionWith(HitBox* box);
		sf::FloatRect getGlobalBounds() const;
	private:
		sf::RectangleShape shape;
	};
}