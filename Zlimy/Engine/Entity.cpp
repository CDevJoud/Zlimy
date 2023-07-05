#include "Entity.hpp"

namespace IExtreme::Engine::Ugr
{
	Box2DEntity::Box2DEntity()
	{
		this->texture->loadFromMemory(this->NullData, NULLSIZE);
		this->sprite.setTexture(*texture);
		sf::Vector2f size = sf::Vector2f(texture->getSize());
		HitBox box(sf::FloatRect(size.x, size.y, 0, 0));
		box.SetHitBoxDye(sf::Color::Yellow);
		box.SetHitBoxThickness(2);
		this->hitBoxes.insert(std::pair<std::string, HitBox>("MainHitBox", box));
	}
	Box2DEntity::~Box2DEntity()
	{
		delete this->texture;
		this->hitBoxes.clear();
	}
	void Box2DEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->sprite);
		for (auto& i : this->hitBoxes)
			target.draw(i.second);
	}
	void Box2DEntity::Update(const sf::Time& dt)
	{
		b2Vec2 bodyPosition = body->GetPosition();
		sprite.setPosition(bodyPosition.x, bodyPosition.y);
		float bodyAngle = body->GetAngle();
		sprite.setRotation(bodyAngle * 180.0f / b2_pi);

		this->UpdateTransformation();
		for (auto& i : this->hitBoxes)
			i.second.SetPosition(this->sprite.getPosition().x, this->sprite.getPosition().y);
		this->dt = dt.asSeconds();
	}
	void Box2DEntity::SetPosition(float x, float y)
	{
		this->sprite.setPosition(x, y);
	}
	sf::Vector2f Box2DEntity::GetPosition() const
	{
		return this->sprite.getPosition();
	}
	void Box2DEntity::AddHitBox(std::string IDHitBox, HitBox& box)
	{
		this->hitBoxes.insert(std::pair<std::string, HitBox>(IDHitBox, box));
	}
	HitBox& Box2DEntity::GetHitBox(std::string ID)
	{
		return this->hitBoxes[ID];
	}
	b2Body* Box2DEntity::GetBody()
	{
		return this->body;
	}
	void Box2DEntity::SetBody(b2Body* body)
	{
		this->body = body;
	}
	sf::Vector2f Box2DEntity::GetSize() const
	{
		return sf::Vector2f(this->texture->getSize());
	}
	void Box2DEntity::Move(float x, float y)
	{
		this->sprite.move(x, y);
		for (auto& i : this->hitBoxes)
			i.second.UpdateRelativeTo({ x, y }, this->dt);
	}
	void Box2DEntity::UpdateTransformation()
	{
		//this->sprite.setPosition(this->getPosition());
		//this->sprite.setRotation(this->getRotation());
		this->sprite.setScale(this->getScale());
		this->sprite.setOrigin(this->getOrigin());
	}


	Entity::Entity()
	{
		Logger::Debug("Setting Up An Entity!");
		this->texture = new sf::Texture();
		Logger::Warn("There is no available texture Applying a default one!");
		Logger::Debug("Setting Up A default texture to Insure if there is no texture is loaded!");
		this->texture->loadFromMemory(this->NullData, NULLSIZE);
		Logger::Debug("Applying Texture To Sprite");
		this->sprite.setTexture(this->texture);
		Logger::Debug("Setting Up HitBox");
		sf::Vector2u size = this->texture->getSize();
		this->hitBox.SetHitBoxSize(size.x, size.y);
		this->hitBox.SetHitBoxThickness(3);
		this->hitBox.SetHitBoxDye(sf::Color::Yellow);
		this->sprite.setSize(sf::Vector2f(size));
		Logger::Info("Done!");
	}
	Entity::~Entity()
	{
		
	}
	void Entity::Clean()
	{
		std::string str = "Deleting Texture of An Entity with ID: " + std::to_string(this->ID);
		Logger::Debug(str.c_str());
		delete this->texture;
	}
	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->sprite);
		target.draw(this->hitBox);
		target.draw(this->nametag);
	}
	void Entity::SetTexture(sf::Texture* texture)
	{
		this->sprite.setTexture(texture);
	}
	bool Entity::LoadTexture(std::string file)
	{
		std::string str = "Loading File: " + file;
		Logger::Info(str.c_str());
		if (!this->texture->loadFromFile(file))
		{
			Logger::Error("File Could not be load!\n\tmake sure you typed the directory correct or the name of the file correct!");
			return false;
		}
		this->sprite.setTexture(this->texture);
		sf::Vector2u size = this->texture->getSize();
		this->sprite.setSize(sf::Vector2f(size));
		this->sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		this->hitBox.SetHitBoxSize(size.x, size.y);
		this->hitBox.SetHitBoxThickness(3);

		this->hitBox.SetHitBoxDye(sf::Color::Yellow);
		return true;
	}

	void Entity::AddAnimation(Animation* ani, bool a)
	{
		std::string key = ani->aniName;
		this->animations.insert(std::pair<std::string, Animation>(key, *ani));
 		if (a)
		{
			auto& texture = *this->animations[key].texture;
			this->sprite.setTexture(&texture);
			this->sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
		}
	}

	void Entity::ResetAnimation(std::string aniName)
	{
		this->animations[aniName].rect.left = 0;
		this->sprite.setTextureRect(this->animations[aniName].rect);
	}

	void Entity::PlayAnimation(std::string aniName)
	{

		if (this->animations.count(aniName))
		{
			auto& ani = this->animations[aniName];
			sf::Texture* texture = ani.texture;
			this->sprite.setTexture(texture);
			if (this->coolDown.getElapsedTime().asSeconds() > ani.coolDown)
			{
				
				/*if (ani.rect.left != ani.rect.width * ani.amountFrames)
					ani.rect.left += ani.rect.width;
				else
					ani.rect.left = 0;*/
				if (ani.currentFrame >= ani.amountFrames)
					ani.currentFrame = 0;

				this->coolDown.restart();
  				this->sprite.setTextureRect(ani.frames[ani.currentFrame]);
				ani.currentFrame++;
			}
		}
	}

	void Entity::SetSize(sf::Vector2f size)
	{
		this->sprite.setSize(size);
		this->hitBox.SetHitBoxSize(size.x, size.y);
	}
	void Entity::SetSize(float x, float y)
	{
		this->sprite.setSize({ x, y });
		this->hitBox.SetHitBoxSize(x, y);
	}
	void Entity::SetPosition(sf::Vector2f pos)
	{
		
		this->hitBox.SetPosition(pos.x, pos.y);
		this->sprite.setPosition(pos);
	}
	void Entity::SetPosition(float x, float y)
	{
		this->hitBox.SetPosition(x, y);
		this->sprite.setPosition(x, y);
	}
	void Entity::SetOrigin(sf::Vector2f org)
	{
		this->hitBox.SetOrigin(org);
		this->sprite.setOrigin(org);
	}
	void Entity::SetOrigin(float x, float y)
	{
		this->hitBox.SetOrigin(x, y);
		this->sprite.setOrigin(x, y);
	}
	void Entity::SetScale(sf::Vector2f scale)
	{
		this->hitBox.SetScale(scale);
		this->sprite.setScale(scale);
	}
	void Entity::SetScale(float x, float y)
	{
		this->hitBox.SetScale(x, y);
		this->sprite.setScale(x, y);
	}
	void Entity::SetRotation(float x)
	{
		this->sprite.setRotation(x);
	}
	void Entity::SetProprety(Proprety prop)
	{
		this->prop = prop;
	}
	void Entity::SetVelocity(sf::Vector2f vel)
	{
		//We set the requested velocity and then on Update function we register it
		this->reqvelocity = vel;
	}
	void Entity::SetVelocity(float x, float y)
	{
		//We set the requested velocity and then on Update function we register it
		this->reqvelocity = { x, y };
	}
	Entity::Proprety Entity::GetProprety() const
	{
		return this->prop;
	}
	sf::Vector2f Entity::GetPosition() const
	{
		return this->sprite.getPosition();
	}
	sf::Vector2f Entity::GetOrigin() const
	{
		return this->sprite.getOrigin();
	}
	sf::Vector2f Entity::GetScale() const
	{
		return this->sprite.getScale();
	}
	float Entity::GetRotation() const
	{
		return this->sprite.getRotation();
	}
	void Entity::Move(sf::Vector2f offset)
	{
		this->hitBox.Move(offset);
		this->sprite.move(offset);
	}
	void Entity::Move(float offsetx, float offsety)
	{
		this->hitBox.Move(offsetx, offsety);
		this->sprite.move(offsetx, offsety);
	}
	void Entity::Rotate(float rotation)
	{
		this->sprite.rotate(rotation);
	}
	void Entity::Scale(sf::Vector2f scale)
	{
		this->sprite.scale(scale);
	}
	void Entity::Scale(float x, float y)
	{
		this->sprite.setScale(x, y);
	}
	void Entity::Update(const sf::Time& dt)
	{
		sf::FloatRect posrect = this->sprite.getGlobalBounds();
		this->nametag->setPosition(posrect.left + posrect.width * 0.5f, posrect.top);

		sf::FloatRect orgrect = this->nametag->getGlobalBounds();
		this->nametag->setOrigin(orgrect.width * 0.5f, orgrect.height * 0.5f);

		this->velocity.y += 500.82 * dt.asSeconds();
		sf::Vector2f pos = this->GetPosition();

		if (hitBox.collider.IsCollidingFromTop)
			velocity.y = 0;

		if (reqvelocity.x != 0 || reqvelocity.y != 0)
			velocity = reqvelocity;

		pos += velocity * dt.asSeconds();

		this->SetPosition(pos);
		reqvelocity = sf::Vector2f(0, 0);
	}
	HitBox* Entity::GetHitBox()
	{
		return &this->hitBox;
	}
	sf::Vector2f Entity::GetSize() const
	{
		return this->sprite.getSize();
	}
	sf::Vector2f Entity::GetVelocity() const
	{
		return this->velocity;
	}
	NameTag& Entity::GetNameTag()
	{
		return this->nametag;
	}
}