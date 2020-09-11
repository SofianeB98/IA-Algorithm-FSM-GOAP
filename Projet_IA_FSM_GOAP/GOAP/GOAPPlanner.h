#pragma once
#include <string>
#include <vector>

class Action;

class GOAPPlanner
{
public:
	void plan(const std::vector<Action>&, //action
		std::vector<std::pair<std::string, bool>> actualState, //actual state
		std::vector<std::pair<std::string, bool>> goal); //goal
};
