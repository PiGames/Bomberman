#include "Game.h"

int main()
{
	Menu * menu = new Menu();

	if (!menu->Run())
	{
		return 0;
	}
	delete menu;

	Game game(12*64, 10*64);
	game.Initialize();
	game.Run();

	return 0;
}
