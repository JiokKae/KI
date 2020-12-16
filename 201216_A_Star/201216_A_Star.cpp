#include <iostream>
#include <list>
using namespace std;

struct POINT { int x, y; };

struct Node {
	POINT pos;
	Node* parent;

	Node() 
		: parent(nullptr) 
	{};
};

int main()
{
	int nodeCount = 6;
	POINT startPos = { 0,0 };
	POINT endPos = { nodeCount, nodeCount };
	list<Node*> openList;
	list<Node*> closeLIst;

	Node** map = new Node * [nodeCount];
	for (int y = 0; y < nodeCount; y++)
	{
		map[y] = new Node[nodeCount];
		for (int x = 0; x < nodeCount; x++)
		{
			map[y][x].pos = { x, y };
		}
	}

	openList.push_back(&map[startPos.x][startPos.y]);

	while (true)
	{
	
	}

	for (int i = 0; i < nodeCount; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}
