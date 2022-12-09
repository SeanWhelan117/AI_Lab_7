#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemies
{
public:
	Enemies();

	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window);

	void render(sf::RenderWindow& t_window);


	sf::CircleShape enemies;
private:



};

