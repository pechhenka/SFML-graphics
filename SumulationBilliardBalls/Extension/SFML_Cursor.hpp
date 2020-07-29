#pragma once
#include <SFML\Window\Cursor.hpp>
#include <SFML\Graphics\RenderWindow.hpp>


class SFML_Cursor
{
public:
	void setCursorType(const sf::Cursor::Type& type);
	void setRenderWindow(sf::RenderWindow* win);

	SFML_Cursor(sf::RenderWindow* win);
private:
	sf::Cursor cursor;
	sf::RenderWindow* window;
};