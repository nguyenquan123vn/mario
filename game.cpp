#include "game.h"
#include <iostream>

Game::Game(int width, int height, int res,const std::string& title):
        window(sf::VideoMode(width, height, res), title),
        level(std::make_unique<Level>(gravity) ),
        mario_player(std::make_unique<Mario> (level))
{
    window.setFramerateLimit(60);
    level -> loadLevel("res/Levels/level1.txt");
    //level -> load_background("res/Textures/Backgrounds/Sky.png");
    enemies.emplace_back(std::make_unique<Enemy>(sf::Vector2f(30.f, 12.f), level));
    enemies.emplace_back(std::make_unique<Enemy>(sf::Vector2f(20.f, 12.f), level));
    enemies.emplace_back(std::make_unique<Enemy>(sf::Vector2f(55.f, 12.f), level));
    enemies.emplace_back(std::make_unique<Enemy>(sf::Vector2f(100.f, 12.f), level));
    enemies.emplace_back(std::make_unique<Enemy>(sf::Vector2f(127.f, 12.f), level));
    std::cout  << level -> leftBound();
}


void Game::init()
{   
    window.clear();
    view.setSize(window.getSize().x, window.getSize().y);
    //view.setCenter(sf::Vector2f(mario_player.getPos_x(), mario_player.getPos_y()));
    view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
    window.setView(view);
}

void Game::displayGameOver()
{
    try
    {
        fonts.loadFromFile("res/Fonts/menu_font.ttf");
    }
    catch(std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    
    sf::Text text("GAME OVER", fonts);

    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);

    window.setView(window.getDefaultView());
    text.setPosition(window.getSize().x/2, window.getSize().y/2);

    sf::sleep(sf::seconds(1));

    window.clear(sf::Color::Black);
    window.draw(text);
    window.display();

    sf::sleep(sf::seconds(2));
}

void Game::displayGameWon()
{
    try
    {
        fonts.loadFromFile("res/Fonts/menu_font.ttf");
    }
    catch(std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }
    
    sf::Text text("You won", fonts);

    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);

    window.setView(window.getDefaultView());
    text.setPosition(window.getSize().x/2, window.getSize().y/2);

    sf::sleep(sf::seconds(1));

    window.clear(sf::Color::Black);
    window.draw(text);
    window.display();

    sf::sleep(sf::seconds(2));
}

void Game::handleInputs()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        mario_player->jump();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mario_player-> endWalk();
    } 
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        mario_player -> move(Mario::Right);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        mario_player -> move(Mario::Left);
    }
}

void Game::handleButtonEvents(sf::Event& event)
{
    switch(event.key.code)
    {
        case sf::Keyboard::Up:      mario_player -> endJump();
                                    break;
        case sf::Keyboard::Left:
        case sf::Keyboard::Right:   mario_player -> endWalk();
                                    break;
        default:                    break;
    }
}

void Game::pollWindowEvents(sf::Event& event)
{
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyReleased)
            handleButtonEvents(event);
    }   
}

void Game::updateObjects()
{
    mario_player -> updatePosition();

    if(mario_player->isAlive() == false)   
    {
        gameOver = true;
        return;
    }

    if(level->reachedFinish(mario_player->getPosition().x)) 
    {
        gameWon = true;
        return;
    }

    std::for_each(enemies.begin(), enemies.end(), [](std::unique_ptr<Enemy>& e)
    {
        e->updatePosition();
    });

    checkForEnemyCollision();
    cleanUpDeadEnemies();

    view.setCenter(sf::Vector2f(mario_player -> getSprite().getPosition().x, window.getSize().y / 2));
    
    if(view.getCenter().x < view.getSize().x/2)
        view.setCenter(sf::Vector2f(view.getSize().x/2, window.getSize().y / 2));

    window.setView(view);
}

void Game::drawObjects()
{
    window.clear(sf::Color::Blue);
    level -> draw(window);

     std::for_each(enemies.begin(), enemies.end(), [this](std::unique_ptr<Enemy>& e)
    {
        e->draw(window);
    });
    mario_player -> draw(window);
    window.display();
}

void Game::run()
{
    init();
    while (window.isOpen())
    {
        handleInputs();
        updateObjects();
        sf::Event event;
        pollWindowEvents(event);
        if(gameOver == true)
        {
            displayGameOver();
            return;
        }
        if(gameWon == true)
        {
            displayGameWon();
            return;
        }
        drawObjects();
    }
}

void Game::cleanUpDeadEnemies()
{
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const std::unique_ptr<Enemy>& e)
    {
        if(!e->isAlive())   return true;
        else                return false;
    }), enemies.end());
}

bool Game::playerStompsEnemy(const std::unique_ptr<Enemy>& e)
{
    float slope = (e->getPosition().y- mario_player->getPosition().y)/(e->getPosition().y-mario_player->getPosition().y);
    
    return (slope >= 1) && mario_player->bottomBoundary() < e->bottomBoundary() && mario_player->getVelocity().y > 0;
}

void Game::checkForEnemyCollision()
{
    std::for_each(enemies.begin(), enemies.end(), [this](std::unique_ptr<Enemy>& e)
    {
        if(mario_player->getSprite().getGlobalBounds().intersects(e->getSprite().getGlobalBounds()))
        {
            if(playerStompsEnemy(e))
            {
                e->kill();
                mario_player->stomp();
            }
            else    
            {
                gameOver = true;
            }
        }
    }); 
}