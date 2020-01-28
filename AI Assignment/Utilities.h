#pragma once

#include "Definitions.h"

using namespace std;

void AddNode(deque<unique_ptr<SNode>>& myList, int xValue, int yValue, SNode* current);

void Display(deque<unique_ptr<SNode>>& myList);

bool Search(deque<unique_ptr<SNode>>& myList, int xValue, int yValue);

void MoveNodes(deque<unique_ptr<SNode>>& myList1, deque<unique_ptr<SNode>>& myList2);

void Raw(SNode* t);

unique_ptr<SNode> Transfer(unique_ptr <SNode> t);

int CalcDistance(unique_ptr<SNode> &current, unique_ptr<SNode> &goal);