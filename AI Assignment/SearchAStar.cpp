#pragma once

#include "SearchAStar.h"
#include "Utilities.h"


bool CSearchAStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
	NodeList openList;
	NodeList closedList;
	unique_ptr<SNode> current(new SNode);
	SNode* prior = current.get();
	SNode* path1;
	start->score = CalcDistance(start, goal);
	openList.push_back(move(start));

	if (terrain[current->y + 1][current->x] != 0 && current->y + 1 < maxY) //North node CHECK IF NULL BECAUSE OUT OF BOUNDS OF THE VECTOR WOULD BE NULL IF THERE'S NO WALLS function
	{
		if (!Search(closedList, current->x, current->y + 1) && !Search(openList, current->x, current->y + 1)) //check that the node isn't already on the open/closed list to stop duplication
		{
			AddNode(openList, current->x, current->y + 1, prior);
		}
	}

	if (terrain[current->y][current->x + 1] != 0 && current->x + 1 < maxX) //East node
	{
		if (!Search(closedList, current->x + 1, current->y) && !Search(openList, current->x + 1, current->y))
		{
			AddNode(openList, current->x + 1, current->y, prior);
		}
	}

	if (terrain[current->y - 1][current->x] != 0 && current->y - 1 > 0) //South node
	{
		if (!Search(closedList, current->x, current->y - 1) && !Search(openList, current->x, current->y - 1))
		{
			AddNode(openList, current->x, current->y - 1, prior);
		}
	}

	if (terrain[current->y][current->x - 1] != 0 && current->x - 1 > 0) //West node
	{
		if (!Search(closedList, current->x - 1, current->y) && !Search(openList, current->x - 1, current->y))
		{
			AddNode(openList, current->x - 1, current->y, prior);
		}
	}

	while (!openList.empty())
	{
		current = move(openList.front()); // pop first element 


		if (current->x == goal->x && current->y == goal->y) //Goal is found
		{
			path1 = current.get();
			while (path1 != 0)
			{
				AddNode(path, path1->x, path1->y, 0);
				path1 = path1->parent;
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