
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
	blackBox.setSize(sf::Vector2f(400, 1000));
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


	for (int i = 0; i < numOfEnemies; i++)
	{
		myEnemies[i].render(m_window);
	}
	m_window.display();
}

void Game::setupTexts()
{
	//blackBox.setPosition(0, 1100);
	EnemyNumberText.setString("");


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

	rangesText.setFont(m_NewYorkfont);
	rangesText.setString("Ranges Relationships: \n close = " + std::to_string(rangeClose) + "\n mid = " + std::to_string(rangeMid) + "\n far =" + std::to_string(rangeFar));
	rangesText.setPosition(20.0f, 1225.0f);
	rangesText.setCharacterSize(30U);
	rangesText.setFillColor(sf::Color::Red);

	forcesText.setFont(m_NewYorkfont);
	forcesText.setString("forces Relationships: \n tiny = " + std::to_string(forceTiny) + "\n small = " + std::to_string(forceSmall) + "\n mid =" + std::to_string(forceMid) + "\n large =" + std::to_string(forceLarge));
	forcesText.setPosition(20.0f, 1400.0f);
	forcesText.setCharacterSize(30U);
	forcesText.setFillColor(sf::Color::Red);

	threatLevelText.setFont(m_NewYorkfont);

	std::string message = "";

	if (threatHigh)
	{
		message = "high";
	}
	else if (threatMid)
	{
		message = "mid";
	}
	else if (threatLow)
	{
		message = "low";
	}

	threatLevelText.setString("Threat Level: " + message);
	threatLevelText.setPosition(20.0f, 1600.0f);
	threatLevelText.setCharacterSize(30U);
	threatLevelText.setFillColor(sf::Color::Red);

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
	int force = numOfEnemies;
	int range = randXPosEnemies;

	//force calculations
	// 1 - 20 people
	// force tiny = 1 - 7
	// force small = 6 - 12
	// force mid = 11 - 17
	// force large = 16 - 20

	forceTiny = 0;
	forceSmall = 0;
	forceMid = 0;
	forceLarge = 0;

	if (force >= 1 && force <= 5)
	{
		forceTiny = 1;
	}
	else if (force == 6)
	{
		forceTiny = 0.6;
		forceSmall = 0.1;
	}
	else if (force == 7)
	{
		forceTiny = 0.1;
		forceSmall = 0.6;
	}
	else if (force >= 8 && force <= 10)
	{
		forceTiny = 0;
		forceSmall = 1;
	}
	else if (force == 11)
	{
		forceSmall = 0.6;
		forceMid = 0.1;
	}
	else if (force == 12)
	{
		forceSmall = 0.1;
		forceMid = 0.6;
	}
	else if (force >= 13 && force <= 15)
	{
		forceSmall = 0;
		forceMid = 1;
	}
	else if (force == 7)
	{
		forceMid = 0.6;
		forceLarge = 0.1;
	}
	else if (force == 7)
	{
		forceMid = 0.1;
		forceLarge = 0.6;
	}
	else if (force >= 18 && force <= 22)
	{
		forceMid = 0;
		forceLarge = 1;
	}

	//range Calculations
	// 500 - 2700 pixels away
	// range close = 500 - 1300
	// range mid = 1100 - 2100
	// range far = 1900 - 2900

	rangeClose = 0;
	rangeMid = 0;
	rangeFar = 0;

	if (range >= 500 && range <= 1099)
	{
		rangeClose = 1;
		rangeMid, rangeFar = 0;

	}
	else if (range >= 1100 && range <= 1199)
	{
		rangeClose = 0.6;
		rangeMid = 0.1;
	}
	else if (range >= 1200 && range <= 1300)
	{
		rangeClose = 0.1;
		rangeMid = 0.6;
	}
	else if (range >= 1301 && force <= 1899)
	{
		rangeClose = 0;
		rangeMid = 1;
	}
	else if (range >= 1900 && range <= 1999)
	{
		rangeMid = 0.6;
		rangeFar = 0.2;
	}
	else if (range >= 2000 && range <= 2100)
	{
		rangeMid = 0.1;
		rangeFar = 0.6;
	}
	else if (range >= 2101 && force <= 2900)
	{
		rangeMid = 0;
		rangeFar = 1;
	}

	/*forceTiny, forceSmall, forceMid, forceLarge = 0;
	rangeClose, rangeMid, rangeFar = 0;*/

	if (forceTiny > 0.5)
	{
		forceTinyBool == true;
	}
	else if (forceSmall > 0.5)
	{
		forceSmallBool == true;
	}
	else if (forceMid > 0.5)
	{
		forceMidBool == true;
	}
	else if (forceLarge > 0.5)
	{
		forceLargeBool == true;
	}



	if (rangeClose > 0.5)
	{
		rangeCloseBool == true;
	}
	else if (rangeMid > 0.5)
	{
		rangeMidBool == true;
	}
	else if (rangeFar > 0.5)
	{
		rangeFarBool == true;
	}

}


void Game::fuzzyLogic()
{
	if ((rangeMid && forceTiny) || (rangeMid && forceSmall) || (rangeFar && !forceLarge))
	{
		threatLow = true;
		threatMid = false;
		threatHigh = false;
	}

	if ((rangeFar && forceLarge) || (rangeMid && forceMid) || (rangeClose && forceTiny))
	{
		threatMid = true;
		threatLow = false;
		threatHigh = false;
	}

	if ((rangeMid && forceLarge) || (rangeClose && !forceTiny))
	{
		threatLow = false;
		threatMid = false;
		threatHigh = true;
	}

}
