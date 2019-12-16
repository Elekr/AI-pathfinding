// Definitions.h
// =============
//
// Type definitions to support path finding 
//
#pragma once

#include <vector>
#include <deque>
#include <memory>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

const string MAP = "Map.txt";
const string COORDS = "coords.txt";
const string WATER = "blue.png";
const string WOOD = "green.png";
const string CLEAR = "grey.png";
const string WALL = "black.png";
const string PATH = "red.png";

// Represents a node in the search tree.-
struct SNode //Declare a deque list of these for the open and closed lists
{
  int x;            // x coordinate
  int y;            // y coordinate
  int score;        // used in more complex algorithms
  SNode* parent = 0; // note use of raw pointer here
};

// Lists of nodes (e.g Open, Closed and Paths) are implemented as double-ended queues
using NodeList = deque<unique_ptr<SNode>>;

// Terrain costs for map squares
enum ETerrainCost
{
  Clear = 1,
  Water = 2,
  Wood  = 3,
  Wall  = 0
};

// Maps of any size are implemented as 2D vectors
using TerrainMap = vector<vector<ETerrainCost>>;