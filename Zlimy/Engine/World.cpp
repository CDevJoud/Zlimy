#include "World.h"
namespace IExtreme::Engine::Ugr
{
	World::World()
	{

	}
	World::~World()
	{
        delete this->world;
        for (auto& i : this->bentities)
            delete i.second.get();
        this->bentities.clear();
	}
    void World::Update(const sf::Time& dt)
    {
        world->Step(dt.asSeconds(), 80, 30);
        for (auto& i : this->bentities)
            i.second->Update(dt);

        for (auto& e : this->entities)
        {
            for (auto& target : this->entities)
            {
                if (e.second->ID != target.second->ID)
                {
                    if (target.second->GetHitBox()->CheckIntersectionWith(e.second->GetHitBox()))
                    {
                        target.second->pVelocity.y = 0;
                        target.second->UpdatePollGravitation = false;
                        target.second->IsCollidingToGround = true;
                    }
                    else
                    {
                        target.second->UpdatePollGravitation = true;
                        target.second->IsCollidingToGround = false;
                    }
                    target.second->Update(dt);
                }
            }
        }
    }
    void World::AddEntity(Box2DEntity* entity)
	{
        // Create a Box2D body
        b2BodyDef bodyDef;
        bodyDef.type = b2BodyType(entity->prop);
        bodyDef.position.Set(entity->GetPosition().x, entity->GetPosition().y);
        b2Body* body = entity->GetBody();
        body = world->CreateBody(&bodyDef);

        // Create a Box2D shape
        b2PolygonShape shape;
        shape.SetAsBox(entity->GetSize().x / 2.0f, entity->GetSize().y / 2.0f);

        // Create a Box2D fixture
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);

        entity->SetBody(body);
        this->bentities.insert(std::pair<int, std::unique_ptr<Box2DEntity>>(entity->ID, std::move(entity)));
	}
    void World::AddEntity(Entity* entity)
    {
        if (!entity->ID)
        {
            std::string outstr = "You didn't specify the ID for The current Entity! ";
            Logger::Fatal(outstr.c_str());
            assert(entity->ID && outstr.c_str());
        }
        this->entities.insert(std::pair<int, std::unique_ptr<Entity>>(entity->ID, entity));
    }
    void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& i : this->bentities)
            target.draw(*i.second.get());

        for (auto& i : this->entities)
            target.draw(*i.second.get());
    }
}