#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

#include "Game.h"

int main() 
{
    auto game = make_unique<Game>();
    game->run();
    return 0;
}
