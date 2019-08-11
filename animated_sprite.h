#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "sprite.h"
#include <chrono>

class AnimatedSprite: public sprite
{
    public:
        AnimatedSprite(const int width, const int height, const double speed = 0.1);

        void update(const int startTexture, const int endTexture);

        void updateEnemy(const int startTexture, const int endTexture);

        void setPlayer(const int texture);

        void setEnemy(const int texture);

        void setTile(const int texture);

        int getCurrentTexture() const;

    private:
        
        using clock = std::chrono::high_resolution_clock;
        clock::time_point lastframe;

        bool nextTextureRight = true;
        
        const double speed;

        const int width, height;

        int currentTexture = 0;

        void animate(const int targetFrame);

        void animateEnemy(const int targetFrame);
};

#endif