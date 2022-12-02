#include "MainMenuState.h"

MainMenuState::MainMenuState(
	sf::RenderWindow* window,
	std::map<std::string, int>* supportedKeys
)
	: State(window, supportedKeys)
{
	this->initKeybinds();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/keybinds.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);

		}
	}
	ifs.close();

}

void MainMenuState::endState()
{
	std::cout << "Ending game" << "\n";
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();

}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		std::cout << "Quit" << "\n";
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (target)
		target = this->window;
	target->draw(this->background);

}
