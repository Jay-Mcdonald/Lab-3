/// <summary>
/// @author Jay McDonald
/// @date December 2019
///
/// you need to change the above lines or lose marks
/// project comment in main.cpp
/// </summary>

#include "Game.h"
#include "MyVector2.h"
#include <iostream>
#include <math.h>
#include <string>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Lab3" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	setupShapes();
	setupSounds();
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
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseReleaseEvents(newEvent);
		}
		if (sf::Event::KeyReleased == newEvent.type)
		{
			processKeyReleases(newEvent);
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
}

void Game::processKeyReleases(sf::Event t_event)
{
	if (sf::Keyboard::T == t_event.key.code)
	{
		if (m_textures == false)
		{
			m_textures = true;
			changeTextures();
		}
		else
		{
			m_textures = false;
			changeTextures();
		}
	}

	if (sf::Keyboard::R == t_event.key.code)
	{
		if (m_gameOver == true)
		{
			resetGame();
			m_gameOver = false;
			
		}
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

	powerBar();
	missileUpdate();
	meteorUpdate();
	meteoriteCreate();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	if (m_textures == true)
	{
		//if textures are active, draw textures
		m_window.clear(sf::Color::Black);
		m_window.draw(m_groundSprite);
		m_window.draw(m_playerSprite);
		m_window.draw(m_powerBar);
		m_window.draw(m_explosion);
		m_window.draw(m_altitudeText);
		m_window.draw(m_gameOverText);
		m_window.draw(m_scoreText);
		m_window.draw(m_explosionSprite);
	}
	else
	{
		//if textures arent active, draw shapes
		m_window.clear(sf::Color::Black);
		m_window.draw(m_ground);
		m_window.draw(m_player);
		m_window.draw(m_powerBar);
		m_window.draw(m_explosion);
		m_window.draw(m_altitudeText);
		m_window.draw(m_gameOverText);
		m_window.draw(m_scoreText);
		
	}

	m_window.draw(m_resetText);
	m_window.draw(m_line);
	m_window.draw(m_meteoriteLines);
	m_window.display();

	

	
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_altitudeText.setFont(m_ArialBlackfont);
	m_altitudeText.setString("Altitude");
	m_altitudeText.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_altitudeText.setPosition(35.0f, 565.0f);
	m_altitudeText.setCharacterSize(20U);
	m_altitudeText.setFillColor(sf::Color::White);

	//Game Over Text
	m_gameOverText.setFont(m_ArialBlackfont);
	m_gameOverText.setString("GAME OVER!");
	m_gameOverText.setStyle(sf::Text::Bold);
	m_gameOverText.setPosition(250.0f, 250.0f);
	m_gameOverText.setCharacterSize(50U);
	m_gameOverText.setFillColor(sf::Color::Transparent);

	//Score Text
	m_scoreText.setFont(m_ArialBlackfont);
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_scoreText.setStyle(sf::Text::Bold);
	m_scoreText.setPosition(669.0f, 10.0f);
	m_scoreText.setCharacterSize(20U);
	m_scoreText.setFillColor(sf::Color::White);

	//Reset Game Text
	m_resetText.setFont(m_ArialBlackfont);
	m_resetText.setString("Push 'R' to reset the game");
	m_resetText.setPosition(250.0f, 335.0f);
	m_resetText.setCharacterSize(30.0f);
	m_resetText.setFillColor(sf::Color::Transparent);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	//Ground Texture
	if (!m_groundTexture.loadFromFile("ASSETS\\IMAGES\\ground.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading ground" << std::endl;
	}
	m_groundSprite.setTexture(m_groundTexture);
	m_groundSprite.setPosition(0.0f, 570.0f);
	
	//Player Texture
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\base.png"))
	{
		std::cout << "problem loading player texture" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(365.0f, 550.0f);

	//Explosion Texture
	if (!m_explosionTexture.loadFromFile("ASSETS\\IMAGES\\explosion.png"))
	{
		std::cout << "problem loading explosion texture" << std::endl;
	}
	m_explosionSprite.setTexture(m_explosionTexture);
	m_explosionSprite.setPosition(1000.0f, 1000.0f);
	m_explosionSprite.setTextureRect(sf::IntRect{ 0, 0, 66, 66 });
	m_explosionSprite.setOrigin(33, 33);
}


//Loads explosion sound
void Game::setupSounds()
{
	if (!m_boomBuffer.loadFromFile("ASSETS\\AUDIO\\explosion.wav"))
	{
		std::cout << "problem with Explosion sound" << std::endl;
	}
	m_boomSound.setLoop(false);
	m_boomSound.setBuffer(m_boomBuffer);
	
}


//Animates the explosion sprite
void Game::animateExplosion()
{
	
	m_explosionSprite.setPosition(m_missileLocation);
	
	m_explosionFrameCounter += m_explosionFrameIncrement;
	m_explosionFrame = static_cast<int>(m_explosionFrameCounter) % 9;
	m_explosionSprite.setTextureRect(sf::IntRect{ 0, m_explosionFrame * 66, 66, 66 });
	
}

void Game::setupShapes()
{
	//PlayerShape
	m_player.setSize(sf::Vector2f(50, 50));
	m_player.setPosition(375.0f, 510.0f);
	m_player.setFillColor(sf::Color(170, 0, 255));

	//GroundShape
	m_ground.setSize(sf::Vector2f(800, 40));
	m_ground.setPosition(0.0f, 560.0f);
	m_ground.setFillColor(sf::Color::Green);

	//Power BarShape
	m_powerBar.setPosition(140.0f, 566.0f);
	m_powerBar.setFillColor(sf::Color::Red);

	//ExplosionShape
	m_explosion.setFillColor(sf::Color::Transparent);
}

void Game::changeTextures()
{
	if (m_textures == false)
	{
		//PowerBar Setup
		m_powerBar.setPosition(140.0f, 566.0f);
		m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 25)); 

		//Altitude Text Setup
		m_altitudeText.setPosition(35.0f, 565.0f);
		m_altitudeText.setCharacterSize(20U);
	}
	else
	{
		//PowerBar Setup
		m_powerBar.setPosition(140.0f, 588.0f);
		m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 10));

		//Altitude Text Setup
		m_altitudeText.setPosition(35, 580.0f);
		m_altitudeText.setCharacterSize(15U);
	}
}


