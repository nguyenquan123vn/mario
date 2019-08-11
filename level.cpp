#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "level.h"

Level::Level(float grav)
{
    gravity = grav;
}

void Level::loadLevel(const std::string& pathname)
{
    text_tile.loadFromFile("res/Textures/Tiles.png");
    std::fstream file(pathname);
    if(!file.is_open())
    {
        throw std::runtime_error ("Error to load level");
    }

    for(int i = 0; !file.eof(); ++i)
    {
        std::string level_line ;
        file >> level_line;
        //std::cout << level_line << '\n';
        map_tile.push_back(std::vector<char> ());
        for(int j = 0; j < level_line.length(); ++j)
        {
            map_tile.back().push_back(level_line[j]);
            if(map_tile[i][j] == 'g')
            {
                finish = j;
            }
            //std::cout << map_tile[i][j];
        }
        //std::cout << '\n';
    } 
    file.close();
}

float Level::getGravity() const
{
    return gravity;
}

void Level::load_background(const std::string& path)
{
    background_text.loadFromFile(path);
}

int Level::leftBound() const
{
    return 0;
}

int Level::rightBound() const
{
    return map_tile[0].size();
} 

int Level::topBound() const
{
    return 0;
}

int Level::bottomBound() const
{
    return map_tile.size();
}

bool Level::isPassable(const int x, const int y) const
{
    if(map_tile[y][x] != '-' &&  map_tile[y][x] != '0' && map_tile[y][x] != 't' &&  map_tile[y][x] != '1' 
       && map_tile[y][x] != '2' &&  map_tile[y][x] != '3' &&  map_tile[y][x] != 'g' && map_tile[y][x] != 'b'
       &&  map_tile[y][x] != '4')
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

bool Level::reachedFinish(const int x) const
{
    return x > finish;
}


void Level::draw(sf:: RenderWindow& window)
{
    /*sf::Sprite background(background_text);
    background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    background.setPosition(sf::Vector2f(window.getView().getSize().x, window.getView().getSize().y));
    window.draw(background); */

    sf::Sprite sprite;
    for (int j = 0; j < map_tile.size(); ++j)
    {
        for (int i = 0; i < map_tile[j].size(); ++i)
        {
            // std::cout << map_tile[j][i];
            sprite.setTexture(text_tile);
            if(map_tile[j][i] == 'G')
            {
                sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
            }   
            else if(map_tile[j][i] == 'B' || map_tile[j][i] == 'b')
            {
                sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
            }
            else if(map_tile[j][i] == 'P')
            {
                sprite.setTextureRect(sf::IntRect(224, 32, 32, 32));
            }
            else if(map_tile[j][i] == 'S')
            {
                sprite.setTextureRect(sf::IntRect(192, 32, 32, 32));
            }
            else if(map_tile[j][i] == 'L')
            {
                sprite.setTextureRect(sf::IntRect(192, 64, 32, 32));
            }
            else if(map_tile[j][i] == 'R')
            {
                sprite.setTextureRect(sf::IntRect(224, 64, 32, 32));
            }
            else if(map_tile[j][i] == 'Q')
            {
                sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
            }
            else if(map_tile[j][i] == '0')
            {
                sprite.setTextureRect(sf::IntRect(80 ,160, 64, 64));
            }
            else if(map_tile[j][i] == 't')
            {
                sprite.setTextureRect(sf::IntRect(32 ,160, 32, 32));
            }
            else if(map_tile[j][i] == 'q')
            {
                sprite.setTextureRect(sf::IntRect(64 ,32, 32, 32));
            }
            else if(map_tile[j][i] == 'g')
            {
                sprite.setTextureRect(sf::IntRect(96, 256, 32, 64));
            }
            else if(map_tile[j][i] == '1')
            {
                sprite.setTextureRect(sf::IntRect(0, 256, 32, 32));
            }
            else if(map_tile[j][i] == '2')
            {
                sprite.setTextureRect(sf::IntRect(32, 256, 32, 32));
            }
            else if(map_tile[j][i] == '3')
            {
                sprite.setTextureRect(sf::IntRect(0, 256, 32, 64));
            }
            else if(map_tile[j][i] == '4')
            {
                sprite.setTextureRect(sf::IntRect(64, 256, 32, 64));
            }
            else
            {
                sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));
            } 
            sprite.setPosition(i * 32, j * 32);
            window.draw(sprite);
        }
        //std::cout << '\n';
    }
}
