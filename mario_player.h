#ifndef _MARIO_PLAYER_H
#define _MARIO_PLAYER_H

#include <SFML/Graphics.hpp>
#include "level.h"
#include "animated_sprite.h"
#include "character.h"
#include <memory>

class Mario : public Character
{
    private:
        AnimatedSprite mario_sprite;
        sf::Texture mario_text;

        const std::string texture_path = "res/Textures/Mario.png";
        static const int height = 1;
        static const int width = 1;

        //mario stat
        const float jumpSpeed = -.25f;
        const float moveSpeed = .01f;
        const float maxSpeed = .15f;
        const float stopSpeed = 0.005f;

        bool moving = false;
        bool jumpKeyReleased = true;

        void setDirection(Direction dir) override;
    public:
        Mario(std::shared_ptr<Level>& level);
        
        sf::Sprite getSprite() const override;

        void move(Direction dir) override;
        void jump() override;
        void stomp();
        void endJump();
        void endWalk();

        void updatePosition() override;
        void draw(sf::RenderWindow& window) override;

};

#endif