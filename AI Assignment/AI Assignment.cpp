// AI Assignment.cpp: A program using the TL-Engine
#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include "SearchFactory.h"
#include "MapIO.h"

using namespace tle;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );
	myEngine->AddMediaFolder("D:\\Users\\tcrosby\\Documents\\GitHub\\AI-pathfinding\\AI Assignment");

	/**** Set up your scene here ****/


	// MENU 
	EInputState currentState;
	bool bRealTime = false;
	bool success;
	int userInput = Menu;
	int userChoice = 1;
	string userMap = "m";

	//**** PATHFINDING ****//
	// ALGORITHM
	ESearchType searchAlgorithm = BreadthFirst;
	ISearch* PathFinder;
	TerrainMap currentMap;
	ModelMap tilesMap;
	unique_ptr<SNode> start(new SNode);
	unique_ptr<SNode> goal(new SNode);
	NodeList path;

	//**** TL ENGINE ****//
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual, 50, 50, -150); 

	SetMap(userMap, currentMap); 
	MapCoordinates(userMap, start, goal);
	
	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		switch(userInput)
		{
		case Menu:
			cout << "Current Map: " << userMap << " Current Algorithm: " << searchAlgorithm << " RealTime " << bRealTime << endl;
			cout << "Select Option" << endl;
			cout << "(1) Choose Map" << endl;
			cout << "(2) Choose Algorithm" << endl;
			cout << "(3) Real Time" << endl;
			cout << "(4) Draw Path" << endl;
			cout << "(5) Exit" << endl;
			cin >> userInput;
			break;
		case ChooseMap:
			cout << "Choose Map" << endl;
			currentMap.clear();
			cin >> userMap;
			SetMap(userMap, currentMap);
			userInput = Menu;
			break;
		case ChooseAlgorithm:
			cout << "Choose Algorithm (1: BreadthFirst / 2: AStar)" << endl;
			cin >> userChoice;
			if (userChoice == 1)
			{
				searchAlgorithm = BreadthFirst;
			}
			if (userChoice == 2)
			{
				searchAlgorithm = AStar;
			}
			userInput = Menu;
			break;
		case RealTime:
			cout << "Show Algorithm in real time (1: Yes/ 2: no)" << endl;
			cin >> userChoice;
			if (userChoice == 1)
			{
				bRealTime = true;
			}
			if (userChoice == 2)
			{
				bRealTime = false;
			}
			userInput = Menu;
			break;
		case ShowPath:
			ResetMap(tilesMap, start, goal, path);
			MapCoordinates(userMap, start, goal);
			InitTLMap(myEngine, currentMap, tilesMap);
			DrawTLMap(myEngine, currentMap, tilesMap);
			PathFinder = NewSearch(searchAlgorithm);
			if (bRealTime)
			{
				success = PathFinder->FindPathRT(currentMap, move(start), move(goal), path, tilesMap, myEngine);
			}
			else
			{
				success = PathFinder->FindPath(currentMap, move(start), move(goal), path);
			}
			
			if (success == true) //change to work with states
			{
				DrawPath(tilesMap, path);
				OutputPath(path);

			}
			else
			{
				cout << "Path not found " << endl;

			}

			userInput = Menu;
			break;
		case Exit:
			myEngine->Stop();
			break;
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
