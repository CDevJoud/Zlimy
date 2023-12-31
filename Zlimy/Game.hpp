#pragma once
#include "Engine/State.hpp"
#include "Engine/Entity.hpp"
#include "Engine/World.hpp"
#include "Engine/Utility.hpp"

namespace IExtreme::Application::TWarior
{
	using namespace Engine;
	class Game : public Ugr::State
	{
	public:
		Game(Evar* var) : State(var) {}

		void OnUserCreate();
		void OnUserUpdate(const sf::Time& dt);
		void Render();
		void HandleEvent(sf::Event& event);
		void Clean();
		Ugr::State::ReturnExitValue ExitValue();
	private:
		Ugr::State::ReturnExitValue val;
		Ugr::Entity* player = new Ugr::Entity();
		Ugr::Entity* ground = new Ugr::Entity();
		
		Ugr::World world;
	};
}
