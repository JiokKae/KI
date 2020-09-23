#include <iostream>
using namespace std;

// 단일 연결리스트에서 데이터를 담기 위한 구조체를 Node라고 한다.
struct Node
{
	int data;		// 데이터를 이 변수에 담을 것
	Node* pNext;	// 현재 노드의 다음 노드의 메모리 주소
	// pNext로 각 노드는 내 다음 순서가 될 노드를 알아야 함
};

Node* CreateNode(int data) {
	Node * newNode = new Node;
	newNode->data = data;
	newNode->pNext = nullptr;

	return newNode;
}

class LinkedList
{
	Node* head;
public:
	LinkedList() {
		head = nullptr;
	}
	void InsertNode(int data)
	{
		Node * new_node = CreateNode(data);
		Node *p = head;
		if (p == nullptr)
			head = new_node;
		else
		{
			while (p->pNext != nullptr)
				p = p->pNext;
			p->pNext = new_node;
		}
	}
	void DeleteLastNode() {
		Node* p = head;
		if (p != nullptr)
		{
			if (p->pNext == nullptr)
			{
				delete p;
				head = nullptr;
			}
			else
			{
				while (p->pNext->pNext != nullptr)
					p = p->pNext;
				cout << p->pNext->data << "삭제" << endl;
				delete p->pNext;
				p->pNext = nullptr;
			}
		}
	}
	void DeleteNodeByIndex(int index)
	{
		Node* p = head;
		if (p->pNext == nullptr)
		{
			delete p;
			head = nullptr;
		}
		else if(p != nullptr)
		{
			for (int i = 0; i < index - 1; i++)
			{
				p = p->pNext;
			}
			if (p->pNext->pNext != nullptr)
			{
				Node *back = p->pNext->pNext;
				delete p->pNext;
				p->pNext = back;
			}
			else
			{
				delete p->pNext;
				p->pNext = nullptr;
			}
		}
	}
	void Print() 
	{
		Node *p = head;
		cout << "[리스트 출력]" << endl;
		while (p != nullptr)
		{
			cout << p->data << " -> ";
			p = p->pNext;
		}
		cout << endl;
	}
	
};

int main()
{
	// 10->6
	/*
	Node* startNode = new Node;
	startNode->data = 10;
	{
		Node* secondNode = new Node;
		secondNode->data = 6;

		Node* thirdNode = new Node;
		thirdNode->data = 7;

		// startNode의 다음 노드에 sescondNode를 대입
		startNode->pNext = secondNode;
		secondNode->pNext = thirdNode;
	}

	// startNode 데이터 출력
	cout << startNode->data << endl;
	// secondNode 데이터 출력
	cout << startNode->pNext->data << endl;
	// thirdNode 데이터 출력
	cout << startNode->pNext->pNext->data << endl;

	*/
	/*
	실습
	1.
	숫자를 10번 입력받는다.
	입력받은 숫자들을 단일 연결리스트를 활용해서 저장한다음 해당 숫자들을 순서대로 출력하는 프로그램을 만들어보아라

	=> nullptr NULL 조사
	*/
	
	int input;
	int length = 5;
	LinkedList list;

	cout << "숫자 "<< length << "번 입력 : ";
	for (int i = 0; i < length; i++)
	{
		cin >> input;
		list.InsertNode(input);
	}
	list.Print();

	// 맨 뒤 삭제
	list.DeleteLastNode();
	list.Print();

	// 3번째 노드 삭제
	list.DeleteNodeByIndex(2);
	list.Print();

	// 3번째 노드 삭제
	list.DeleteNodeByIndex(2);
	list.Print();

	list.DeleteNodeByIndex(1);
	list.Print();
	
	list.DeleteNodeByIndex(0);
	list.Print();
}