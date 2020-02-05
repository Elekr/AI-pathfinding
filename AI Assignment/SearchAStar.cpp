#pragma once

#include "SearchAStar.h"
#include "Utilities.h"


bool CSearchAStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
	int maxY = terrain.size() - 1; //used to check that the pointer stays within the vector
	int maxX = terrain[0].size() - 1;
	int newCost;
	unique_ptr<SNode> current(new SNode);
	unique_ptr<SNode> n(new SNode);
	SNode* prior = current.get();
	SNode* returnPath;

	//Create Open and Closed lists
	NodeList openList;
	NodeList closedList;

	//Push start onto OpenList and set parent & cost to 0, set score to heuristic value
	start->score = CalcDistance(start, goal);
	openList.push_back(move(start));

	//or openList is empty
	while (!openList.empty())
	{
		if (current->x == goal->x && current->y == goal->y) //
		{
			returnPath = current.get();
			while (returnPath != 0)
			{
				AddNode(path, returnPath->x, returnPath->y, 0, returnPath->score);
				returnPath = returnPath->parent;
			}

			return true;
		}
		//pop the first element from the open list and call it current
		current = move(openList.front()); 

		if (terrain[current->y + 1][current->x] != 0 && current->y + 1 < maxY) //For each state that can match current
		{
			//i
			//Apply the rule to generate a new state and call it N
			n->x = current->x;
			n->y = current->y + 1;

			//ii
			//current cost = score - heuristic value;
			newCost = current->score - CalcDistance(current, goal) + terrain[current->x + 1][current->y]; // beware that current will have the heuristic cost after the first iteration (check if it's not the goal)

			//iii
			if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //if N is on the open or the closed list
			{
				//iv
				if (!getNScore(n, openList, closedList)) // if the new cost is not less than the existing cost 
				{
					//v
					if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //If N is on the open or closedList current = n
					{
						n = move(Transfer(n, openList, closedList)); // let n now refer to existing_n
						n->parent = current.get(); //Set the parent of n to current
						n->score = newCost + CalcDistance(n, goal); //Set the score of n to the newcost + heuristic value (calculating the accumulated cost through score so don't need to set the cost)

						if (Search(closedList, n->x, n->y)) // If n was on the closedList then remove it from the closedList and push to open
						{

						}
					}
					openList.push_back(move(n)); //if N was not on the open or closedList then push n to openList
				}

			}

			//AddNode(openList, current->x + 1, current->y, prior, current->score + terrain[current->x + 1][current->y]); //generate new state cost = cost of current + cost of next 
		}


		closedList.push_back(move(current)); // Push current on to the closedList

	}
	return false; //quit if the open list is empty
}
bool CSearchAStar::FindPathRT(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, ModelMap &map, I3DEngine* &myEngine)
{
	return false;
}