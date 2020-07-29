#pragma once
#include <SFML\System\Time.hpp>


class FPSCounter
{
public:
	int getFPS(const sf::Time& deltaTime);
	void setTimeLimit(const sf::Time& l);

	FPSCounter(const sf::Time& intervalTime);
	FPSCounter(const float& intervalTime);
private:
	int FPS = 60;

	float timeLimit = 0.2f;
	float timeAccumulator = 0.f;
	int countCalls = 0;
};

