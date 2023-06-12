#include "Game.h"

namespace IExtreme::Application::TWarior
{
	void Game::OnUserCreate()
	{
		this->player1->ID = Ugr::ID::GenerateID();
		this->player1->SetProprety(Ugr::Entity::Dynamic);
		this->player1->SetPosition(1920 * 0.5, 0);
		this->world.AddEntity(this->player1);

		this->player2->ID = Ugr::ID::GenerateID();
		this->player2->SetPosition(1920 * 0.5, 900);
		this->world.AddEntity(this->player2);
	}
	void Game::OnUserUpdate(const sf::Time& dt)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
			this->player1->SetVelocity(0, -500);
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
		/*this->player->Clean();
		this->player1->Clean();*/
	}
	Ugr::State::ReturnExitValue Game::ExitValue()
	{
		return this->val;
	}
}