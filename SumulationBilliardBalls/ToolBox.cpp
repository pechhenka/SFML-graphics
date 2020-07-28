#include "ToolBox.hpp"

void ToolBox::initRandomGeneration() {
	srand(static_cast <unsigned> (time(0)));
}

bool ToolBox::randBool() {
	return rand() % 2 == 0;
}

int ToolBox::randInt(const int& min, const int& max) {
	return min + (rand() % (max - min + 1));
}

float ToolBox::randFloat(const float& min, const float& max) {
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

sf::Vector2f ToolBox::randVector2f(const sf::Vector2f& min, const sf::Vector2f& max) {
	return sf::Vector2f(ToolBox::randFloat(min.x, max.x), ToolBox::randFloat(min.y, max.y));
}

Ball ToolBox::randBall(const sf::Vector2f& posSize)
{
	using namespace sf;

	const float speedMin = 5.f;
	const float speedMax = 100.f;

	float radius = ToolBox::randFloat(7.f, 20.f);

	Vector2f pos = ToolBox::randVector2f(Vector2f(radius, radius) + 1.f, posSize - (2 * radius - 2.f));

	bool flagSignSpeed[] = { ToolBox::randBool(), ToolBox::randBool() };
	Vector2f speed = ToolBox::randVector2f(
		Vector2f(flagSignSpeed[0] ? speedMin : -speedMin,
			flagSignSpeed[1] ? speedMin : -speedMin),
		Vector2f(flagSignSpeed[0] ? speedMax : -speedMax,
			flagSignSpeed[1] ? speedMax : -speedMax));

	Color color = Color(ToolBox::randInt(10, 240), ToolBox::randInt(10, 240), ToolBox::randInt(10, 240));

	return Ball(pos, speed, color, radius);
}