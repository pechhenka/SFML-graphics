#include <SFML/Graphics.hpp>
#include "ToolBox.hpp"
#include "Global.hpp"
#include "Ball.hpp"
#include <iostream>
#include <vector>
#include "FPSCounter.hpp"
#include "Extension/SFML_Vector.hpp"
#include "Extension/SFML_Cursor.hpp"
#include "ToolBox.hpp"
#include <algorithm>

// 1 pixel = 1 meter

int main(/*int argc, char* argv[]*/)
{
	/*std::cout << "Count args: " << argc << std::endl;
	for (int i = 0; i < argc; i++)
		std::cout << i << ") " << argv[i] << std::endl;*/

	using namespace sf;

	ToolBox::initRandomGeneration();

	ContextSettings settings;
	settings.antialiasingLevel = 16;

	RenderWindow window(VideoMode::getFullscreenModes()[0], "Balls", Style::Fullscreen, settings);
	window.setVerticalSyncEnabled(true);
	Global::windowSize = Vector2f(window.getSize());

	std::vector<Ball> balls;
	for (int i = 0; i < 100; i++)
		balls.push_back(ToolBox::randBall(Global::windowSize));

	sf::Font Arial_font;
	if (!Arial_font.loadFromFile("Arial.ttf"))
	{
#ifdef _IOSTREAM_
		std::cout << "failed load font" << std::endl;
#endif
	}

	FPSCounter FPS_counter(0.15f);
	sf::Text FPS_text;
	FPS_text.setFont(Arial_font);
	FPS_text.setCharacterSize(36);
	FPS_text.setFillColor(Color::Red);

	SFML_Cursor cur(&window);

	sf::Clock clock;
	while (window.isOpen())
	{
		Global::deltaTime = clock.restart();
		if (Global::onStatistics)
			FPS_text.setString(std::to_string(FPS_counter.getFPS(Global::deltaTime)));

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape))
				window.close();
			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::LControl || event.key.code == Keyboard::RControl)
					Global::linesBethBalls = !Global::linesBethBalls;
				if (event.key.code == Keyboard::Tab)
					Global::ClearWindow = !Global::ClearWindow;
				if (event.key.code == Keyboard::D)
					Global::drawBalls = !Global::drawBalls;
				if (event.key.code == Keyboard::I)
					Global::InvertBackgroundColor = !Global::InvertBackgroundColor;
				if (event.key.code == Keyboard::S)
					Global::onStatistics = !Global::onStatistics;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Add || event.key.code == Keyboard::Equal)
					balls.push_back(ToolBox::randBall(Global::windowSize));
				if ((event.key.code == Keyboard::Subtract || event.key.code == Keyboard::Hyphen) && !balls.empty())
				{
					size_t lastBall = balls.size() - 1;
					std::swap(balls[lastBall], balls[ToolBox::randIntIncl(lastBall)]);
					balls.pop_back();
					size_t ballsSize = balls.size();
					for (size_t i = 0; i < ballsSize; i++)
						balls[i].externalBallDeleted();
				}
			}
		}

		if (Global::ClearWindow)
			window.clear(Global::InvertBackgroundColor ? Color(28, 28, 32) : Color(248, 248, 240));

		size_t ballsSize = balls.size();
		for (size_t i = 0; i < ballsSize; i++)
			balls[i].move();

		for (size_t i = 0; i < ballsSize; i++)
			for (size_t j = i + 1; j < ballsSize; j++)
			{
				if (Global::linesBethBalls)
				{
					sf::Vertex line[] = {
						sf::Vertex(balls[i].getPosition()),
						sf::Vertex(balls[j].getPosition())
					};
					line[0].color = Color::Red;
					line[1].color = Color::Green;
					window.draw(line, 2, sf::Lines);
				}
				Ball::collisionHandling(balls[i], balls[j]);
			}

		Vector2i mouse = Mouse::getPosition();
		bool flag = false;
		if (Global::drawBalls)
			for (size_t i = 0; i < ballsSize; i++)
			{
				if (!flag && distanceSquared<float>(balls[i].getPosition(), mouse) <= balls[i].getRadiusSquared())
					flag = true;
				window.draw(balls[i].getDrawable());
			}

		/*if (flag)
			cur.setCursorType(Cursor::Type::SizeAll);
		else
			cur.setCursorType(Cursor::Type::Arrow);*/

		if (Global::onStatistics)
		{
			/*FloatRect br = FPS_text.getGlobalBounds();
			sf::RectangleShape background(sf::Vector2f(br.width, br.height));
			background.setFillColor(Color(128,128,128));
			window.draw(background, FPS_text.getTransform());*/
			window.draw(FPS_text);
		}
		window.display();
	}

	return EXIT_SUCCESS;
}