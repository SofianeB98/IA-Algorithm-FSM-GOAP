#include "GameMaster.h"

int main()
{
	GameMaster gm{};

	//Initialise le programme
	gm.StartGame();

	//boucle principale du programme
	gm.UdapteGame();

	//destruction de tout les element
	gm.DeleteGame();

	return EXIT_SUCCESS;
}