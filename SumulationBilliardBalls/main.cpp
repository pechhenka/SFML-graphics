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
	for (int i = 0; i < 10; i++)
		balls.push_back(ToolBox::randBall(Global::windowSize));

	
	sf::Text fps;
	sf::Font font;
	if (!font.loadFromFile("Arial.ttf"))
	{
#ifdef _IOSTREAM_
		std::cout << "failed load font" << std::endl;
#endif
	}

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

		size_t ballsSize = balls.size();
		for (size_t i = 0; i < ballsSize; i++)
			balls[i].move();

		for (size_t i = 0; i < ballsSize; i++)
			for (size_t j = i + 1; j < ballsSize; j++)
			{
				sf::Vertex line[] = {
					sf::Vertex(balls[i].getPosition()),
					sf::Vertex(balls[j].getPosition())
				};
				line[0].color = Color::Red;
				line[1].color = Color::Green;
				window.draw(line, 2, sf::Lines);
				Ball::collisionHandling(balls[i], balls[j]);
			}

		for (size_t i = 0; i < ballsSize; i++)
			window.draw(balls[i].getDrawable());

		window.draw(fps);
		window.display();
	}

	return EXIT_SUCCESS;
}