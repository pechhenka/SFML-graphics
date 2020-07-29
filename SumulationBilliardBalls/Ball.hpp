#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Extension/SFML_Vector.hpp"

class Ball
{
public:
	sf::Vector2f getPosition();
	float getRadiusSquared();

	void move();
	const sf::Drawable& getDrawable();

	static void collisionHandling(Ball& a, Ball& b);

	Ball(const sf::Vector2f& pos, const sf::Vector2f& speed, const sf::Color& color, const float& radius);
private:
	sf::CircleShape circle;
	sf::Vector2f position; // Circle center (m)
	sf::Vector2f speed; // m/s
	float radius;
	float radiusSquared;

	sf::Vector2f offsetPos;
	float weight;
};