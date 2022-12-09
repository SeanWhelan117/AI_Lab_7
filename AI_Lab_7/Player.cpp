#include "Player.h"

Player::Player()
{
	player.setFillColor(sf::Color::Green);
	player.setRadius(25);
	player.setPosition(50, 1000);
}

void Player::update(sf::Time t_deltaTime, sf::RenderWindow& t_window)
{
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(player);
}
