#include "Game.hpp"

namespace IExtreme::Application::TWarior
{
	void Game::OnUserCreate()
	{
		this->ground->ID = Ugr::ID::GenerateID();
		this->ground->SetPosition(1920 * 0.5, 900);
		this->ground->SetTexture(this->textures["Entity.Block.Ground"]);
		this->ground->SetProprety(Ugr::Entity::Static);
		this->ground->SetSize(1920, 100);
		this->ground->SetOrigin(this->ground->GetSize() * 0.5f);
		this->world.AddEntity(this->ground);

		this->player->AddAnimation(this->ani["Animation.Player.Idle"]);
		this->player->AddAnimation(this->ani["Animation.Player.Run"]);
		this->player->AddAnimation(this->ani["Animation.Player.Jump"]);
		this->player->ID = Ugr::ID::GenerateID();
		this->player->SetProprety(Ugr::Entity::Dynamic);
		this->player->SetPosition(1920 * 0.5, 0);
		this->player->SetSize(512, 256);
		this->player->SetOrigin(this->player->GetSize() * 0.5f);
		this->player->GetHitBox()->SetHitBoxSize(256, 250);
		this->player->GetHitBox()->SetOrigin(128, 250 * 0.5f);
		this->player->GetHitBox()->SetHitBoxThickness(0);
		this->player->GetNameTag()->setFont(*this->fonts["System.Font.First-Job"]);
		this->player->GetNameTag()->setString("Steve");
		this->player->GetNameTag()->setCharacterSize(30);
		this->player->GetNameTag()->setFillColor(sf::Color::Blue);
		this->world.AddEntity(this->player);
	}
	void Game::OnUserUpdate(const sf::Time& dt)
	{
		auto& col = this->player->GetHitBox()->collider;

		/*this->player->PlayAnimation("Animation.Player.Idle");*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && col.IsCollidingFromTop)
		{
			this->player->SetVelocity(0, -600);
			this->player->PlayAnimation("Animation.Player.Jump");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->player->Move(-500 * dt.asSeconds(), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->player->PlayAnimation("Animation.Player.Run");
			this->player->Move(500 * dt.asSeconds(), 0);
		}
		else
			this->player->PlayAnimation("Animation.Player.Idle");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->player->Move(0, -500 * dt.asSeconds());
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !col.IsCollidingFromTop) this->player->Move( 0, 500 * dt.asSeconds());
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