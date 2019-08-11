#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "level.h"
#include "mario_player.h"
#include "enemy.h"

class Game
{
    public:
        Game(int height, int width, int res, const std::string& title);
        void run();
        sf::View getView();
    private:
        sf::RenderWindow window;
        sf::View view;
        bool gameOver = false;
        bool gameWon = false;
        const float gravity = 0.0075f;    
        std::shared_ptr<Level> level;
        std::unique_ptr<Mario> mario_player;
        std::vector<std::unique_ptr<Enemy>> enemies;
        sf::Texture player; 
        sf::Font fonts;

        void init();
        void displayGameOver();
        void displayGameWon();
        void pause();
        void pollWindowEvents(sf::Event& event);
        void handleInputs();
        void handleButtonEvents(sf::Event& event);
        void updateObjects();
        void drawObjects();
        void checkForEnemyCollision();
        void cleanUpDeadEnemies();
        bool playerStompsEnemy(const std::unique_ptr<Enemy>& e);
};

#endif