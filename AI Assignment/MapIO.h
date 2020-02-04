#pragma once

#include "Definitions.h"
#include <TL-Engine.h>

using namespace tle;

//TODO: create class to store these
TerrainMap SetMap(string userChoice, TerrainMap &map);

void MapCoordinates(string userChoice, unique_ptr<SNode>& start, unique_ptr<SNode>& goal);

void TLMap(I3DEngine* &myEngine, TerrainMap currentMap, ModelMap &tilesMap);

void DrawPath(ModelMap &tilesMap, NodeList &path);

void DisplayVector(TerrainMap currentMap);

void DisplayPath(NodeList &path);
