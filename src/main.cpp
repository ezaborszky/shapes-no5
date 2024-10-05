#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include <imgui-SFML.h>
#include <imgui.h>

int main() 
{
  Game newGame;

  newGame.run();
  return 0;
}

