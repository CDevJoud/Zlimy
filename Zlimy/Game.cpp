#include "Game.h"

namespace IExtreme::Application::TWarior
{
	void Game::OnUserCreate()
	{
		this->player1->ID = Ugr::ID::GenerateID();
		this->player1->SetProprety(Ugr::Entity::Dynamic);
		this->player1->SetPosition(1920 * 0.5, 300);
		this->player1->GetHitBox()->SetHitBoxThickness(7);
		this->player1->GetHitBox()->SetHitBoxDye(sf::Color::Red);
		this->world.AddEntity(this->player1);

		this->player2->ID = Ugr::ID::GenerateID();
		this->player2->SetPosition(1920 * 0.5, 900);
		this->world.AddEntity(this->player2);
	}
	void Game::OnUserUpdate(const sf::Time& dt)
	{
		this->world.Update(dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (player1->IsCollidingToGround)
			{
				// Apply jump velocity
				player1->SetVelocity(0, -25000);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			this->player1->SetPosition(this->player1->GetPosition().x, 0);
			this->player1->SetVelocity(0, 0);
		}
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
		/*this->player->Clean();
		this->player1->Clean();*/
	}
	Ugr::State::ReturnExitValue Game::ExitValue()
	{
		return this->val;
	}
}