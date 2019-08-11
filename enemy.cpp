#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Enemy::Enemy(const sf::Vector2f position, const std::shared_ptr<Level>& Level):
    Character(width, height, Level),
    sprite(width, height, 0.1)
{
    setHorisontalVelocity(moveSpeed);
    setStopSpeed(0);

    Character::setPosition(position);
    
    try
    {
        textures.loadFromFile(texture_path);
    }
    catch(std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    sprite.setTexture(textures);
}

void Enemy::updatePosition()
{
    sprite.updateEnemy(0, 1);

    if(getVelocity().x == 0)
    {
        rotate();
        setHorisontalVelocity(moveSpeed * getDirection());
    }

    Character::updatePosition();

    sprite.setPosition(getPosition().x, getPosition().y);
}

sf::Sprite Enemy::getSprite() const
{
    return sprite;
}

void Enemy::rotate()
{
    if(getDirection() == Left)  setDirection(Right);
    else                        setDirection(Left);

    sprite.rotate();
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

