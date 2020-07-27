#include "Ball.hpp"

void Ball::move()
{
	position += speed * Global::deltaTime.asSeconds();
	if ((speed.x < 0.f && position.x - radius <= 0.f) ||
		(speed.x > 0.f && position.x + radius >= Global::windowSize.x)) speed.x = -speed.x;
	if ((speed.y < 0.f && position.y - radius <= 0.f) ||
		(speed.y > 0.f && position.y + radius >= Global::windowSize.y)) speed.y = -speed.y;
}

const sf::Drawable& Ball::getDrawable()
{
	circle.setPosition(position - offsetPos);
	return circle;
}

Ball::Ball(const sf::Vector2f& pos, const sf::Vector2f& speed, const sf::Color& color, const float& radius)
{
	circle.setPosition(pos);
	circle.setRadius(radius);
	circle.setFillColor(color);
	circle.setPointCount(40);
	offsetPos = sf::Vector2f(radius, radius);
	position = pos;
	this->speed = speed;
	this->radius = radius;
	weight = radius * radius; // reduction from M_PI * (radius ** 2)
}