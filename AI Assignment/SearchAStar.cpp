#pragma once

#include "SearchAStar.h"
#include "Utilities.h"


bool CSearchAStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
	int maxY = terrain.size() - 1; //used to check that the pointer stays within the vector
	int maxX = terrain[0].size() - 1;

	NodeList openList;
	NodeList closedList;
	unique_ptr<SNode> current(new SNode);
	unique_ptr<SNode> n(new SNode);
	SNode* prior = current.get();
	SNode* returnPath;
	start->score = CalcDistance(start, goal);
	openList.push_back(move(start));

	while (!openList.empty())
	{
		current = move(openList.front()); // pop first element 

		if (terrain[current->y + 1][current->x] != 0 && current->y + 1 < maxY) //North node 
		{
			
			AddNode(openList, current->x + 1, current->y, prior, current->score + terrain[current->x + 1][current->y]);

		}

		if (current->x == goal->x && current->y == goal->y) //Goal is found
		{
			returnPath = current.get();
			while (returnPath != 0)
			{
				AddNode(path, returnPath->x, returnPath->y, 0, returnPath->score);
				returnPath = returnPath->parent;
			}

			return true;
		}
	}
	return false; //return false if the open list is empty
}
bool CSearchAStar::FindPathRT(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, ModelMap &map, I3DEngine* &myEngine)
{
	return false;
}