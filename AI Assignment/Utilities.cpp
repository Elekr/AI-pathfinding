#pragma once


#include "Utilities.h"

void AddNode(NodeList& myList, int xValue, int yValue, SNode* current, int score)
{
	unique_ptr <SNode> tmpNode(new SNode);
	tmpNode->x = xValue;
	tmpNode->y = yValue;
	tmpNode->parent = current;
	tmpNode->score = score;
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
	if (!myList.empty())
	{
		for (auto it = myList.begin(); it != myList.end(); ++it)
		{
			if (xValue == (*it)->x && yValue == (*it)->y)
			{
				return true;
			}
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
			return std::move(*it);
		}
	}

	for (auto it = closedList.begin(); it != closedList.end(); ++it)
	{
		if (n->x == (*it)->x && n->y == (*it)->y) // if it's on the list
		{
			return std::move(*it);
		}
	}

}

int CalcDistance(unique_ptr<SNode> &current, unique_ptr<SNode> &goal)
{

	int dx = abs(goal->x - current->x);
	int dy = abs(goal->y - current->y);
	return dx + dy;
}

bool getNScore(unique_ptr<SNode> &n, NodeList &openList, NodeList &closedList)
{
	for (auto it = openList.begin(); it != openList.end(); ++it)
	{
		if (n->x == (*it)->x && n->y == (*it)->y) // if it's on the list
		{
			//if (n->score >= (*it)->score) // if the the newcost  >= existing_n cost
			//{
			//	return true;
			//}
			//else // continue
			//{
			//	false;
			//}

			return (n->score >= (*it)->score);
		}
	}

	for (auto it = closedList.begin(); it != closedList.end(); ++it)
	{
		if (n->x == (*it)->x && n->y == (*it)->y) // if it's on the list
		{
			//if (n->score >= (*it)->score) // if the the newcost  >= existing_n cost
			//{
			//	return true;
			//}
			//else // continue
			//{
			//	return false;
			//}
			return (n->score >= (*it)->score);
		}
	}
}

void RemoveN(unique_ptr<SNode> &n, NodeList &closedList)
{
	for (auto it = closedList.begin(); it != closedList.end(); ++it)
	{
		if (n->x == (*it)->x && n->y == (*it)->y) // if it's on the list
		{
			closedList.erase(it); // Remove it
		}
	}
}

void SortList(NodeList &openList)
{
	//sorty stuff
	std::sort(openList.begin(), openList.end(), CompareScore);
}

bool CompareScore(unique_ptr<SNode> &node1, unique_ptr<SNode> &node2)
{
	return node1->score < node2->score;
}