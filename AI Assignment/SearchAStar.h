#pragma once

#include "Search.h"       // Base (=interface) class definition

class CSearchAStar : public ISearch
{
	bool FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path);
	bool FindPathRT(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, ModelMap &map, I3DEngine* &myEngine);
};