#include "sprite.h"
#include <iostream>


void sprite::rotate()
{
    if(getScale().x > 0)
    {
        setOrigin({getLocalBounds().width, 0});
        setScale(sf::Vector2f(-1, 1));
    }
    else
    {
        setOrigin({0, 0});
        setScale(sf::Vector2f(1, 1));
    }
}

void sprite::setPosition(float x, float y)
{
    sf::Sprite::setPosition(convertCoords(x), convertCoords(y));
}

void sprite::setTexture(sf::Texture& texture)
{
    sf::Sprite::setTexture(texture);
};

int sprite::getTextureSize()
{
    return textureSize;
}

float sprite::convertCoords(const float c)
{
    return c*textureSize;
}
