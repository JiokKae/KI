// 201124_StrategyPattern.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.

/*
	Strategy 전략 패턴
	- 알고리즘을 교체 가능하게 하는 패턴.
	- 알고리즘의 인터페이스를 정의하고, 각각의 클래스 별로 캡슐화한 후 사용.

	활용성
	- 행동들이 조금씩 다를 뿐 개념적으로 관련된 많은 클래스들이 존재할 때.
	- 사용자가 몰라야 하는 데이터를 사용하는 알고리즘이 있을 때.
	- 하나의 클래스가 많은 행동을 정의하고, 이런 행동들이 
	그 클래스의 연산 안에서 복잡한 다중 조건문의 모습을 가질 때
		-> 많은 조건문 보다는 각각을 Strategy 클래스로 옮기는 것이 좋다.

*/
#include <iostream>
using namespace std;

class SortInterface
{
public:
	virtual void DoSort() = 0;	// 순수 가상 함수

};

class QuickSort : public SortInterface
{
public:
	virtual void DoSort() override { cout << "Do QuickSort~!!" << endl; }
};

class BubbleSort : public SortInterface
{
public:
	virtual void DoSort() override { cout << "Do BubbleSort~!!" << endl; }
};

class InsertionSort : public SortInterface
{
public:
	virtual void DoSort() override { cout << "Do InsertionSort~!!" << endl; }
};

class MergeSort : public SortInterface
{
public:
	virtual void DoSort() override { cout << "Do MergeSort~!!" << endl; }
};

class SortManager
{
private:
	SortInterface* sort;
public:
	SortManager() : sort(nullptr) {}
	~SortManager() { if (sort) delete sort; }

	void DoSort() { sort->DoSort(); }
	void ChangeSort(SortInterface* changeSort)
	{
		if (sort)
			delete sort;
		sort = changeSort;
	}
};

int main()
{
	SortManager sortMgr;

	sortMgr.ChangeSort(new QuickSort());
	sortMgr.DoSort();

	sortMgr.ChangeSort(new BubbleSort());
	sortMgr.DoSort();

	sortMgr.ChangeSort(new InsertionSort());
	sortMgr.DoSort();

	sortMgr.ChangeSort(new MergeSort());
	sortMgr.DoSort();

}
