#include "Engine.hpp"
//SFML_DEFINE_DISCRETE_GPU_PREFERENCE
namespace IExtreme::Engine::Ugr
{
	Engine::Engine()
	{
		

		Logger::Init();
		Logger::Logging(true);
		Logger::SetPriority(Logger::LogPriority::Trace);

		Ugr::CompileRecourceFile("data.json", "data", ".ugr.tablet");

		this->ParseJson();

		sf::ContextSettings s;
		s.antialiasingLevel = 8;
		s.attributeFlags = sf::ContextSettings::Attribute::Debug;
		sf::err().clear(std::ios::failbit);

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
		this->fps.SetFont(this->evar->fonts["System.Font.Default"]);
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
		this->fps.Update();
	}
	void Engine::Render()
	{
		this->clear();
		if (!this->states.empty())
			this->states.top()->Render();
		this->draw(this->fps);
		this->display();
	}
	void Engine::HandleEvent()
	{
		sf::Event event{};
		while (this->pollEvent(event))
		{
			if (!this->states.empty())
				this->states.top()->HandleEvent(event);
		}
	}
	void Engine::ParseJson()
	{
		std::ifstream file("data.ugr.tablet", std::ios::binary);
		if (file.is_open())
		{
			std::vector<sf::Uint8> buffer;
			std::vector<sf::Uint8> UgrTabdata(std::istreambuf_iterator<char>(file), {});

			Decompress(UgrTabdata, buffer);
			nlohmann::json data = nlohmann::json::parse(buffer);
			if (data["Version"] != "1.0.0")
			{
				Logger::Error("Unsupportable Resource File Version");
				exit(-100);
			}
			else
			{
				if (data["Textures"].is_object())
				{
					for (auto& textelements : data["Textures"].items())
					{
						if (data["Textures"][textelements.key()].is_string())
						{
							sf::Texture* tmp = new sf::Texture();
							std::string path = data["Textures"][textelements.key()];
							std::string key  = textelements.key();
							tmp->loadFromFile(path);
							this->evar->textures.insert(std::pair<std::string, sf::Texture*>(key, tmp));
						}
					}
				}
				if (data["Fonts"].is_object())
				{
					for (auto& fontselements : data["Fonts"].items())
					{
						if (data["Fonts"][fontselements.key()].is_string())
						{
							sf::Font* tmp = new sf::Font();
							std::string path = data["Fonts"][fontselements.key()];
							std::string key  = fontselements.key();
							tmp->loadFromFile(path);
							this->evar->fonts.insert(std::pair < std::string, sf::Font*>(key, tmp));
						}
					}
				}
			}
			file.close();
		}
		else
		{
			Logger::Fatal("Ugarit Engine could not find the resource data file: data.ugr.tablet.\n\t The file went missing! Terminating immediately!");
			exit(-1);
			file.close();
		}
	}
	void Engine::Clean()
	{
		this->evar->fonts.clear();
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