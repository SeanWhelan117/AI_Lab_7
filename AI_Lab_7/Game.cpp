
#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 3000U, 2000U, 32U }, "Seáns Game" },
	m_exitGame{false} //when true game will exit
{
	srand(time(NULL));
	if (!m_NewYorkfont.loadFromFile("ASSETS\\FONTS\\NewYork.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	blackBox.setFillColor(sf::Color::Black);
	blackBox.setPosition(0, 1100);
	blackBox.setSize(sf::Vector2f(425, 1000));
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	if (sf::Keyboard::Space == t_event.key.code)
	{
		setEnemies = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (setEnemies)
	{
		setRandomEnemyVariables();
		setEnemies = false;
		findForceAndRange();
		fuzzyLogic();
		deFuzzifyResults();
		setupTexts();

	}

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	myPlayer.render(m_window);

	m_window.draw(blackBox);
	m_window.draw(EnemyNumberText);
	m_window.draw(EnemyDistanceText);
	m_window.draw(rangesText);
	m_window.draw(forcesText);
	m_window.draw(threatLevelText);
	m_window.draw(defuzzedResultText);



	for (int i = 0; i < numOfEnemies; i++)
	{
		myEnemies[i].render(m_window);
	}
	m_window.display();
}

void Game::setupTexts()
{
	EnemyNumberText.setString("");

	double pi = 3.14159265359;

	std::stringstream stream;

	EnemyNumberText.setFont(m_NewYorkfont);
	EnemyNumberText.setString("Num of Enemies: " + std::to_string(numOfEnemies));
	EnemyNumberText.setPosition(20.0f, 1125.0f);
	EnemyNumberText.setCharacterSize(30U);
	EnemyNumberText.setFillColor(sf::Color::Red);

	int distanceFromPlayer = randXPosEnemies - myPlayer.player.getPosition().x;
	EnemyDistanceText.setFont(m_NewYorkfont);
	EnemyDistanceText.setString("Enemy Distance: " + std::to_string(distanceFromPlayer));
	EnemyDistanceText.setPosition(20.0f, 1175.0f);
	EnemyDistanceText.setCharacterSize(30U);
	EnemyDistanceText.setFillColor(sf::Color::Red);

	stream << std::fixed << std::setprecision(3) << rangeClose;
	std::string closeString = stream.str();


	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(3) << rangeMid;
	std::string midString = stream2.str();


	std::stringstream stream3;
	stream3 << std::fixed << std::setprecision(3) << rangeFar;
	std::string FarString = stream3.str();

	rangesText.setFont(m_NewYorkfont);
	rangesText.setString("Ranges Relationships: \n close = " + closeString + "\n mid = " + midString + "\n far =" + FarString);
	rangesText.setPosition(20.0f, 1225.0f);
	rangesText.setCharacterSize(30U);
	rangesText.setFillColor(sf::Color::Red);

	std::stringstream stream4;
	stream4 << std::fixed << std::setprecision(3) << forceTiny;
	std::string tinyString = stream4.str();


	std::stringstream stream5;
	stream5 << std::fixed << std::setprecision(3) << forceSmall;
	std::string smallString = stream5.str();

	std::stringstream stream6;
	stream6 << std::fixed << std::setprecision(3) << forceMid;
	std::string midString2 = stream6.str();

	std::stringstream stream7;
	stream7 << std::fixed << std::setprecision(3) << forceLarge;
	std::string largeString = stream7.str();


	forcesText.setFont(m_NewYorkfont);
	forcesText.setString("forces Relationships: \n tiny = " + tinyString + "\n small = " + smallString + "\n mid =" + midString2 + "\n large =" + largeString);
	forcesText.setPosition(20.0f, 1400.0f);
	forcesText.setCharacterSize(30U);
	forcesText.setFillColor(sf::Color::Red);

	std::stringstream stream8;
	stream8 << std::fixed << std::setprecision(3) << threatLow;
	std::string lowString = stream8.str();

	std::stringstream stream9;
	stream9 << std::fixed << std::setprecision(3) << threatMid;
	std::string midString3 = stream9.str();

	std::stringstream stream10;
	stream10 << std::fixed << std::setprecision(3) << threatHigh;
	std::string highString = stream10.str();

	threatLevelText.setFont(m_NewYorkfont);
	threatLevelText.setString("Threat Level: \n low = " + lowString + "\n mid = " + midString3 + "\n high =" + highString);
	threatLevelText.setPosition(20.0f, 1600.0f);
	threatLevelText.setCharacterSize(30U);
	threatLevelText.setFillColor(sf::Color::Red);

	std::stringstream stream11;
	stream11 << std::fixed << std::setprecision(3) << defuzzedResult;
	std::string defuzzedString = stream11.str();

	defuzzedResultText.setFont(m_NewYorkfont);
	defuzzedResultText.setString("Defuzzified Result: " + defuzzedString);
	defuzzedResultText.setPosition(20.0f, 1800.0f);
	defuzzedResultText.setCharacterSize(30U);
	defuzzedResultText.setFillColor(sf::Color::Red);
}

void Game::setRandomEnemyVariables()
{
	numOfEnemies = rand() % 20 + 1;     
	randXPosEnemies = rand() % 2200 + 500;
	
	int tempY = 50;
	for (int i = 0; i < numOfEnemies; i++)
	{
		myEnemies[i].enemies.setPosition(randXPosEnemies, tempY);
		tempY += 100;
	}

}

void Game::findForceAndRange()
{
	//3 2338

	int force = numOfEnemies;
	int range = randXPosEnemies;

	//force calculations
	// 1 - 20 people
	// force tiny = 1 - 7
	// force small = 6 - 12
	// force mid = 11 - 17
	// force large = 16 - 20

	//double FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);

	forceTiny = FuzzyTrapezoid(force, 0, 3, 5, 7);
	forceSmall = FuzzyTrapezoid(force, 6, 8, 10, 12);
	forceMid = FuzzyTrapezoid(force, 11, 13, 15, 17);
	forceLarge = FuzzyTrapezoid(force, 16, 18, 20, 22);



	//range Calculations
	// 500 - 2700 pixels away
	// range close = 500 - 1300
	// range mid = 1150 - 2100
	// range far = 1950 - 2750

	rangeClose = FuzzyTrapezoid(range, 500, 700, 1100, 1300);
	rangeMid = FuzzyTrapezoid(range, 1150, 1350, 1900, 2100);
	rangeFar = FuzzyTrapezoid(range, 1950, 2150, 2550, 2750);


}


void Game::fuzzyLogic()
{
	threatLow = FuzzyOR(FuzzyOR(FuzzyAND(rangeMid, forceTiny), FuzzyAND(rangeMid, forceSmall)), FuzzyAND(rangeFar, FuzzyNOT(forceLarge)));
	threatMid = FuzzyOR(FuzzyOR(FuzzyAND(rangeClose, forceTiny), FuzzyAND(rangeMid, forceMid)), FuzzyAND(rangeFar, forceLarge));
	threatHigh = FuzzyOR(FuzzyAND(rangeClose, FuzzyNOT(forceTiny)), FuzzyAND(rangeMid, forceLarge));

}

void Game::deFuzzifyResults()
{
	defuzzedResult = 0;
	defuzzedResult = (threatLow * 10 + threatMid * 30 + threatHigh * 50) / (threatLow + threatMid + threatHigh);
}


double Game::FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3)
{
	double result = 0;
	double x = value;

	if ((x <= x0) || (x >= x3))
	{
		result = 0;
	}
	else if ((x >= x1) && (x <= x2))
	{
		result = 1;
	}
	else if ((x > x0) && (x < x1))
	{
		result = ((x - x0) / (x1 - x0));
	}
	else
	{
		result = ((x3 - x) / (x3 - x2));
	}

	return result;
}

double Game::FuzzyAND(double A, double B)
{
	return std::min(A, B);
}

double Game::FuzzyOR(double A, double B)
{
	return std::max(A, B);
}

double Game::FuzzyNOT(double A)
{
	return 1.0 - A;
}
