#pragma once
#include <cstdlib>
#include <ctime>
#include <SFML\System\Vector2.hpp>
#include "Ball.hpp"
#include "Extension/SFML_Vector.hpp"

class ToolBox
{
public:
	static void initRandomGeneration();
	static bool randBool();
	static int randInt(const int& min, const int& max); // return random int in [min; max]
	static float randFloat(const float& min, const float& max); // raturn random float in [min; max]
	static sf::Vector2f randVector2f(const sf::Vector2f& min, const sf::Vector2f& max);
	static Ball randBall(const sf::Vector2f& posSize);
};