//Increases size of power bar
void Game::powerBar()
{
	if (m_powerBarSize <= 250.0f)
	{
		m_powerBarSize += 0.5f;
		if (m_textures == false)
		{
			m_powerBar.setPosition(140.0f, 566.0f);
			m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 25));
		}
		else
		{
			m_powerBar.setPosition(140.0f, 588.0f);
			m_powerBar.setSize(sf::Vector2f(m_powerBarSize, 10));
		}
	}
}

void Game::processMouseReleaseEvents(sf::Event t_mouseEvent)
{
	if(m_canFire == true)
	{
		if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
		{
			

			m_mouseInput = sf::Vector2f{ static_cast<float>(t_mouseEvent.mouseButton.x), static_cast<float>(t_mouseEvent.mouseButton.y) };

			if (m_mouseInput.y < m_player.getPosition().y)
			{
				if (m_mouseInput.x < 400)
				{
					m_playerSprite.setScale(sf::Vector2f{ -1.0f, 1.0f });
					m_playerSprite.setPosition(400.0f, 550.0f);
				}
				else
				{
					m_playerSprite.setScale(sf::Vector2f{ 1.0f, 1.0f });
					m_playerSprite.setPosition(365.0f, 550.0f);
				}
				m_firing = true;
				m_laserEnd = sf::Vertex{ m_mouseInput };
				m_powerBar.setSize(sf::Vector2f(0, 25));
				m_altitude = m_powerBarSize;
				m_powerBarSize = 0;
				m_explosion.setFillColor(sf::Color::Transparent);
				radius = 0;

				m_laserStart = { sf::Vector2f{400.0f, 510.0f}, sf::Color(170, 0, 255) };

				m_headingVector = m_mouseInput - m_laserStart.position;
				m_headingVector = vectorUnitVector(m_headingVector);
				m_velocity = m_headingVector * m_laserSpeed;
				m_missileLocation = sf::Vector2f{ 400.0f, 510.0f };

				
				m_canFire = false;
			}

			
		}
	}
}


//Moves missile
void Game::missileUpdate()
{
	if (m_firing == true)
	{
		if (!m_exploding)
		{
			m_missileLocation += m_velocity;
			m_laserEnd = { m_missileLocation, sf::Color::Magenta };
			m_laserStart.color = sf::Color::Blue;
			m_laserEnd.color = sf::Color(170, 0, 255);
			m_line.clear();
			m_line.append(m_laserStart);
			m_line.append(m_laserEnd);
		}
		
		//Calls detination function
		detination();

		//stops laser going past mouse input point
		if (m_missileLocation.y <= m_mouseInput.y)
		{
			m_missileLocation = m_mouseInput;
			explosion();
		}

		if (m_missileLocation.y <= m_player.getPosition().y - m_altitude * 4)
		{
			explosion();
		}
	}
}


