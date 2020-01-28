#pragma once

#include "SearchAStar.h"
#include "Utilities.h"


bool CSearchAStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path)
{
	NodeList openList;
	NodeList closedList;
	start->score = CalcDistance(start, goal);
	openList.push_back(move(start));
	return false;
}
bool CSearchAStar::FindPathRT(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, ModelMap &map, I3DEngine* &myEngine)
{
	return false;
}