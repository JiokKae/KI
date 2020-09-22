#include <iostream>
#include <string>
using namespace std;

/*
	포인터
	변수
	1.이름 2.값 3.메모리 주소 4.메모리 크기
	&변수명 : 해당 변수의 메모리 주소를 알 수 있는 기호

	int : 기호가 있는 정수
	float : 기호가 있는 실수
	char : 문자
	string : 문자열
	포인터 : 변수의 메모리 주소

	사용하는 이유
	1. 변수의 접근이나 제어가 불가능한 외부에서 해당 변수에 접근하여 값을 제어하기 위해서
	2. 동적할당(new)을 통해서 런타임때 메모리에 할당되는 변수를 제어하기 위해서

	2. 동적할당
	1. 동적할당의 기본 방법과 개념
	 개념 : 힙 메모리에 자료를 저장한 공간을 할당해 놓는 것
	 (기존에는 스택 메모리)

	 자료형 변수명; (스택 메모리)
	 자료형* 변수명 = new 자료형; (힙 메모리)

	 2. 힙메모리와 스택메모리
	 힙 : 프로그래머(프로그램)이 자유롭게 할당하고 해제할 수 있는 메모리 영역
	 스택 : 특정 구문 내에서 {} 영역 내에서 임시로 할당되는 변수를 저장하는 영역

	 a. 데이터의 크기가 일정하지 않은 형태의 자료형
	 b. 서로 다른 구문 {}에서 변수의 값을 같이 쓰고 싶을 때
	*/

struct Node {
	int data;
	// 요 포인터를 이용해서 다음 노드의 메모리를 저장합니다.
	Node* pNext;
	
};

Node* create_node(int data)
{
	Node* new_node = new Node;
	new_node->data = data;
	new_node->pNext = NULL;
	return new_node;
}




class LinkedList {
	Node* head = NULL;
public:
	void insert_node(int data)
	{
		Node** head = &(this->head);
		Node * node = create_node(data);
		Node *p = *head;
		if (*head == NULL)
		{
			*head = node;
		}
		else if ((*head)->pNext == NULL)
		{
			(*head)->pNext = node;
		}
		else
		{
			while (p->pNext != NULL)
			{
				p = p->pNext;
			}
			p->pNext = node;
		}
	}
	void print_list()
	{
		Node *p = head;
		while (p != NULL)
		{
			cout << p->data << "-> ";
			p = p->pNext;
		}

	}
};