//Checks for collision between meteor and explosion
void Game::detination()
{
	m_distance = m_meteorEnd.position - m_explosion.getPosition();
	m_length = vectorLength(m_distance);
	if (m_length < m_explosion.getRadius())
	{
		m_meteoriteLines.clear();
		m_meteorEnd.position = (sf::Vector2f{0.0f, 0.0f});
		m_meteoriteAmount = 1;
		m_score += 10;
		m_scoreText.setString("Score: " + std::to_string(m_score));
	}
}


//Makes explosion
void Game::explosion()
{
	//If textures arent active, draw circle shape(explosion)
	if (m_textures == false)
	{
		//If explosion is at radius of 25, explosion is over
		if (radius <= 25)
		{

			radius++;
			m_explosion.setOrigin(radius, radius);
			m_explosion.setPosition(m_missileLocation);
			m_explosion.setRadius(radius);
			m_explosion.setFillColor(sf::Color::Magenta);
			m_exploding = true;
		}
		else
		{

			m_explosion.setPosition(1000.0f, 1000.0f);
			m_missileLocation = sf::Vector2f{ 400.0f, 510.0f };
			m_firing = false;
			m_exploding = false;
			m_canFire = true;
		}
	}

	//If textures are active, draw explosion sprite
	else
	{
		//If explosion is at radius of 25, explosion is over
		if (radius <= 25)
		{

			radius += 1.5; // adds 1.5 to radius
			animateExplosion();// calls animate explosion function
			m_explosion.setOrigin(radius, radius);
			m_explosion.setPosition(m_missileLocation);
			m_explosion.setRadius(radius);
			m_explosion.setFillColor(sf::Color::Transparent);
			m_explosion.setOutlineColor(sf::Color::Red);
			m_explosion.setOutlineThickness(1);
			//Plays explosion sound
			if (sf::Sound::Playing != m_boomSound.getStatus())
			{
				m_boomSound.play();
			}
			m_exploding = true;
		}
		else
		{
			m_explosionSprite.setPosition(1000.0f, 1000.0f);
			m_explosion.setPosition(1000.0f, 1000.0f);
			m_missileLocation = sf::Vector2f{ 400.0f, 510.0f };
			m_firing = false;
			m_exploding = false;
			m_canFire = true;
		}
	}
	m_line.clear();
}


//Creates the meteor
void Game::meteoriteCreate()
{
	if (m_meteoriteAmount == 1)
	{
		m_meteorStart.position = { (float)(rand() % 800 + 1), 0.0f };
		m_meteorEnd.position = { (float)(rand() % 800 + 1), 510.0f };

		m_headingVector = m_meteorEnd.position - m_meteorStart.position;
		m_headingVector = vectorUnitVector(m_headingVector);
		m_meteorVelocity = m_headingVector * m_meteoriteSpeed;

		m_meteorEnd.position = m_meteorStart.position;

		m_meteoriteAmount = 0;
	}

}


//Moves the meteor
void Game::meteorUpdate()
{
	m_meteorEnd.position += m_meteorVelocity;
	m_meteorEnd.color = sf::Color::Red;
	m_meteorStart.color = sf::Color::Yellow;

	m_meteoriteLines.clear();

	m_meteoriteLines.append(m_meteorStart);
	m_meteoriteLines.append(m_meteorEnd);

	//Checks if the meteor has hit the ground
	if (m_meteorEnd.position.y >= m_ground.getPosition().y)
	{
		m_meteoriteLines.clear();
		
		m_line.clear();
		m_explosion.setFillColor(sf::Color::Transparent);
		m_powerBar.setFillColor(sf::Color::Transparent);
		m_gameOverText.setFillColor(sf::Color::Yellow);

		m_scoreText.setPosition(250.0f, 300.0f);
		m_scoreText.setCharacterSize(40U);
		m_gameOver = true;
		m_resetText.setFillColor(sf::Color::White);
		
	}
}

//Reset the game if the player lost
void Game::resetGame()
{
		m_resetText.setFillColor(sf::Color::Transparent);
		m_meteoriteLines.clear();
		m_meteorEnd.position = (sf::Vector2f{ 0.0f, 0.0f });
		m_meteoriteAmount = 1;
		m_powerBarSize = 0;
		m_line.clear();
		m_score == 0;
		m_powerBar.setFillColor(sf::Color::Red);
		m_gameOverText.setFillColor(sf::Color::Transparent);
		m_scoreText.setPosition(669.0f, 10.0f);
		m_scoreText.setCharacterSize(20U);
}
