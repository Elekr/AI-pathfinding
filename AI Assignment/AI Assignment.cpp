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

	/**** Set up your scene here ****/

	//**** PATHFINDING ****//
	//SETUP
	TerrainMap currentMap;
	unique_ptr<SNode> start(new SNode);
	unique_ptr<SNode> goal(new SNode);
	NodeList path;
	string userInput = "d";
	string search;

	//LOAD
	SetMap(userInput, currentMap); // USER INPUT FOR SETTING MAP
	MapCoordinates(userInput, start, goal); // MAKE PART OF SET MAP?
	DisplayVector(currentMap);

	//SEARCH FUNCTION
	ISearch* PathFinder = NewSearch(BreadthFirst);

	//bool success = PathFinder->FindPath(currentMap, move(start), move(goal), path); // NOT REAL TIME

	//DisplayPath(path);

	//**** TL ENGINE ****//

	
	ModelMap tilesMap;
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual, 50, 50, -150); //half of max X, half of max Y, -150
	TLMap(myEngine, currentMap, tilesMap);

	//PATHFINDING AND DRAWING PATH
	bool success = PathFinder->FindPathRT(currentMap, move(start), move(goal), path, tilesMap, myEngine);
	DrawPath(tilesMap, path);

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		//CHOOSE MAP
		//CHOOSE ALGORITHM STATES
		//ALGORITHM LOOP


		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
