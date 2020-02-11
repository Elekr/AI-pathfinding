#pragma once

#include "SearchBreadthFirst.h"
#include "Utilities.h"
#include <sstream>



bool CSearchBreadthFirst::FindPath(TerrainMap &terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList &path) //SEND OVER AN ARRAY OF MODELS TO UPDATE WHEN SHIT HAPPENS
{
	int maxY = terrain.size() - 1; //used to check that the pointer stays within the vector
	int maxX = terrain[0].size() - 1;

	NodeList openList;
	NodeList closedList;
	unique_ptr<SNode> current(new SNode);
	SNode* prior = current.get();
	SNode* path1;
	openList.push_back(move(start)); //push initial state onto open list

	while (!openList.empty()) // until goal state is found or openlist is empty
	{
		current = move(openList.front()); // pop first element 
		openList.pop_front();
		prior = current.get();

		if (terrain[current->y + 1][current->x] != 0 && current->y + 1 < maxY) //North node CHECK IF NULL BECAUSE OUT OF BOUNDS OF THE VECTOR WOULD BE NULL IF THERE'S NO WALLS function
		{
			if (!Search(closedList, current->x, current->y + 1) && !Search(openList, current->x, current->y + 1)) //check that the node isn't already on the open/closed list to stop duplication
			{
				AddNode(openList, current->x, current->y + 1, prior, 0);
			}
		}

		if (terrain[current->y][current->x + 1] != 0 && current->x + 1 < maxX) //East node
		{
			if (!Search(closedList, current->x + 1, current->y) && !Search(openList, current->x + 1, current->y))
			{
				AddNode(openList, current->x + 1, current->y, prior, 0);
			}
		}

		if (terrain[current->y - 1][current->x] != 0 && current->y - 1 > 0) //South node
		{
			if (!Search(closedList, current->x, current->y - 1) && !Search(openList, current->x, current->y - 1))
			{
				AddNode(openList, current->x, current->y - 1, prior, 0);
			}
		}

		if (terrain[current->y][current->x - 1] != 0 && current->x - 1 > 0) //West node
		{
			if (!Search(closedList, current->x - 1, current->y) && !Search(openList, current->x - 1, current->y))
			{
				AddNode(openList, current->x - 1, current->y, prior, 0);
			}
		}
		//cout << current->x << " " << current->y << endl;

		if (current->x == goal->x && current->y == goal->y)
		{
			path1 = current.get();
			while (path1 != 0)
			{
				AddNode(path, path1->x, path1->y, 0, 0);
				//cout << path1->x << " " << path1->y << endl;
				path1 = path1->parent;
			}

			return true;
		}
		closedList.push_back(move(current));
	}
	return false;
}

bool CSearchBreadthFirst::FindPathRT(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, ModelMap& map, I3DEngine* &myEngine)
{
	//**** TL ENGINE
	IFont* myFont = myEngine->LoadFont("Comic Sans MS", 36);
	float timePassed = 0.0f;
	//**** PATHFINDING
	NodeList openList;
	NodeList closedList;
	unique_ptr<SNode> current(new SNode);
	SNode* prior = current.get();
	SNode* returnPath;
	openList.push_back(move(start)); //push initial state onto open list
	int maxY = terrain.size() - 1; //used to check that the pointer stays within the vector
	int maxX = terrain[0].size() - 1;



	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		float frameTime = myEngine->Timer();
		//**** Output Text
		stringstream outText;
		outText << "Frame Time: " << frameTime;
		myFont->Draw(outText.str(), 0, 0, kBlack);
		outText.str("");
		outText << "timePassed " << timePassed;
		myFont->Draw(outText.str(), 0, 30, kBlack);

		if (!openList.empty()) // until goal state is found or openlist is empty
		{


			current = move(openList.front()); // pop first element 
			openList.pop_front();

			if (current->x == goal->x && current->y == goal->y)
			{
				returnPath = current.get();
				while (returnPath != 0)
				{
					AddNode(path, returnPath->x, returnPath->y, 0, 0);
					//cout << path1->x << " " << path1->y << endl;
					returnPath = returnPath->parent;
				}

				return true;
			}

			prior = current.get();

			if (current->y != maxY)
			{
				if (terrain[current->y + 1][current->x] != 0) //North node not a wall and inbounds
				{
					if (!Search(closedList, current->x, current->y + 1) && !Search(openList, current->x, current->y + 1)) //check that the node isn't already on the open/closed list to stop duplication
					{
						cout << "North node added" << endl;
						AddNode(openList, current->x, current->y + 1, prior, 0);
					}
				}
			}

			if (current->x != maxX)
			{
				if (terrain[current->y][current->x + 1] != 0) //East node
				{
					if (!Search(closedList, current->x + 1, current->y) && !Search(openList, current->x + 1, current->y))
					{
						cout << "East node added" << endl;
						AddNode(openList, current->x + 1, current->y, prior, 0);
					}
				}
			}

			if (current->y != 0)
			{
				if (terrain[current->y - 1][current->x] != 0 && current->y - 1 >= 0) //South node
				{
					if (!Search(closedList, current->x, current->y - 1) && !Search(openList, current->x, current->y - 1))
					{
						cout << "South node added" << endl;
						AddNode(openList, current->x, current->y - 1, prior, 0);
					}
				}
			}

			if (current->x != 0)
			{
				if (terrain[current->y][current->x - 1] != 0 && current->x - 1 >= 0) //West node
				{
					if (!Search(closedList, current->x - 1, current->y) && !Search(openList, current->x - 1, current->y))
					{
						cout << "West node added" << endl;
						AddNode(openList, current->x - 1, current->y, prior, 0);
					}
				}
			}
		}

		
		//DRAW THE OPEN AND CLOSED LIST
			for (auto it = openList.begin(); it != openList.end(); ++it)
			{
				
				while (timePassed < 0.5f)
				{
					timePassed += myEngine->Timer() * 100;
				}
				map[(*it)->y][(*it)->x]->SetSkin("yellow.png");
				timePassed = 0.0f;
			}
			closedList.push_back(move(current));

			for (auto it = closedList.begin(); it != closedList.end(); ++it)
			{
				while (timePassed < 0.5f)
				{
					timePassed += myEngine->Timer() * 100;
				}

				map[(*it)->y][(*it)->x]->SetSkin("purple.png");
				timePassed = 0.0f;
			}

	}

	if (myEngine->KeyHit(Key_Escape))
	{
		myEngine->Stop();
		return 0;
	}
	return false;
}
