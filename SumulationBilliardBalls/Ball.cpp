#include "Ball.hpp"

sf::Vector2f Ball::getPosition() {
	return position;
}

float Ball::getRadiusSquared()
{
	return radiusSquared;
}

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

void Ball::collisionHandling(Ball& a, Ball& b)
{
	float radiusSumm = a.radius + b.radius;
	auto processed = std::find(a.processedBalls.begin(), a.processedBalls.end(), &b);
	bool impactDistance = distanceSquared(a.position, b.position) <= radiusSumm * radiusSumm;
	if (!impactDistance) {
		if (processed != a.processedBalls.end())
		{
			a.processedBalls.erase(processed);
			return;
		}
	}
	else if (impactDistance && processed == a.processedBalls.end())
	{
		a.processedBalls.push_front(&b);
		// n - normal; t - tangent; r - "after the collision"
		// 1.
		sf::Vector2f normal = b.position - a.position;
		sf::Vector2f unitNormal = normal / vector2Length(normal);
		sf::Vector2f unitTangent(-unitNormal.y, unitNormal.x);

		// 3.
		float fVan = scalarMultiplication(unitNormal, a.speed);
		float fVat = scalarMultiplication(unitTangent, a.speed);
		float fVbn = scalarMultiplication(unitNormal, b.speed);
		float fVbt = scalarMultiplication(unitTangent, b.speed);

		// 4.
		float fVatr = fVat;
		float fVbtr = fVbt;

		// 5.
		float fVanr = (fVan * (a.weight - b.weight) + 2 * b.weight * fVbn) / (a.weight + b.weight);
		float fVbnr = (fVbn * (b.weight - a.weight) + 2 * a.weight * fVan) / (a.weight + b.weight);

		// 6.
		sf::Vector2f Vanr = fVanr * unitNormal;
		sf::Vector2f Vatr = fVatr * unitTangent;
		sf::Vector2f Vbnr = fVbnr * unitNormal;
		sf::Vector2f Vbtr = fVbtr * unitTangent;

		// 7.
		a.speed = Vanr + Vatr;
		b.speed = Vbnr + Vbtr;
	}
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
	radiusSquared = radius * radius;
	weight = radius * radius; // reduction from M_PI * (radius ** 2)
	processedBalls.clear();
}

void Ball::externalBallDeleted()
{
	for (auto it = this->processedBalls.begin(); it != this->processedBalls.end(); it++) {
		if (*it == nullptr)
			this->processedBalls.erase(it);
	}
}