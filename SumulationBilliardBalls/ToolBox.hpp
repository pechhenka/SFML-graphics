#pragma once
#include <cstdlib>
#include <ctime>
#include <SFML\System\Vector2.hpp>
#include "Ball.hpp"
#include "Extension/SFML_Vector.hpp"
#include <cmath>

namespace ToolBox
{
	void initRandomGeneration();
	bool randBool();
	int randInt(const int& min, const int& max); // return random int in [min; max]
	float randFloat(const float& min, const float& max); // raturn random float in [min; max]
	sf::Vector2f randVector2f(const sf::Vector2f& min, const sf::Vector2f& max);
	Ball randBall(const sf::Vector2f& posSize);
};