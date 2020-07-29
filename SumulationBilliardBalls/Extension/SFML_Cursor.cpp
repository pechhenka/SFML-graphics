#include "SFML_Cursor.hpp"

void SFML_Cursor::setCursorType(const sf::Cursor::Type& type)
{
	if (cursor.loadFromSystem(type))
		window->setMouseCursor(cursor);

}

void SFML_Cursor::setRenderWindow(sf::RenderWindow* win)
{
	window = win;
}

SFML_Cursor::SFML_Cursor(sf::RenderWindow* win)
{
	window = win;
}
