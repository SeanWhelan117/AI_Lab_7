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

	float threatLow = 0;
	float threatMid = 0;
	float threatHigh = 0;

	double defuzzedResult = 0;

	void fuzzyLogic();
	void deFuzzifyResults();
	void findForceAndRange();

	double FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);

	double FuzzyAND(double A, double B);

	double FuzzyOR(double A, double B);

	double FuzzyNOT(double A);

	sf::RectangleShape blackBox;
	sf::Text EnemyNumberText; 
	sf::Text EnemyDistanceText;
	sf::Text forcesText;
	sf::Text rangesText;
	sf::Text threatLevelText;
	sf::Text defuzzedResultText;

};

#endif // !GAME_HPP

