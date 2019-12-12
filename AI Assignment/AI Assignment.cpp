// AI Assignment.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "Definitions.h"
#include "Search.h"
#include "SearchFactory.h"
#include "SearchNoStar.h"



const string MAP = "Map.txt";
const string COORDS = "coords.txt";
const string WATER = "blue.jpg";
const string WOOD = "green.jpg";
const string CLEAR = "bottom.jpg";
const string WALL = "purple.jpg";

void AddNode(deque<unique_ptr<SNode>>& myList, int xValue, int yValue)
{
	unique_ptr <SNode> tmpNode(new SNode);
	tmpNode->x = xValue;
	tmpNode->y = yValue;
	myList.push_back(move(tmpNode));
}

void Display(deque<unique_ptr<SNode>>& myList)
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

void Search(deque<unique_ptr<SNode>>& myList, int xValue, int yValue)
{
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		if (xValue == (*it)->x && yValue == (*it)->y)
		{
			cout << "node exists" << endl;
		}
	}
}

void MoveNodes(deque<unique_ptr<SNode>>& myList1, deque<unique_ptr<SNode>>& myList2)
{
	for (auto it = myList1.begin(); it != myList1.end(); ++it)
	{
		myList2.push_back(move((*it)));
	}
}

void Raw(SNode* t)
{
	cout << "Raw output " << t->x << " " << t->y << endl << endl;
}

unique_ptr<SNode> Transfer(unique_ptr <SNode> t)
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


using namespace tle;

TerrainMap currentMap;

NodeList openList;
NodeList closedList;

class Tile
{
public:
	IModel* cube;
	SNode tileNode;
	Tile();
	~Tile();
};

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	/**** Set up your scene here ****/

	IMesh* cubeMesh;

	cubeMesh = myEngine->LoadMesh("Cube.x");

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
