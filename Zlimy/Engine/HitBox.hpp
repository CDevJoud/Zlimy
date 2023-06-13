#pragma once
#include <SFML/Graphics.hpp>
#include "logger.hpp"
namespace IExtreme::Engine::Ugr
{
	class HitBox : public sf::Drawable
	{
		
	public:
		struct Collider
		{
			bool IsCollidingFromTop = false;
			bool IsCollidingFromBottom = false;
			bool IsCollidingFromLeft = false;
			bool IsCollidingFromRight = false;
		};

		HitBox();
		HitBox(sf::FloatRect prop);
		HitBox(sf::Vector2f size, sf::Vector2f pos);

		void SetHitBoxSize(float x, float y);

		void SetHitBoxThickness(float thickness);
		float GetHitBoxThickness() const;
		
		void SetOrigin(sf::Vector2f org);
		void SetOrigin(float x, float y);

		sf::Vector2f GetOrigin() const;

		void SetScale(sf::Vector2f scale);
		void SetScale(float x, float y);

		void SetHitBoxDye(sf::Color dye);
		sf::Color GetHitBoxDye() const;

		void SetPosition(float x, float y);
		void UpdateRelativeTo(sf::Vector2f vec, const float& dt);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void Move(sf::Vector2f offset);
		void Move(float offsetx, float offsety);

		Collider CheckIntersectionWith(HitBox* box);
		sf::FloatRect getGlobalBounds() const;

		Collider collider;
		friend class World;
	private:
		sf::RectangleShape shape;
		float pushStrength = 0.0f;		
	};
}
