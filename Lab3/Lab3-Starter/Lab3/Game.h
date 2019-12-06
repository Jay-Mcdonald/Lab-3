/// <summary>
/// @author Jay McDonald
/// @date December 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// 
/// project comment in main.cpp
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processKeyReleases(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void processMouseReleaseEvents(sf::Event t_mouseEvent);
	void setupFontAndText(); // sets up font and text
	void setupSprite(); // sets up textures and sprites
	void setupShapes(); // sets up basic shapes
	void setupSounds(); // sets up audio

	void powerBar();// power bar function
	void meteoriteCreate(); // creates meteorite
	void meteorUpdate(); // moves meteorite
	void missileUpdate(); // moves missile
	void explosion(); // explosion update
	void detination(); // checks for collision between meteorite and explosion
	void changeTextures(); // changes textures
	void animateExplosion(); // animates explosion sprite
	void resetGame(); // resets the game

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_altitudeText; // text used for altitude bar
	sf::Text m_gameOverText; // text used for game over screen
	sf::Text m_scoreText; // text used for score
	sf::Text m_resetText; // text used for reset screen

	//Sounds
	sf::SoundBuffer m_boomBuffer; // bufferss explosion sound
	sf::Sound m_boomSound; // audio used for explosion sound

	//Textures
	sf::Texture m_groundTexture; // texture used for ground
	sf::Texture m_playerTexture; // texture used for player
	sf::Texture m_explosionTexture; // textures used for explosion

	//Sprites
	sf::Sprite m_groundSprite; // sprite used for ground
	sf::Sprite m_playerSprite; // sprite used for player
	sf::Sprite m_explosionSprite; // sprite used for explosion

	//Shapes
	sf::RectangleShape m_player; // player shape
	sf::RectangleShape m_ground; // ground shape
	sf::RectangleShape m_powerBar; // powerBar shape
	sf::CircleShape m_explosion; // explosion shape

	sf::Vector2f m_headingVector; // used for heading vector calculation
	sf::Vector2f m_velocity; // used for velocity variable
	sf::Vector2f m_meteorVelocity; // used for meteor velocity
	sf::Vector2f m_missileLocation; // used for missile location
	sf::Vector2f m_meteorLocation; // used for meteor location
	sf::Vector2f m_mouseInput; // stores mouse input
	sf::Vector2f m_distance; // //stores the distance between explosion and meteorite


	bool m_exitGame; // control exiting game
	bool m_canFire = true; // checks if player can shoot
	bool m_firing = false; // checks if laser is firing
	bool m_exploding = false; // checks if there is an explosion
	bool m_textures = false; // check if textures are active
	bool m_gameOver = false; // checks if the game has ended

	
	int m_meteoriteAmount{ 1 }; // limits meteorites to 1 at a time
	int m_score{ 0 }; // players score
	int m_explosionFrame{ 0 }; // checks for explosion animation fram
	float m_laserSpeed{ 3.5f }; // speed of laser
	float m_meteoriteSpeed{ 1.0f }; // speed of meteorite
	float radius{ 0.0f }; // radius of explosion
	float m_powerBarSize{ 0.0f }; // size of power bar
	float m_altitude{ 0.0f }; // max altitude
	float m_length; // length between laser and meteorite
	float m_explosionFrameCounter{ 0.0f };
	float m_explosionFrameIncrement{ 0.25f }; // speed of explosion animation
	

	sf::Vertex m_laserStart; // start point of laser
	sf::Vertex m_laserEnd; // end point of laser
	sf::Vertex m_meteorStart; // start point of meteorite
	sf::Vertex m_meteorEnd; // end point of meteorite

	sf::VertexArray m_line{ sf::Lines };
	sf::VertexArray m_meteoriteLines{ sf::Lines };

};

#endif // !GAME_HPP

