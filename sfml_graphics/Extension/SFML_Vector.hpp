#pragma once
#include <SFML/System.hpp>

template<typename T>
sf::Vector2<T> operator-(const sf::Vector2<T>& a, const T& b) {
	return sf::Vector2<T>(a.x - b, a.y - b);
}

template<typename T>
sf::Vector2<T> operator+(const sf::Vector2<T>& a, const T& b) {
	return sf::Vector2<T>(a.x + b, a.y + b);
}