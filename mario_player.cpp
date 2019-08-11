#include "mario_player.h"
#include <SFML/Graphics.hpp>

Mario::Mario(std::shared_ptr<Level>& level):
    Character(width, height, level),
    mario_sprite(width, height)
{
    setMaxSpeed(maxSpeed);
    setMoveSpeed(moveSpeed);
    setJumpSpeed(jumpSpeed);
    setStopSpeed(stopSpeed);

    if(!mario_text.loadFromFile(texture_path))
    {
        throw std::runtime_error("Failed to load " + texture_path);
    }
    mario_sprite.setTexture(mario_text);
}
    
sf::Sprite Mario:: getSprite() const
{
    return mario_sprite;
}

void Mario::draw(sf::RenderWindow& window)
{
    window.draw(mario_sprite);
}

void Mario::move(Direction dir)
{
    setDirection(dir);
    Character::move(dir);
}

void Mario::jump()
{
    if(!jumpKeyReleased)    return;
    
    jumpKeyReleased = false;

    if(onGround())
    {
        Character::jump();
    }
}

void Mario::endJump()
{    
    jumpKeyReleased = true;

    if(getVelocity().y < jumpSpeed/2) setVerticalVelocity(jumpSpeed/2);
}

void Mario::endWalk()
{
    moving = false;
}


void Mario::updatePosition()
{
    if(!onGround() )                                  mario_sprite.setPlayer(3);
    else if(mario_sprite.getCurrentTexture() == 3)    mario_sprite.setPlayer(0);
    else if(moving)                                   mario_sprite.update(0, 3);
    else                                              mario_sprite.update(0, 0);
    
    Character::updatePosition();
    
    mario_sprite.setPosition(getPosition().x, getPosition().y);
}

void Mario::stomp()
{
    setVerticalVelocity(jumpSpeed/2);
}



void Mario::setDirection(Direction new_dir)
{
    moving = true;
    
    if(getDirection() != new_dir)
    {
        mario_sprite.rotate();
        Character::setDirection(new_dir);
    }
}

