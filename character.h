#ifndef CHARACTER_H
#define CHARACTER_H

#include "level.h"
#include "animated_sprite.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Character
{
public:
    Character(const int width, const int height, const std::shared_ptr<Level>& level); 

    void setJumpSpeed(const float value);   

    void setMoveSpeed(const float value);   
    void setMaxSpeed(const float value);    
    void setStopSpeed(const float value);
    void setVerticalVelocity(const float value);   
    void setHorisontalVelocity(const float value);
    
    void setVelocity(const sf::Vector2f _velocity); 
    
    sf::Vector2f getVelocity() const;   
    sf::Vector2f getPosition() const;   
    void setPosition(const sf::Vector2f _position); 

    virtual sf::Sprite getSprite() const = 0;   

    virtual void draw(sf::RenderWindow& window) = 0;    

    
    enum Direction 
    {
        Left = -1,
        Right = 1
    };

    virtual void move(Direction dir);   

    virtual void jump();    
    virtual void updatePosition();  
    Direction getDirection() const;
    
    virtual void setDirection(Direction dir);

    bool onGround() const;

    bool isAlive() const;

    float leftBoundary() const;

    float rightBoundary() const;

    float topBoundary() const;

    float bottomBoundary() const;

    void kill();

private:

    void checkForGround();

    void checkForRoof();

    void checkForWall();

    int bufferedRoundoff(float i) const;

    int left() const;

    int right() const;

    int top() const;

    int bottom() const;

    //character variables
    const std::shared_ptr<Level> level;

    const int height;
    const int width;

    bool _onGround = false;

    float jumpSpeed = 0;
    float moveSpeed = 0;
    float maxSpeed = 0;
    float stopSpeed = 0;

    sf::Vector2f velocity = {0, 0};
    sf::Vector2f position = {5, 12};

    Direction dir = Right;

    bool _isAlive = true;

};

#endif