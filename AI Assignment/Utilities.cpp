#pragma once

#include "Utilities.h"

void AddNode(deque<unique_ptr<SNode>>& myList, int xValue, int yValue, SNode* current)
{
	unique_ptr <SNode> tmpNode(new SNode);
	tmpNode->x = xValue;
	tmpNode->y = yValue;
	tmpNode->parent = current;
	myList.push_back(move(tmpNode));
}

void Display(deque<unique_ptr<SNode>>& myList)
{
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		cout << (*it)->x << " " << (*it)->y << endl;
	}
	cout << endl;
}

bool Search(deque<unique_ptr<SNode>>& myList, int xValue, int yValue)
{
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		if (xValue == (*it)->x && yValue == (*it)->y)
		{
			return true;
		}
	}
	return false;

}

void MoveNodes(deque<unique_ptr<SNode>>& myList1, deque<unique_ptr<SNode>>& myList2)
{
	for (auto it = myList1.begin(); it != myList1.end(); ++it)
	{
		myList2.push_back(move((*it)));
	}
}

void Raw(SNode* t)
{
	cout << "Raw output " << t->x << " " << t->y << endl << endl;
}

unique_ptr<SNode> Transfer(unique_ptr <SNode> t)
{
	cout << "Node current values " << t->x << " " << t->y << endl;
	t->x = 1;
	t->y = 2;
	return std::move(t); //moves ownership back to the passed node so that it is out of scope
}

int CalcDistance(unique_ptr<SNode> &current, unique_ptr<SNode> &goal)
{

	int dx = abs(goal->x - current->x);
	int dy = abs(goal->y - current->y);
	return dx + dy;
}