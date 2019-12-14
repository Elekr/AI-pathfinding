// AI Assignment.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "Definitions.h"
#include "Search.h"
#include "SearchFactory.h"

TerrainMap SetMap(string userChoice, TerrainMap &map)
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
		vector<vector<ETerrainCost>>::iterator ptr;
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
	reverse(map.begin(), map.end());
	return map;
	infile.close();
}

void MapCoordinates(string userChoice, unique_ptr<SNode>& start, unique_ptr<SNode>& goal)
{
	string mapName = userChoice;
	mapName.append(COORDS);
	cout << "map file name: " << mapName << endl; //set the file names for the fstream to open

	fstream infile;
	infile.open(mapName); //Opens the file 
	if (!infile) {
		cout << "file not found" << endl;
	}
	else
	{
		infile >> start->x >> start->y >> goal->x >> goal->y;
	}
	infile.close();
}


using namespace tle;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );

	/**** Set up your scene here ****/

	//**** PATHFINDING ****//
	TerrainMap currentMap;
	unique_ptr<SNode> start(new SNode);
	unique_ptr<SNode> goal(new SNode);
	NodeList path;

	SetMap("d", currentMap); // USER INPUT FOR SETTING MAP
	MapCoordinates("d", start, goal); // MAKE PART OF SET MAP?

	ISearch* PathFinder = NewSearch(BreadthFirst);	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << currentMap[i][j];
		}
		cout << endl;
	}
	cout << currentMap[6][2] << endl;	bool success = PathFinder->FindPath(currentMap, move(start), move(goal), path);



	//**** TL ENGINE ****//
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kFPS, 50, 50, -150); //half of max X, half of max Y, -100
	
	IModel* quad;
	IMesh* quadMesh = myEngine->LoadMesh("quad.x"); //Model set up for the tiles in the maze

	for (int i = 0; i < 10; i++) //TODO change to iterator to support dynamic map size
	{
		for (int j = 0; j < 10; j++)
		{
			switch (currentMap[i][j])
			{
			case(Wall):
				quad = quadMesh->CreateModel(j*10, i*10, 0);
				quad->SetSkin(WALL);
				break;
			case(Clear):
				quad = quadMesh->CreateModel(j*10, i*10, 0);
				quad->SetSkin(CLEAR);
				break;
			case(Water):
				quad = quadMesh->CreateModel(j * 10, i * 10, 0);
				quad->SetSkin(WATER);
				break;
			case(Wood):
				quad = quadMesh->CreateModel(j * 10, i * 10, 0);
				quad->SetSkin(WOOD);
				break;
			}
		}
	}


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/

		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
