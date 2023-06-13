#include "Game.h"

namespace IExtreme::Application::TWarior
{
	void Game::OnUserCreate()
	{
		this->player2->ID = Ugr::ID::GenerateID();
		this->player2->SetPosition(1920 * 0.5, 900);
		this->player2->LoadTexture("Ground.png");
		this->player2->SetProprety(Ugr::Entity::Static);
		this->player2->SetSize(1920, 100);
		this->player2->SetOrigin(this->player2->GetSize() * 0.5f);
		this->world.AddEntity(this->player2);


		Ugr::Entity::Animation* animation = new Ugr::Entity::Animation();
		animation->texture = new sf::Texture();
		animation->texture->loadFromFile("Assets/64x128_Idle_Free.png");
		animation->rect = sf::IntRect(0, 0, 64 * 7, 128 * 3);
		animation->frames = 7;
		animation->coolDown = 0.05f;
		this->player1->AddAnimation("Player-Running", animation, true);
		this->player1->ID = Ugr::ID::GenerateID();
		this->player1->SetProprety(Ugr::Entity::Dynamic);
		this->player1->SetPosition(1920 * 0.5, 0);
		this->player1->SetSize(64*7, 128*4);
		this->player1->SetOrigin(this->player1->GetSize() * 0.5f);
		this->player1->GetHitBox()->SetHitBoxSize(256, 380);
		this->player1->GetHitBox()->SetOrigin(128, 380 * 0.5f);
		this->player1->GetHitBox()->SetHitBoxThickness(0);
		this->world.AddEntity(this->player1);
	}
	void Game::OnUserUpdate(const sf::Time& dt)
	{
		//this->player1->PlayAnimation("Player-Running");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
 			this->player1->SetVelocity(0, -300);

		auto& col = this->player1->GetHitBox()->collider;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->player1->Move(-500 * dt.asSeconds(), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->player1->Move( 500 * dt.asSeconds(), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->player1->Move(0, -500 * dt.asSeconds());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !col.IsCollidingFromTop) this->player1->Move( 0, 500 * dt.asSeconds());
		this->world.Update(dt);
	}
	void Game::Render()
	{
		this->target->draw(this->world);
	}
	void Game::HandleEvent(sf::Event& event)
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			this->quit = true;
			this->val = Ugr::State::ReturnExitValue::EXIT;
		}
	}
	void Game::Clean()
	{
		this->world.Clean();
	}
	Ugr::State::ReturnExitValue Game::ExitValue()
	{
		return this->val;
	}
}