int main()
{
	// 배열의 동적할당
	//int numbers[10];

	
	// 배열의 크기를 입력받아서 처리하자.
	
	
	/*
		실습1.
		위에서 배운 배열의 할당 방법(동적할당)을 써서 숫자를 1 ~ 10까지 입력 받아
		입력받은 횟수만큼 cin으로 입력한다.
		1 ~ 10 사이의 숫자(배열 인덱스)를 입력하면 해당 데잍어를 출력한다.

		예시) 
		"배열의 크기를 입력하세요 : " _6
		"크기만큼 데이터를 입력하세요 : " _ * 6;

	int size;
	int index;

	cout << "배열의 크기를 입력하세요 : ";
	cin >> size;
	int * numbers = new int[size];
	
	cout << "크기만큼 데이터를 입력하세요 : ";
	for (int i = 0; i < size; i++)
	{
		cin >> numbers[i];
	}

	cout << "출력할 데이터의 인덱스를 입력하세요 : ";
	cin >> index;
	cout << numbers[index];
	*/

	/*
	int a = 10;		// 스택 메모리 할당 
					// 이름 : a, 값 : 10, 크기 : 4byte, 메모리 주소 : ???
	
	int * pa = &a;	// 스택 메모리 할당
					// 이름 : pa, 값 : ???, 크기 : 4byte, 메모리 주소 : ???
	int & ra = a;

	*pa = 15;
	cout << a << endl; 
	ra = 20;
	cout << a << endl;

	cout << "a의 값 : " << a << endl;
	cout << "a의 크기 : " << sizeof(a) << endl;
	cout << "a의 메모리주소 : " << &a << endl;

	cout << "pa의 값 : " << pa << endl;
	cout << "pa의 크기 : " << sizeof(pa) << endl;
	cout << "pa의 메모리주소 : " << &pa << endl;

	__int64 test64 = 134823489723498;
	__int64* pTest64 = &test64;

	cout << "test64의 값 : " << test64 << endl;
	cout << "test64의 크기 : " << sizeof(test64) << endl;
	cout << "test64의 메모리주소 : " << &test64 << endl;

	cout << "pTest64의 값 : " << pTest64 << endl;
	cout << "pTest64의 크기 : " << sizeof(pTest64) << endl;
	cout << "pTest64의 메모리주소 : " << &pTest64 << endl;
	*/
	
	/*
		실습2.
		구구단 저장 조건
		1. 몇 단까지 저장할 것인지 cin으로 입력받아서
		2단 ~ input단까지 guguData에 저장
		
		몇 단을 보여줄까요? _
		몇을 곱할까요? _ _
		_ *  _ = __
	
	int inputData;
	int* guguData[9];
	cout << "몇 단까지 저장할 것인가? : ";
	cin >> inputData;
	
	for (int i = 0; i < 9; i++)
	{
		guguData[i] = new int[inputData - 1];
		for (int j = 0; j < inputData - 1; j++)
		{
			guguData[i][j] = (j + 2) * (i + 1);
			cout << guguData[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "몇 단을 보여줄까요? : ";
	int dan;
	cin >> dan;

	cout << dan << "단 : " << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << guguData[i][dan - 2] << endl;
	}

	cout << "몇을 곱할까요? : ";
	int a, b;
	cin >> a >> b;
	
	cout << a << " * " << b << " = " << guguData[b - 1][a - 2] << endl;
	

	int a = 3, b = 4, c = 5;
	int*** testArray;
	
	testArray = new int**[a];
	for (int i = 0; i < a; i++)
	{
		testArray[i] = new int*[b];
		for (int j = 0; j < b; j++)
		{
			testArray[i][j] = new int[c];
			for (int k = 0; k < c; k++)
			{
				testArray[i][j][k] = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
			}
		}
	}

	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			for (int k = 0; k < c; k++)
			{
				cout << testArray[i][j][k] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
	*/
	// 역참조란? 포인터가 가르키고 있는 메모리 주소의 값에 접근하는 것
	// int * ptr;
	// *포인터 변수
	// *ptr;

	//int a = 0;
	//int* ptr = &a;
	//
	//cout << ptr << endl;
	//// 역참조 => *포인터 변수
	//cout << *ptr << endl;
	//
	//*ptr = 3;
	//
	//cout << a << endl;
	//
	//// 지역 변수가 메모리가 해제되는 타이밍은
	//// 해당 변수가 선언된 코드블럭이 끝났을 때
	//{
	//	// int a;
	//}
	//int *ptr = new int;
	//// delete 삭제할 메모리 주소
	//delete ptr;
	//
	//int* array = new int[10];
	//// 동적생성한 배열 할당 해제하는 방법
	//delete[] array;

	/*
	실습
	생성한 3차원 배열을 delete[] 키워드를 사용해서 할당 해제 해보기
	*/
	/*
	int a = 40, b = 40, c = 40;
	int*** testArray;
	getchar();
	testArray = new int**[a];
	for (int i = 0; i < a; i++)
	{
		testArray[i] = new int*[b];
		for (int j = 0; j < b; j++)
		{
			testArray[i][j] = new int[c];
			for (int k = 0; k < c; k++)
			{
				testArray[i][j][k] = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
			}
		}
	}
	
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			for (int k = 0; k < c; k++)
			{
				cout << testArray[i][j][k] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
	getchar();
	
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++) 
		{
			delete[] testArray[i][j];
		}
		delete[] testArray[i];
	}
	delete[] testArray;

	getchar();
	getchar();

	*/
	
	//링크드 리스트 (자료구조)
	//-> 노드라는 구조체에 데이터를 넣어서 관리
	//-> 노드라는 구조체는 다음 노드의 메모리 주소를 알고 있어야 한다.
	//Node * head = NULL;
	//insert_node(&head, 3);
	//insert_node(&head, 4);
	//insert_node(&head, 78);
	//insert_node(&head, 4);
	//insert_node(&head, 5);
	//insert_node(&head, 33);
	//insert_node(&head, 72);

	//linked list

	LinkedList list;

	list.insert_node(3);
	list.insert_node(4);
	list.insert_node(6);
	list.insert_node(7);
	list.insert_node(8);
	list.insert_node(9);
	list.insert_node(12);

	list.print_list();

}
