#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{

public:
	Player();

	void update(sf::Time t_deltaTime, sf::RenderWindow& t_window);

	void render(sf::RenderWindow& t_window);


	sf::CircleShape player;
private:


};

