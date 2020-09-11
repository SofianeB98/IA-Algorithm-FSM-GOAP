#include "GOAPPlanner.h"

void GOAPPlanner::plan(const std::vector<Action>& actions, std::vector<std::pair<std::string, bool>> actualState, std::vector<std::pair<std::string, bool>> goal)
{
	//reset toutes les action
	// - exemple : Je suis plus en trian de miner, etc etc


	
	// --build graph
	// Pour chaque action :
	// - est ce que la precondition de laction est remplis par le state de la node a test ?
	//	- Oui --> j'applique l'effect de cette action sur le state et j'en créer un nouveau
	//	- puis je l'ajoute au graph
	//	- Non ? ---> Je recrer u nset sans cette action
	// ---------------------------


	//Je renvois un boolean si oui ou non j'ai reussis a planifier
	
}