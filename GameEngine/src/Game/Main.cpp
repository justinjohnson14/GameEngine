#include <iostream>

#include "Game.h"
#include "Application.h"

int main()
{
	Game* game = new Game();
	auto app = new Application("New Game", 800, 600, true, game);
	delete app;
	return 0;
}