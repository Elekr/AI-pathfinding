#pragma once

#include "SearchAStar.h"
#include "Utilities.h"


bool CSearchAStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
	int maxY = terrain.size() - 1; //used to check that the pointer stays within the vector
	int maxX = terrain[0].size() - 1;
	int newCost;
	int timesSorted = 0;
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
		
		//pop the first element from the open list and call it current
		current = move(openList.front()); 
		cout << "current X: " << current->x << " current y: " << current->y << endl;
		openList.pop_front();

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

		//North Node
		if (terrain[current->y + 1][current->x] != 0 && current->y + 1 < maxY) //For each state that can match current
		{
			//i
			//Apply the rule to generate a new state and call it N
			n->x = current->x;
			n->y = current->y + 1;

			//ii
			//current cost = score - heuristic value;
			newCost = (current->score - CalcDistance(current, goal)) + terrain[current->y + 1][current->x]; // beware that current will have the heuristic cost after the first iteration (check if it's not the goal)
			n->score = newCost;
			//iii
			if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //if n is on the open or the closed list
			{
				n->score = newCost + CalcDistance(n, goal);
				//iv
				if (!getNScore(n, openList, closedList)) // if the new cost is not less than the existing cost 
				{
					//v
					if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //If N is on the open or closedList current = n
					{
						n = move(Transfer(n, openList, closedList)); // let n now refer to existing_n
						n->parent = current.get(); //Set the parent of n to current
						n->score = newCost + CalcDistance(n, goal); //Set the score of n to the newcost + heuristic value (calculating the accumulated cost through score so don't need to set the cost)

						//vi
						if (Search(closedList, n->x, n->y)) // If n was on the closedList then remove it from the closedList and push to open
						{
							RemoveN(n, closedList); //if n was on the closedList then remove it
							AddNode(openList, n->x, n->y, n->parent, newCost + CalcDistance(n, goal)); //push N to the openList
						}
					}
				}
			}
			else
			{
				AddNode(openList, n->x, n->y, n->parent, newCost + CalcDistance(n, goal));
				cout << "New node created at " << n->x << " " << n->y << " Score: " << newCost + CalcDistance(n, goal) << endl;
			}
			SortList(openList); //Reorder the openList by score (sort function)
			timesSorted++;
		}

		//East Node
		if (terrain[current->y][current->x + 1] != 0 && current->x + 1 < maxX) //East node
		{
			//i
			//Apply the rule to generate a new state and call it N
			n->x = current->x + 1;
			n->y = current->y;

			//ii
			//current cost = score - heuristic value;
			newCost = current->score - CalcDistance(current, goal) + terrain[current->y][current->x + 1]; // beware that current will have the heuristic cost after the first iteration (check if it's not the goal)

																										  //iii
			if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //if N is on the open or the closed list
			{
				n->score = newCost + CalcDistance(n, goal);
				//iv
				if (!getNScore(n, openList, closedList)) // if the new cost is not less than the existing cost 
				{
					//v
					if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //If N is on the open or closedList current = n
					{
						n = move(Transfer(n, openList, closedList)); // let n now refer to existing_n
						n->parent = current.get(); //Set the parent of n to current
						n->score = newCost + CalcDistance(n, goal); //Set the score of n to the newcost + heuristic value (calculating the accumulated cost through score so don't need to set the cost)

																	//vi
						if (Search(closedList, n->x, n->y)) // If n was on the closedList then remove it from the closedList and push to open
						{
							RemoveN(n, closedList); //if n was on the closedList then remove it
							AddNode(openList, n->x, n->y, n->parent, n->score); //push N to the openList
						}
					}
				}
			}
			else
			{
				AddNode(openList, n->x, n->y, prior, newCost + CalcDistance(n, goal));
				cout << "New node created at " << n->x << " " << n->y << " Score: " << newCost + CalcDistance(n, goal) << endl;
			}
			SortList(openList); //Reorder the openList by score (sort function)
		}

		//South Node
		if (terrain[current->y - 1][current->x] != 0 && current->y - 1 > 0) //South node
		{
			//i
			//Apply the rule to generate a new state and call it N
			n->x = current->x;
			n->y = current->y - 1;

			//ii
			//current cost = score - heuristic value;
			newCost = current->score - CalcDistance(current, goal) + terrain[current->y - 1][current->x]; // beware that current will have the heuristic cost after the first iteration (check if it's not the goal)

																										  //iii
			if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //if N is on the open or the closed list
			{
				n->score = newCost + CalcDistance(n, goal);
				//iv
				if (!getNScore(n, openList, closedList)) // if the new cost is not less than the existing cost 
				{
					//v
					if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //If N is on the open or closedList current = n
					{
						n = move(Transfer(n, openList, closedList)); // let n now refer to existing_n
						n->parent = current.get(); //Set the parent of n to current
						n->score = newCost + CalcDistance(n, goal); //Set the score of n to the newcost + heuristic value (calculating the accumulated cost through score so don't need to set the cost)

																	//vi
						if (Search(closedList, n->x, n->y)) // If n was on the closedList then remove it from the closedList and push to open
						{
							RemoveN(n, closedList); //if n was on the closedList then remove it
							AddNode(openList, n->x, n->y, n->parent, n->score); //push N to the openList
						}
					}
				}
			}
			else
			{
				AddNode(openList, n->x, n->y, prior, newCost + CalcDistance(n, goal));
				cout << "New node created at " << n->x << " " << n->y << " Score: " << newCost + CalcDistance(n, goal) << endl;
			}
			SortList(openList); //Reorder the openList by score (sort function)
		}

		//West Node
		if (terrain[current->y][current->x - 1] != 0 && current->x - 1 > 0) //West node
		{
			//i
			//Apply the rule to generate a new state and call it N
			n->x = current->x - 1;
			n->y = current->y;

			//ii
			//current cost = score - heuristic value;
			newCost = current->score - CalcDistance(current, goal) + terrain[current->y][current->x - 1]; // beware that current will have the heuristic cost after the first iteration (check if it's not the goal)

																										  //iii
			if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //if N is on the open or the closed list
			{
				n->score = newCost + CalcDistance(n, goal);
				//iv
				if (!getNScore(n, openList, closedList)) // if the new cost is not less than the existing cost 
				{
					//v
					if (Search(openList, n->x, n->y) || Search(closedList, n->x, n->y)) //If N is on the open or closedList current = n
					{
						n = move(Transfer(n, openList, closedList)); // let n now refer to existing_n
						n->parent = current.get(); //Set the parent of n to current
						n->score = newCost + CalcDistance(n, goal); //Set the score of n to the newcost + heuristic value (calculating the accumulated cost through score so don't need to set the cost)

																	//vi
						if (Search(closedList, n->x, n->y)) // If n was on the closedList then remove it from the closedList and push to open
						{
							RemoveN(n, closedList); //if n was on the closedList then remove it
							AddNode(openList, n->x, n->y, n->parent, n->score); //push N to the openList
						}
					}
				}
			}
			else
			{
				AddNode(openList, n->x, n->y, prior, newCost + CalcDistance(n, goal)); //if n was not on the open or closedList then push n to openList
				cout << "New node created at " << n->x << " " << n->y << " Score: " << newCost + CalcDistance(n, goal) << endl;
			}
			SortList(openList); //Reorder the openList by score (sort function)
		}

		closedList.push_back(move(current)); // Push current on to the closedList

	}
	return false; //quit if the open list is empty
}
bool CSearchAStar::FindPathRT(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, ModelMap &map, I3DEngine* &myEngine)
{
	return false;
}