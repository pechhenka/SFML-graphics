#include <SFML/Graphics.hpp>
#include "ToolBox.hpp"
#include "Global.hpp"
#include "Ball.hpp"
#include <iostream>
#include <vector>

// 1 pixel = 1 meter

int main()
{
	using namespace sf;

	ToolBox::initRandomGeneration();

	ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	RenderWindow window(VideoMode::getFullscreenModes()[0], "Balls", Style::Fullscreen, settings);
	window.setVerticalSyncEnabled(true);
	Global::windowSize = Vector2f(window.getSize());

	std::vector<Ball> balls;
	for (int i = 0; i < 50; i++)
		balls.push_back(ToolBox::randBall(Global::windowSize));

	
	sf::Text fps;
	sf::Font font;
	if (!font.loadFromFile("Arial.ttf"))
		std::cout << "failed load font" << std::endl;
	fps.setFont(font);
	fps.setCharacterSize(36);
	fps.setFillColor(Color::Red);

	sf::Clock clock;
	while (window.isOpen())
	{
		Global::deltaTime = clock.restart();

		fps.setString(std::to_string((int)(1.f / Global::deltaTime.asSeconds())));

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || (event.type == Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		window.clear(Color::White);

		for (size_t i = 0; i < balls.size(); i++)
			balls[i].move();

		for (size_t i = 0; i < balls.size(); i++)
			window.draw(balls[i].getDrawable());

		window.draw(fps);
		window.display();
	}

	return EXIT_SUCCESS;
}