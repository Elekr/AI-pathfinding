
#include "MapIO.h"

TerrainMap SetMap(string userChoice, TerrainMap &map)
{
	string mapName = userChoice;
	mapName.append(MAP);

	fstream infile;
	infile.open(mapName); //Opens the file 
	if (!infile)
	{
		cout << "file not found" << endl;
	}
	else
	{
		int arrayX;
		int arrayY;
		char currentChar;
		infile >> arrayX >> arrayY;
		vector<ETerrainCost> row;

		for (int i = 0; i < arrayY; i++)
		{
			for (int j = 0; j < arrayX; j++)
			{
				infile >> currentChar;
				int currentNumber = currentChar - '0';
				switch (currentNumber)
				{
				case(Wall):
					row.push_back(Wall);
					break;
				case(Clear):
					row.push_back(Clear);
					break;
				case(Water):
					row.push_back(Water);
					break;
				case(Wood):
					row.push_back(Wood);
					break;
				}
			}
			map.push_back(row);
			row.clear();
		}
	}
	reverse(map.begin(), map.end());
	return map;
	infile.close();
}

void MapCoordinates(string userChoice, unique_ptr<SNode>& start, unique_ptr<SNode>& goal)
{
	unique_ptr<SNode> tmp1(new SNode);
	unique_ptr<SNode> tmp2(new SNode);
	string mapName = userChoice;
	mapName.append(COORDS);

	fstream infile;
	infile.open(mapName); //Opens the file 
	if (!infile)
	{
		cout << "file not found" << endl;
	}
	else
	{
		infile >> tmp1->x >> tmp1->y >> tmp2->x >> tmp2->y;
		start = move(tmp1);
		goal = move(tmp2);
	}
	infile.close();
}

void InitTLMap(I3DEngine* &myEngine, TerrainMap currentMap, ModelMap &tilesMap)
{
	vector<IModel*> row;
	IMesh* quadMesh = myEngine->LoadMesh("quad.x"); //Model set up for the tiles in the maze
	for (int i = 0; i < currentMap.size(); i++) //TODO change to iterator to support dynamic map size
	{
		for (int j = 0; j < currentMap[0].size(); j++)
		{
			switch (currentMap[i][j])
			{
			case(Wall):
				row.push_back(quadMesh->CreateModel(j * 10, i * 10, 0));
				row[j]->SetSkin(CLEAR);
				break;
			case(Clear):
				row.push_back(quadMesh->CreateModel(j * 10, i * 10, 0));
				row[j]->SetSkin(CLEAR);
				break;
			case(Water):
				row.push_back(quadMesh->CreateModel(j * 10, i * 10, 0));
				row[j]->SetSkin(CLEAR);
				break;
			case(Wood):
				row.push_back(quadMesh->CreateModel(j * 10, i * 10, 0));
				row[j]->SetSkin(CLEAR);
				break;
			}
		}
		tilesMap.push_back(row);
		row.clear();
	}
}

void DrawTLMap(I3DEngine* &myEngine, TerrainMap currentMap, ModelMap &tilesMap)
{
	for (int i = 0; i < currentMap.size(); i++)
	{
		for (int j = 0; j < currentMap[0].size(); j++)
		{
			switch (currentMap[i][j])
			{
			case(Wall):
				tilesMap[i][j]->SetSkin(WALL);
				break;
			case(Clear):
				tilesMap[i][j]->SetSkin(CLEAR);
				break;
			case(Water):
				tilesMap[i][j]->SetSkin(WATER);
				break;
			case(Wood):
				tilesMap[i][j]->SetSkin(WOOD);
				break;
			}
		}
	}
}

void DrawPath(ModelMap &tilesMap, NodeList &path)
{
	for (auto it = path.begin(); it != path.end(); ++it) //Outputs the path
	{
		tilesMap[(*it)->y][(*it)->x]->SetSkin(PATH);
	}
}

void OutputPath(NodeList & path)
{
	ofstream output ("output.txt");
	for (auto it = path.rbegin(); it != path.rend(); ++it) //Outputs the path
	{
		output << (*it)->x << " " << (*it)->y << endl;
	}
	output.close();
}

void DisplayVector(TerrainMap currentMap)
{
	cout << "Vector output: " << endl;
	for (int i = 0; i < currentMap.size(); i++) //Output the enum vector
	{
		for (int j = 0; j < currentMap[0].size(); j++)
		{
			cout << currentMap[i][j];
		}
		cout << endl;
	}

	cout << endl;
}

void DisplayPath(NodeList &path)
{
	cout << "Path output: " << endl;
	for (auto it = path.rbegin(); it != path.rend(); ++it) //Outputs the path
	{
		cout << (*it)->y << " " << (*it)->x << endl;
	}
	cout << endl;
}

void ResetMap(ModelMap &tilesMap, unique_ptr<SNode> &start, unique_ptr<SNode> &goal)
{
	goal.reset();
	start.reset();
	for (int i = 0; i < tilesMap.size(); i++)
	{
		for (int j = 0; j < tilesMap[i].size(); j++)
		{
			//figure out how to delete the model
		}
	}
}
