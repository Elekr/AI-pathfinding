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

	EInputState currentState;
	//**** PATHFINDING ****//
	//SETUP
	TerrainMap currentMap;
	unique_ptr<SNode> start(new SNode);
	unique_ptr<SNode> goal(new SNode);
	NodeList path;
	int userInput = Menu;

	string userMap = "d";

	ESearchType searchAlgorithm = BreadthFirst;
	bool bRealTime = false;

	//SEARCH FUNCTION
	ISearch* PathFinder = NewSearch(searchAlgorithm);

	//**** TL ENGINE ****//

	
	ModelMap tilesMap;
	ICamera* myCamera;
	SetMap(userMap, currentMap); // USER INPUT FOR SETTING MAP
	MapCoordinates(userMap, start, goal);
	myCamera = myEngine->CreateCamera(kManual, 50, 50, -150); //half of max X, half of max Y, -150
	TLMap(myEngine, currentMap, tilesMap);


	bool success = PathFinder->FindPathRT(currentMap, move(start), move(goal), path, tilesMap, myEngine);
	//bool success = PathFinder->FindPath(currentMap, move(start), move(goal), path);
	//bool success = false;
	
	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		//switch(userInput)
		//{
		//case Menu:
		//	cout << "Current Map: " << userMap << " Current Algorithm: " << searchAlgorithm << " RealTime " << bRealTime << endl;
		//	cout << "Select Option" << endl;
		//	cout << "(1) Choose Map" << endl;
		//	cout << "(2) Choose Algorithm" << endl;
		//	cout << "(3) Real Time" << endl;
		//	cin >> userInput;
		//	break;
		//case ChooseMap:
		//	cout << "Choose Map" << endl;

		//	cin >> userMap;
		//	SetMap(userMap, currentMap); // USER INPUT FOR SETTING MAP
		//	MapCoordinates(userMap, start, goal);
		//	currentState = Menu;
		//	break;
		//case ChooseAlgorithm:
		//	cout << "Choose Algorithm" << endl;
		//	break;
		//case ShowPath:
		//	break;
		//case PathError:
		//	break;
		//case RealTime:
		//	break;

		//}
		//CHOOSE MAP
		//CHOOSE ALGORITHM STATE
		//ALGORITHM LOOP

		//PATHFINDING AND DRAWING PATH
		if (success == true) //change to work with states
		{
			DrawPath(tilesMap, path);
			OutputPath(path);
		}
		//else
		//{

		//}
		//success = false;

		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
