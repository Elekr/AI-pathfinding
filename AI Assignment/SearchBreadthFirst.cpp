#pragma once

#include "SearchBreadthFirst.h"
#include "Utilities.h"

bool CSearchBreadthFirst::FindPath(TerrainMap &terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList & path) //SEND OVER AN ARRAY OF MODELS TO UPDATE WHEN SHIT HAPPENS
{
	cout << "search function is being called" << endl;

	NodeList openList;
	NodeList closedList;
	unique_ptr<SNode> current (new SNode);

	openList.push_back(move(start)); //push initial state onto open list
	while (!openList.empty()) // until goal state is found or openlist is empty
	{
		 current = move(openList.front()); // pop first element 
		 openList.pop_front();

		 if (terrain[current->y + 1][current->x] != 0) //North node CHECK IF NULL BECAUSE OUT OF BOUNDS OF THE VECTOR WOULD BE NULL IF THERE'S NO WALLS
		 {
			 if ( !Search(closedList, current->x, current->y + 1)) 
			 {
				 AddNode(openList, current->x, current->y + 1, 0, current.get());
			 }
		 }

		 if (terrain[current->y][current->x + 1] != 0) //East node
		 {
			 if (!Search(closedList, current->x + 1, current->y))
			 {
				AddNode(openList, current->x + 1, current->y, 0, current.get());
			 }
		 }

		 if (terrain[current->y - 1][current->x] != 0) //South node
		 {
			 if (!Search(closedList, current->x, current->y - 1))
			 {
				 AddNode(openList, current->x, current->y - 1, 0, current.get());
			 }
		 }

		 if (terrain[current->y][current->x - 1] != 0) //West node
		 {
			 if (!Search(closedList, current->x - 1, current->y))
			 {
				 AddNode(openList, current->x - 1, current->y, 0, current.get());
			 }
		 }
		 cout << current->x << " " << current->y << endl;

		 if (current->x == goal->x && current->y == goal->y)
		 {
			 return true;
		 }
		 closedList.push_back(move(current));
	}
	return false;
}
