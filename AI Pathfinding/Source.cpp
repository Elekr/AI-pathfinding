
#include <memory>
#include <iostream>
#include <deque>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string MAP = "Map.txt";
const string COORDS = "coords.txt";

enum ETerrainCost
{
	Clear = 1,
	Water = 2,
	Wood = 3,
	Wall = 0
};

using TerrainMap = vector<vector<ETerrainCost>>;

struct coords
{
	int x;
	int y;
	coords* parent = 0; //Linked List for path
};

using NodeList = deque<unique_ptr<coords>>;

void AddNode(deque<unique_ptr<coords>>& myList, int xValue, int yValue)
{
	unique_ptr <coords> tmpNode(new coords);
	tmpNode->x = xValue;
	tmpNode->y = yValue;
	myList.push_back(move(tmpNode));
}

void Display(deque<unique_ptr<coords>>& myList)
{
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		cout << (*it)->x << " " << (*it)->y << endl;
	}
	cout << endl;
	//for (auto& elt : myList)
	//{
	//	cout << elt->x << " " << elt->y << endl;
	//}
}

void Search(deque<unique_ptr<coords>>& myList, int xValue, int yValue)
{
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		if (xValue == (*it)->x && yValue == (*it)->y)
		{
			cout << "node exists" << endl;
		}
	}
}

void MoveNodes(deque<unique_ptr<coords>>& myList1, deque<unique_ptr<coords>>& myList2)
{
	for (auto it = myList1.begin(); it != myList1.end(); ++it)
	{
		myList2.push_back(move((*it)));
	}
}

void Raw(coords* t)
{
	cout << "Raw output " <<  t->x << " " << t->y << endl << endl;
}

unique_ptr<coords> Transfer(unique_ptr <coords> t)
{
	cout << "Node current values " << t->x << " " << t->y << endl;
	t->x = 2;
	t->y = 5;
	return std::move(t); //moves ownership back to the passed node so that it is out of scope
}

TerrainMap SetMap(string userChoice, TerrainMap map)
{
	string mapName = userChoice;
	mapName.append(MAP);
	cout << "map file name: " << mapName << endl; //set the file names for the fstream to open

	fstream infile;
	infile.open(mapName); //Opens the file 
	if (!infile) {
		cout << "file not found" << endl;
	}
	else
	{
		int arrayX;
		int arrayY;
		char currentChar;
		infile >> arrayX >> arrayY;
		vector<ETerrainCost> row;
		//TODO get the starting and goal node locations 
		cout << "arrayX: " << arrayX << " arrayY: " << arrayY << endl; //Get the size of the map 
		//TODO 
		for (int i = 0; i < arrayY; i++)
		{
			for (int j = 0; j < arrayX; j++)
			{
				infile >> currentChar;
				int currentNumber = currentChar - '0';
				switch (currentNumber)
				{
				case(Wall):
					cout << "0";
					row.push_back(Wall);
					break;
				case(Clear):
					cout << "1";
					row.push_back(Clear);
					break;
				case(Water):
					cout << "2";
					row.push_back(Water);
					break;
				case(Wood):
					cout << "3";
					row.push_back(Wood);
					break;
				}
			}
			map.push_back(row);
			row.clear();
			cout << endl;
		}

		cout << endl;
	}
	return map;
	infile.close();
}

void setStartGoal(string userChoice)
{
	string coordsName = userChoice;
	coordsName.append(COORDS);
	cout << "coords file name: " << coordsName << endl; //set the file names for the fstream to open

	fstream infile;
	infile.open(coordsName);
	if (!infile) {
		cout << "file not found" << endl;
	}
	else
	{

	}
	infile.close();
}

int main()
{
	//unique_ptr <coords> ptr1(new coords);
	//ptr1->x = 4;
	//ptr1->y = 7;

	//cout << ptr1->x << endl;
	//cout << ptr1->y << endl;

	//unique_ptr <coords> ptr1(new coords);
	//unique_ptr <coords> ptr2(new coords);

	//ptr1->x = 3;
	//ptr1->y = 9;

	//ptr2 = move(ptr1);

	//cout << ptr2->x << endl;
	//cout << ptr2->y << endl;

	//unique_ptr <coords> tmp(new coords);

	//tmp->x = 4; // x co-ordinate of the start
	//tmp->y = 4; // y co-ordinate of the start

	//**** EXERCISE 3 ****//
	//deque <unique_ptr <coords> > openList;
	//unique_ptr <coords> currentNode (new coords);

	//currentNode->x = 5;
	//currentNode->y = 7;
	//openList.push_back(move(currentNode));
	//cout << openList.front()->x << endl;
	//cout << openList.front()->y << endl;

	//unique_ptr <coords> tmpNode;
	//tmpNode = (move(openList.front()));
	//openList.pop_front();
	//cout << tmpNode->x << endl;
	//cout << tmpNode->y << endl;

	//****EXERCISE 4 ****//
	//deque <unique_ptr <coords> > openList;  //creates a unique pointer to a list of nodes
	//unique_ptr <coords> tmpNode (new coords); //tmp node to push nodes onto the list
	//for (int i = 0; i < 10; i++)
	//{
	//	tmpNode->x = i;  //Set the values of the node
	//	tmpNode->y = i * 2;
	//	openList.push_back(move(tmpNode));  //move the node onto the list
	//	tmpNode.reset(new coords); //reset the temp node with new memory
	//}
	//Display(openList);
	//Search(openList, 5, 5);

	//****EXERCISE 5 ****//
	//deque <unique_ptr <coords>> List;
	//unique_ptr <coords> tempNode(new coords);
	//AddNode(List, 5, 7);
	//Display(List);
	//cout << List.front()->x << " " << List.front()->y << endl;
	//cout << List.back()->x << " " << List.back()->y << endl;

	//deque <unique_ptr <coords> > openList;
	//for (int i = 0; i < 10; i++)
	//{
	//	AddNode(openList, i, i * 2);
	//}

	//Display(openList);

	//deque <unique_ptr <coords> > closedList;
	//unique_ptr <coords> currentNode(new coords);

	//MoveNodes(openList, closedList);
	//Display(closedList);
	//Raw(closedList.front().get());
	//currentNode = Transfer(move(closedList.front()));
	//cout << "Node new values " <<  currentNode->x << " " << currentNode->y << endl;

	//****BREADTH FIRST DEQUE****//
	TerrainMap currentMap;

	NodeList openList;
	NodeList closedList;

	currentMap = SetMap("m", currentMap);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << currentMap[i][j];
		}
		cout << endl;
	}

	system("pause");

};