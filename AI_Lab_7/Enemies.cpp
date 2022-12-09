#include "Enemies.h"

Enemies::Enemies()
{

	enemies.setFillColor(sf::Color::Red);
	enemies.setRadius(25);
}

void Enemies::update(sf::Time t_deltaTime, sf::RenderWindow& t_window)
{
}

void Enemies::render(sf::RenderWindow& t_window)
{
	t_window.draw(enemies);

}
