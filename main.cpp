#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"

int main()
{
    Game game(640, 512, 32, "Mario");
    game.run();
    return 0;
}
