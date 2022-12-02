#include "Game.h"


Game::Game()
{
    this->initWindow();
    this->initKeys();
    this->initStates();
   
}

Game::~Game() 
{
	delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::endApplication()
{
    std::cout << "Ending application"  << "\n";
}
void Game::updateSFMLEvents()
{
 
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }

}
void Game::updateDt()
{
    /*
    * Updates the dt variable with the time it takes to update and render one frame.
    */

    this->dt = this->dtClock.restart().asSeconds();
    //system("cls");
    //std::cout << this->dt << "\n";
}
void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->endApplication();
        this->window->close();
    }
        

}

void Game::render()
{
    this->window->clear();
    //Render items
    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}


void Game::initStates()
{
    this->states.push(
        new MainMenuState (
            this->window, 
            &this->supportedKeys
        ));
   /* this->states.push(
        new GameState(
            this->window,
            &this->supportedKeys
        ));*/
}

void Game::initKeys()
{

    std::ifstream ifs("Config/supportedkeys.ini");
    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;

        }
    }
    ifs.close();

    for (auto& i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";

    }

}
void Game::initWindow()
{
    /*
    * Open Config window file stream
    * Map line by line to get the values and setup the game settings.
    */
    std::ifstream ifs("Config/window.ini");

    std::string title = "WTF";
    sf::VideoMode window_bounds;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> vertical_sync_enabled;
    }
    //Close Game Settings Config stream.
    ifs.close();

    this->window = new sf::RenderWindow((window_bounds), title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);


}


