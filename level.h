#ifndef _LEVEL_H
#define _LEVEL_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "animated_sprite.h"

class Level
{
    private:
        float gravity;
        int finish;
        sf::Texture text_tile, background_text;
        std::vector<std::vector<char> > map_tile;

    public:
        Level(const float grav);
        void load_background(const std::string& path);
        void loadLevel(const std::string& path_level);
        
        //bounds of level
        int leftBound() const;
        int rightBound() const;
        int topBound() const;
        int bottomBound() const;

        float getGravity() const;
        bool isPassable(const int x, const int y) const; //check if tile is passable
        bool reachedFinish(const int x) const;

        void draw(sf::RenderWindow& window);
};

#endif