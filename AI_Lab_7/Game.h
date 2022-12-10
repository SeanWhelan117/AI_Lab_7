#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Enemies.h"
#include "Player.h"
#include <iostream>
class Game
{
public:
	Game();
	~Game();
	static const int MAX_ENEMIES = 20;
	Enemies myEnemies[MAX_ENEMIES];
	Player myPlayer;
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupTexts();
	void setRandomEnemyVariables();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_NewYorkfont; // font used by message
	bool m_exitGame; // control exiting game
	bool setEnemies = false;
	int numOfEnemies = 0;
	int randXPosEnemies = 0;

	float forceTiny, forceSmall, forceMid, forceLarge = 0;
	float rangeClose, rangeMid, rangeFar = 0;

	bool rangeCloseBool, rangeMidBool, rangeFarBool = false;
	bool forceTinyBool, forceSmallBool, forceMidBool, forceLargeBool = false;

	bool threatLow, threatMid, threatHigh;

	void fuzzyLogic();
	void findForceAndRange();

	sf::RectangleShape blackBox;
	sf::Text EnemyNumberText; 
	sf::Text EnemyDistanceText;
	sf::Text forcesText;
	sf::Text rangesText;
	sf::Text threatLevelText;

};

#endif // !GAME_HPP

