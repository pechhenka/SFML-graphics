#pragma once
#include <SFML/System/Vector2.hpp>

template<typename T>
sf::Vector2<T> operator-(const sf::Vector2<T>& a, const T& b) {
	return sf::Vector2<T>(a.x - b, a.y - b);
}

template<typename T>
sf::Vector2<T> operator+(const sf::Vector2<T>& a, const T& b) {
	return sf::Vector2<T>(a.x + b, a.y + b);
}

template<typename T>
T distanceSquared(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
	T distX = a.x - b.x;
	T distY = a.y - b.y;
	return distX * distX + distY * distY;
}