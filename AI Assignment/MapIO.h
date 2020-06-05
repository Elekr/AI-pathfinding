#pragma once

#include "Definitions.h"
#include <TL-Engine.h>

using namespace tle;

TerrainMap SetMap(string userChoice, TerrainMap &map);

void MapCoordinates(string userChoice, unique_ptr<SNode>& start, unique_ptr<SNode>& goal);

void InitTLMap(I3DEngine* &myEngine, TerrainMap currentMap, ModelMap &tilesMap);

void DrawTLMap(I3DEngine* &myEngine, TerrainMap currentMap, ModelMap &tilesMap);

void DrawPath(ModelMap &tilesMap, NodeList &path);

void OutputPath(NodeList & path, string userMap);

void DisplayVector(TerrainMap currentMap);

void DisplayPath(NodeList &path);

void ResetMap(ModelMap &tilesMap, unique_ptr<SNode> &start, unique_ptr<SNode> &goal, NodeList &path);