#include <iostream>

class A 
{
	int money;
public:
	void SetMoney(int money) {
		this->money = money;
	}
	int getMoney()
	{
		return money;
	}
};

class B 
{
public:
	void SetA(A a)
	{
		a.SetMoney(500);
	}
	void SetRefA(A &a)
	{
		a.SetMoney(500);
	}
};

void main()
{
	B b;
	A a;

	a.SetMoney(1000);
	std::cout << a.getMoney() << std::endl;
	b.SetA(a);
	std::cout << a.getMoney() << std::endl;
	b.SetRefA(a);
	std::cout << a.getMoney() << std::endl;

	A* ap = new A[10];
	if (ap == NULL)
		std::cout << "트루1" << std::endl;
	delete[] ap;
	ap = nullptr;
	if (ap == NULL)
		std::cout << "트루2" << std::endl;
}