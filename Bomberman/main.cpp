#include "Game.h"

int main()
{
	Game game(12*64, 10*64);
	game.Initialize();
	game.Run();

	return 0;
}
