#pragma once

#include "Search.h"       // Base (=interface) class definition

class CSearchBreadthFirst : public ISearch
{
	bool FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path);
};