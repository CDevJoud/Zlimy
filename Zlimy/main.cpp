#include <SFML/Graphics.hpp>
#include "Engine/Engine.h"

using namespace IExtreme::Engine;

struct
{
	sf::RenderWindow window;
	sf::RectangleShape player;
	sf::RectangleShape ground;
	sf::Vector2f velocity;
	sf::Clock clock;
}res;

struct Collider
{
	bool IsCollidingFromTop = false;
	bool IsCollidingFromBottom = false;
	bool IsCollidingFromLeft = false;
	bool IsCollidingFromRight = false;
};

void InitGame();
void StartGame();
void HandleEvent();
void Update();
void Render();
Collider CheckCollider(sf::RectangleShape& e1, sf::RectangleShape& e2, float push);

int main()
{
	Ugr::Engine e; e.run(); return 0;
	InitGame();
	StartGame();
}

void InitGame()
{
	res.window.create(sf::VideoMode::getDesktopMode(), "");
	res.player.setSize(sf::Vector2f(100, 100));
	res.player.setFillColor(sf::Color::Red);
	res.player.setOrigin(50, 50);
	res.player.setPosition(1920 * 0.5, 0);

	res.ground.setSize(sf::Vector2f(900, 100));
	res.ground.setFillColor(sf::Color::Green);
	res.ground.setOrigin(res.ground.getSize() * 0.5f);
	res.ground.setPosition(1920 * 0.5, 900);
}

void StartGame()
{
	while (res.window.isOpen())
	{
		HandleEvent();
		Update();
		Render();
	}
}

void HandleEvent()
{
	sf::Event event{};
	while (res.window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			res.window.close();
	}
}

void Update()
{
	float dt = res.clock.restart().asSeconds();

	Collider col = CheckCollider(res.ground, res.player, 1.f);
	sf::Vector2f pos = res.player.getPosition();

	res.velocity.y += 500.82f * dt;

	if (col.IsCollidingFromTop)
		res.velocity.y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		res.velocity.y = -500;

	pos += res.velocity * dt;
	res.player.setPosition(pos);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !col.IsCollidingFromLeft) res.player.move(-500 * dt, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !col.IsCollidingFromRight) res.player.move( 500 * dt, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !col.IsCollidingFromBottom) res.player.move(0.0f, -500 * dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !col.IsCollidingFromTop) res.player.move( 0.0f, 500 * dt);
}

void Render()
{
	res.window.clear();
	res.window.draw(res.ground);
	res.window.draw(res.player);
	res.window.display();
}

Collider CheckCollider(sf::RectangleShape& e1, sf::RectangleShape& e2, float push)
{
	Collider tmp;
	sf::Vector2f epos1 = e1.getPosition();
	sf::Vector2f epos2 = e2.getPosition();

	sf::Vector2f esize1 = e1.getSize() * 0.5f;
	sf::Vector2f esize2 = e2.getSize() * 0.5f;

	float dx = epos1.x - epos2.x;
	float dy = epos1.y - epos2.y;

	float inx = abs(dx) - (esize2.x + esize1.x);
	float iny = abs(dy) - (esize2.y + esize1.y);

	if (inx < 0.0f && iny < 0.0f)
	{
		if (inx > iny)
		{
			if (dx < 0.0f)
			{
				//Left
				e1.move(inx * (1.0f - push), 0.0f);
				e2.move(-inx * (1.0f - push), 0.0f);
				tmp.IsCollidingFromLeft = true;
			}
			else
				tmp.IsCollidingFromLeft = false;
			if (dx > 0.0f)
			{
				//right
				e1.move(-inx * (1.0f - push), 0.0f);
				e2.move(inx * (1.0f - push), 0.0f);
				tmp.IsCollidingFromRight = true;
			}
			else
				tmp.IsCollidingFromRight = false;
		}
		else
		{
			if (dy > 0.0f)
			{
				//top
				e1.move(0.0f, -iny * (1.0f - push));
				e2.move(0.0f, iny * (1.0f - push));
				tmp.IsCollidingFromTop = true;
			}
			else
				tmp.IsCollidingFromTop = false;
			
			if (dy < 0.0f)
			{
				//bottom
				e1.move(0.0f, iny * (1.0f - push));
				e2.move(0.0f, -iny * (1.0f - push));
				tmp.IsCollidingFromBottom = true;
			}
			else
				tmp.IsCollidingFromBottom = false;
		}
	}
	return tmp;
}