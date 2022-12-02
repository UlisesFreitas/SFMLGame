#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"


class Game
{
private:
	//Variables
	unsigned int screenWidth{800};
	unsigned int screenHeight{600};

	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;
	
	std::map<std::string, int> supportedKeys;


	std::stack<State*> states;



	//Initialization
	void initWindow();
	void initKeys();
	void initStates();


public:
	//Constructors/Destructors

	Game();
	virtual	~Game();


	//Regular
	void endApplication();
	
	//Functions
		
	void updateSFMLEvents();
	void update();
	void updateDt();



	//Render
	void render();

	//Core
	void run();

};

#endif