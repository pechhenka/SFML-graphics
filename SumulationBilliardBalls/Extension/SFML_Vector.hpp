#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

inline float vector2Length(const sf::Vector2f& a) {
	return sqrtf(a.x * a.x + a.y * a.y);
}

template<typename T>
inline sf::Vector2<T> operator-(const sf::Vector2<T>& a, const T& b) {
	return sf::Vector2<T>(a.x - b, a.y - b);
}

template<typename T>
inline sf::Vector2<T> operator+(const sf::Vector2<T>& a, const T& b) {
	return sf::Vector2<T>(a.x + b, a.y + b);
}

template<typename T>
inline T distanceSquared(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
	T distX = a.x - b.x;
	T distY = a.y - b.y;
	return distX * distX + distY * distY;
}

template<typename T>
inline T scalarMultiplication(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
	return a.x * b.x + a.y * b.y;
}