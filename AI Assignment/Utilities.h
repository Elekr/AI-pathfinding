#pragma once

#include "Definitions.h"

using namespace std;

void AddNode(NodeList& myList, int xValue, int yValue, SNode* current, int score);

void Display(NodeList& myList);

bool Search(NodeList& myList, int xValue, int yValue);

void MoveNodes(NodeList& myList1, NodeList& myList2);

void Raw(SNode* t);

unique_ptr<SNode> Transfer(unique_ptr<SNode> &n, NodeList &openList, NodeList &closedList);

int CalcDistance(unique_ptr<SNode> &current, unique_ptr<SNode> &goal);

bool getNScore(unique_ptr<SNode> &n, NodeList &openList, NodeList &closedList);

void RemoveN(unique_ptr<SNode> &n, NodeList &closedList);

void SortList(NodeList &openList);

bool CompareScore(unique_ptr<SNode> &node1, unique_ptr<SNode> &node2);