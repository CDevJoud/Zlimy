#pragma once
#include <box2d/box2d.h>
#include "Entity.hpp"
#include "logger.hpp"
namespace IExtreme::Engine::Ugr
{
	class World : public sf::Drawable
	{
	public:
		World();
		~World();

		void Update(const sf::Time& dt);
		void AddEntity(Box2DEntity* entity);
		void AddEntity(Entity* entity);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void Clean();
	private:
		b2World* world = new b2World(b2Vec2(0, 500.82f));
		std::map<int, std::unique_ptr<Box2DEntity>> bentities;
		std::map<int, std::unique_ptr<Entity>> entities;
	};
}
