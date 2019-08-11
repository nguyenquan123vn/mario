#include "animated_sprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(const int width, const int height, const double speed):
    width(width),
    height(height),
    speed(speed)
{
}

void AnimatedSprite::setPlayer(const int texture)
{
    currentTexture = texture;
    setTextureRect(sf::IntRect(texture * 32, 96, width * getTextureSize(), height * getTextureSize()));
}

void AnimatedSprite::setEnemy(const int texture)
{
    currentTexture = texture;
    setTextureRect(sf::IntRect(texture * 32, 0, width * getTextureSize(), height * getTextureSize()));
}

void AnimatedSprite::setTile(const int texture)
{
    currentTexture = texture;
    setTextureRect(sf::IntRect(texture * 32, 0, width * getTextureSize(), height * getTextureSize()));
}

void AnimatedSprite::update(const int startTexture, const int endTexture)
{   
    if(currentTexture == endTexture || currentTexture == 0)
        nextTextureRight = !nextTextureRight;

    if(currentTexture <= endTexture && nextTextureRight)
        animate(endTexture);
    else                               
        animate(startTexture);  
}   

int AnimatedSprite::getCurrentTexture() const
{
    return currentTexture;
}


void AnimatedSprite::animate(const int targetTexture)
{
    if(targetTexture == currentTexture) return;

    auto now = clock::now();

    std::chrono::duration<double> duration = now - lastframe;
    if(duration.count() > speed)
    {
        int x;
        if(currentTexture < targetTexture)  x = getTextureRect().left + getTextureSize();
        else                                x = getTextureRect().left - getTextureSize();
   
        setTextureRect(sf::IntRect(x, 96, width * getTextureSize(), height * getTextureSize()));
        
        currentTexture = x/getTextureSize();
        lastframe = clock::now();
    }
}

void AnimatedSprite::animateEnemy(const int targetTexture)
{
    if(targetTexture == currentTexture) return;

    auto now = clock::now();

    std::chrono::duration<double> duration = now - lastframe;
    if(duration.count() > speed)
    {
        int x;
        if(currentTexture < targetTexture)  x = getTextureRect().left + getTextureSize();
        else                                x = getTextureRect().left - getTextureSize();
   
        setTextureRect(sf::IntRect(x, 0, width * getTextureSize(), height * getTextureSize()));
        
        currentTexture = x/getTextureSize();
        lastframe = clock::now();
    }
}

void AnimatedSprite::updateEnemy(const int startTexture, const int endTexture)
{   
    if(currentTexture == endTexture || currentTexture == 0)
        nextTextureRight = !nextTextureRight;

    if(currentTexture <= endTexture && nextTextureRight)
        animateEnemy(endTexture);
    else                               
        animateEnemy(startTexture);  
}   