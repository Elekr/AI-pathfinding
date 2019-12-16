#pragma once

#include "SearchBreadthFirst.h"
#include "Utilities.h"

bool CSearchBreadthFirst::FindPath(TerrainMap &terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList &path) //SEND OVER AN ARRAY OF MODELS TO UPDATE WHEN SHIT HAPPENS
{
	int maxY = terrain.size() - 1; //used to check that the pointer stays within the vector
	int maxX = terrain[0].size() - 1;

	NodeList openList;
	NodeList closedList;
	unique_ptr<SNode> current (new SNode);
	SNode* prior = current.get();
	SNode* path1;
	openList.push_back(move(start)); //push initial state onto open list

	while (!openList.empty()) // until goal state is found or openlist is empty
	{
		 current = move(openList.front()); // pop first element 
		 prior = current.get();
		 openList.pop_front();

		 if (terrain[current->y + 1][current->x] != 0 && current->y + 1 < maxY) //North node CHECK IF NULL BECAUSE OUT OF BOUNDS OF THE VECTOR WOULD BE NULL IF THERE'S NO WALLS function
		 {
			 if ( !Search(closedList, current->x, current->y + 1) && !Search(openList, current->x, current->y + 1)) //check that the node isn't already on the open/closed list to stop duplication
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
		 //cout << current->x << " " << current->y << endl;

		 if (current->x == goal->x && current->y == goal->y)
		 {
			 path1 = current.get();
			 while (path1 != 0)
			 {
				 AddNode(path, path1->x, path1->y, 0);
				 //cout << path1->x << " " << path1->y << endl;
				 path1 = path1->parent;
			 }

			 return true;
		 }
		 closedList.push_back(move(current));
	}
	return false;
}
