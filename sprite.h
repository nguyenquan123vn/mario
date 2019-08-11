#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

class sprite : public sf::Sprite
{
    public:
        sprite() = default;
        
        void rotate();

        void setPosition(float x, float y);

        void setTexture(sf::Texture& texture);

        static int getTextureSize();
    
    private:    
        static constexpr int textureSize = 32;
        static float convertCoords(const float c);
};

#endif