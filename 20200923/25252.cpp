#include <iostream>

using namespace std;


struct Node
{
	int data;
	Node* nextNode;
};

int main()
{
	Node* prevNode;

	Node* startNode = new Node;

	prevNode = startNode;

	for (int i = 0; i < 10; i++)
	{
		(*startNode).data = i;
		
		startNode = (*startNode).nextNode;

	}

}