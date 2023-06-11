#include "Engine/Engine.h"

using namespace IExtreme::Engine;

int main()
{
	Ugr::Engine e; e.run(); return 0;
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "");
	sf::Event event{};
	sf::RectangleShape shape(sf::Vector2f(100, 100));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(1920 * 0.5 - 50, 0);

	sf::RectangleShape ground(sf::Vector2f(900, 100));
	ground.setFillColor(sf::Color::Green);
	ground.setPosition(1920 * 0.5 - 900 * 0.5, 900);
	sf::Clock clock;
	float dt = 0.0f;
	sf::Vector2f velocity;
	while (window.isOpen())
	{
		std::cout << shape.getGlobalBounds().width << std::endl;
		dt = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		velocity.y += 1000.82 * dt;
		bool collision = shape.getGlobalBounds().intersects(ground.getGlobalBounds());
		if (collision)
			velocity.y = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && collision)
			velocity.y = -700;
		shape.move(velocity * dt);

		window.clear();
		window.draw(shape);
		window.draw(ground);
		window.display();
	}
	return EXIT_SUCCESS;
}