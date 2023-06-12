#include "Engine.h"
//SFML_DEFINE_DISCRETE_GPU_PREFERENCE
namespace IExtreme::Engine::Ugr
{
	Engine::Engine()
	{
		Logger::Init();
		Logger::Logging(true);
		Logger::SetPriority(Logger::LogPriority::Trace);

		sf::ContextSettings s;
		s.antialiasingLevel = 8;
		s.attributeFlags = sf::ContextSettings::Attribute::Debug;

		this->create(sf::VideoMode::getDesktopMode(), "Warior", sf::Style::Fullscreen, s);
		
		std::string out = "Init Warior Game With " + std::to_string(sf::VideoMode::getDesktopMode().width) + "x" + std::to_string(sf::VideoMode::getDesktopMode().height) + "With FullScreen Mode";
		Logger::Info(out.c_str());
		out = "Setting Up Game Quality\nAnti Aliasing: 8\nDebug Mode: True\nFrame/s Set to: 60";

		Logger::Debug(out.c_str());

		Logger::Info("Setting Up Resource Files");
		this->evar->target = this;
		this->evar->window = this;
		Logger::Info("Done!");

		Logger::Info("Init Game States");
		this->states.push(new Application::TWarior::Game(this->evar));
		Logger::Info("Done!");
		this->setFramerateLimit(0);
	}
	void Engine::run()
	{
		Logger::Debug("Igniting The Engine !");
		this->OnUserCreate();
		Logger::Info("Done!");
		this->OnUserUpdate();
	}
	void Engine::OnUserCreate()
	{
		Logger::Debug("Calling \"OnUserCreate()\" Function");
		if (!this->states.empty())
			this->states.top()->OnUserCreate();
	}
	void Engine::OnUserUpdate()
	{
		while (this->isOpen())
		{
			if (!this->states.empty())
			{
				if (this->states.top()->getQuit())
				{
					this->states.top()->Clean();

					this->ManageStates(this->states.top()->ExitValue());
				}
			}
			else
				this->close();
			this->HandleEvent();
			this->Update();
			this->Render();
		}
	}
	void Engine::Update()
	{
		if (!this->states.empty())
			this->states.top()->OnUserUpdate(this->restart());
	}
	void Engine::Render()
	{
		this->clear();
		if (!this->states.empty())
			this->states.top()->Render();
		this->display();
	}
	void Engine::HandleEvent()
	{
		sf::Event event{};
		while (this->pollEvent(event))
		{
			/*if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				this->close();*/
			if (!this->states.empty())
				this->states.top()->HandleEvent(event);
		}
	}
	void Engine::ManageStates(State::ReturnExitValue v)
	{
		switch (v)
		{
		case State::ReturnExitValue::NONE:
			break;

		case State::ReturnExitValue::EXIT:
			Logger::Debug("Last Game State asked For Exiting! Engine responded with no issues"),
			delete this->states.top();
			this->states.pop();
			Logger::Info("There is no more Game states on the stack! quiting...");
			break;
		default:
			break;
		}
	}
}