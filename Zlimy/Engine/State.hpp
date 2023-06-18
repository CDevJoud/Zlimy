#pragma once
#include "EVar.hpp"
namespace IExtreme::Engine::Ugr
{
	class State
	{
	public:
		State(Evar* var) : target(var->target), window(var->window), fonts(var->fonts), textures(var->textures) {}

		enum class ReturnExitValue
		{
			NONE = 0, EXIT
		};

		virtual void OnUserCreate() = 0;
		virtual void OnUserUpdate(const sf::Time& dt) = 0;
		virtual void Render() = 0;
		virtual void HandleEvent(sf::Event& event) = 0;
		virtual void Clean() = 0;
		virtual ReturnExitValue ExitValue() = 0;

		bool getQuit() const;
	protected:
		sf::RenderTarget* target = nullptr;
		sf::Window* window = nullptr;
		std::map<std::string, sf::Font*> fonts;
		std::map<std::string, sf::Texture*> textures;
		bool quit = false;
	};
}
