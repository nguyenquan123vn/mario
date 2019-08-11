#include <iostream>
#include <cmath>
#include "character.h"

Character::Character(const int width, const int height, const std::shared_ptr<Level>& level):
    level(level),
    width(width),
    height(height)
{}

void Character::setJumpSpeed(const float value)
{
    jumpSpeed = value;
}

void Character::setMoveSpeed(const float value)
{
    moveSpeed = value;
}

void Character::setMaxSpeed(const float value)
{
    maxSpeed = value;
}

void Character::setStopSpeed(const float value)
{
    stopSpeed = value;
}

void Character::setVerticalVelocity(const float value)
{
    velocity.y = value;
}

void Character::setHorisontalVelocity(const float value)
{
    velocity.x = value;
}

void Character::setVelocity(const sf::Vector2f _velocity)
{
    velocity = _velocity;
}

sf::Vector2f Character::getVelocity() const
{
    return velocity;
}

sf::Vector2f Character::getPosition() const
{
    return position;
}

void Character::setPosition(const sf::Vector2f _position)
{
    position = _position;
}

void Character::move(Direction dir)
{
    setDirection(dir);
    velocity.x = velocity.x + dir * moveSpeed;
    
    if(fabsf(velocity.x) > maxSpeed) velocity.x = dir * maxSpeed;
}

void Character::jump()
{
    setVerticalVelocity(jumpSpeed);
}

void Character::updatePosition()
{   

        velocity.y += level -> getGravity();
        position.y += velocity.y;
        checkForGround();
        
        if(!isAlive())  return;

        checkForRoof();

        if(fabsf(velocity.x) < stopSpeed)    velocity.x = 0;
        else if(velocity.x > 0)              velocity.x -= stopSpeed;
        else                                velocity.x += stopSpeed;
        position.x += velocity.x;
        checkForWall();
    
}

Character::Direction Character::getDirection() const
{
    return dir;
}

void Character::setDirection(Direction new_dir)
{
    if(dir != new_dir)  dir = new_dir;
}

bool Character::onGround() const
{
    return _onGround;
}

bool Character::isAlive() const
{
    return _isAlive;
}

float Character::leftBoundary() const
{
    return position.x; 
}

float Character::rightBoundary() const
{
    return position.x + width;  
}

float Character::topBoundary() const
{
    return position.y;  //positionY;
}

float Character::bottomBoundary() const
{
    return position.y + height; 
}

void Character::kill()
{
    _isAlive = false;
}

int Character::bufferedRoundoff(float i) const
{
    if(i == (int)i) return i - 1;   
    else            return i;
}

int Character::left() const
{
    return position.x;  
}
int Character::right() const
{
    return bufferedRoundoff(position.x + width);    
}
int Character::top() const
{
    return position.y;   
}
int Character::bottom() const
{
    return bufferedRoundoff(position.y + height);   
}

void Character::checkForGround()
{
    if(position.y > level -> bottomBound() - height)
    {
        _isAlive = false;
        return;
    }

    if( level -> isPassable(left(), bottom() ) == false || 
        level -> isPassable(right(), bottom() ) == false)      
    {
        position.y = top();
        velocity.y = 0;
        _onGround = true; 
    }
    else    _onGround = false;
}

void Character::checkForRoof()
{
    if( level -> isPassable( left(), top()) == false ||   
        level -> isPassable( right(), top()) == false )  
    {
        position.y = getPosition().y + 1;
        velocity.y = -velocity.y;
    }
}

void Character::checkForWall()
{

    if(left() < level -> leftBound())
    {
        position.x = level -> leftBound();
        velocity.x = 0;
    }

    if(position.x > level -> rightBound() - width)
    {
        position.x = level -> rightBound() - width;
        velocity.x = 0;
    }

    if( level -> isPassable(left(), top() )  == false || 
        level -> isPassable(left(), bottom() ) == false)
    {
        position.x = left() + 1;
        velocity.x = 0;
    }
    if( level -> isPassable(right(), top() )  == false || 
        level -> isPassable(right(), bottom() ) == false)
    {
        position.x = right() - 1;
        velocity.x = 0;
    }
}

