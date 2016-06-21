#include "Game.h"

int main()
{
	Game game(14*64, 14*64);
	game.Initialize();
	game.Run();

	return 0;
}
