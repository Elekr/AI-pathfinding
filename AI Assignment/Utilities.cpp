#pragma once


#include "Utilities.h"

void AddNode(NodeList& myList, int xValue, int yValue, SNode* current, int score)
{
	unique_ptr <SNode> tmpNode(new SNode);
	tmpNode->x = xValue;
	tmpNode->y = yValue;
	tmpNode->parent = current;
	tmpNode->score;
	myList.push_back(move(tmpNode));
}

void Display(NodeList& myList)
{
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		cout << (*it)->x << " " << (*it)->y << endl;
	}
	cout << endl;
}

bool Search(NodeList& myList, int xValue, int yValue)
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

void MoveNodes(NodeList& myList1, NodeList& myList2)
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

unique_ptr<SNode> Transfer(unique_ptr<SNode> &n, NodeList &openList, NodeList &closedList)
{

	for (auto it = openList.begin(); it != openList.end(); ++it)
	{
		if (n->x == (*it)->x && n->y == (*it)->y) // if it's on the list
		{
			if (n->score >= (*it)->score) // if the the newcost  >= existing_n cost
			{
				return std::move(*it);
			}
		}
	}

	for (auto it = closedList.begin(); it != closedList.end(); ++it)
	{
		if (n->x == (*it)->x && n->y == (*it)->y) // if it's on the list
		{
			if (n->score >= (*it)->score) // if the the newcost  >= existing_n cost
			{
				return std::move(*it);
			}
		}
	}

}

int CalcDistance(unique_ptr<SNode> &current, unique_ptr<SNode> &goal)
{

	int dx = abs(goal->x - current->x);
	int dy = abs(goal->y - current->y);
	return dx + dy;
}

void SortList(NodeList list)
{

}

bool getNScore(unique_ptr<SNode> &n, NodeList &openList, NodeList &closedList)
{
	for (auto it = openList.begin(); it != openList.end(); ++it)
	{
		if (n->x == (*it)->x && n->y == (*it)->y) // if it's on the list
		{
			if (n->score >= (*it)->score) // if the the newcost  >= existing_n cost
			{
				return true;
			}
			else // continue
			{
				false;
			}
		}
	}

	for (auto it = closedList.begin(); it != closedList.end(); ++it)
	{
		if (n->x == (*it)->x && n->y == (*it)->y) // if it's on the list
		{
			if (n->score >= (*it)->score) // if the the newcost  >= existing_n cost
			{
				return true;
			}
			else // continue
			{
				return false;
			}
		}
	}
}