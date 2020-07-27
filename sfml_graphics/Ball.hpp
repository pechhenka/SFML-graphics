#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "Global.hpp"

class Ball
{
public:
	void move();
	const sf::Drawable& getDrawable();

	Ball(const sf::Vector2f& pos, const sf::Vector2f& speed, const sf::Color& color, const float& radius);
private:
	sf::CircleShape circle;
	sf::Vector2f position; // Circle center (m)
	sf::Vector2f speed; // m/s
	float radius;

	sf::Vector2f offsetPos;
	float weight;
};