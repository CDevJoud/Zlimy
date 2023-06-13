#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include <stack>
#include "Utility.hpp"
#include "logger.hpp"
#include "..\Game.hpp"
#include "SFML/GpuPreference.hpp"
#include "SFML/System/Err.hpp"

#define NULLSIZE 459
namespace IExtreme::Engine::Ugr
{
	class Engine : private sf::RenderWindow, private sf::Clock
	{
	public:
		Engine();

		void run();
	private:
		void OnUserCreate();
		void OnUserUpdate();

		void Update();
		void Render();
		void HandleEvent();

		void ManageStates(State::ReturnExitValue v);
		std::stack<State*> states;

		Evar* evar = new Evar();

		
	};
}

