#include <iostream>
/*
	템플릿(Template)
	-Generic Programming
	지금까지 작성했던 코드는 모두 자료형의 엄격한 제약을 받았다.
	자료형의 제약을 받지 않는 코드를 작성해보자.
	변수
	int num = 10;
*/

/*
	실습.
	두 수를 매개변수로 받아서 둘 중 큰 수를 반환하는 함수
	1) 두 수의 데이터 타입이 같은 경우
	2) 두 수의 데이터 타입이 다른 경우

*/

template<typename T>
T AddNum(T a, T b)
{
	return a + b;
}

template<typename T1, typename T2, typename Re>
Re Bigger(T1 a, T2 b, Re result)
{
	if (a > b)
		return a;
	else
		return b;
}

// 정수 두 개를 매개변수로 받아서 두 수의 합을 반환하는 함수
int AddNum(int a, int b)
{
	return a + b;
}

int main()
{
    std::cout << AddNum(10, 20) << std::endl;
	std::cout << AddNum(10.5f, 20.7f) << std::endl;

	int A = 10;
	float B = 20.5f;
	float C = 10.4f;
	int D = 20;
	int result = 0;

	std::cout << Bigger(A, B, (A > B) ? A : B) << std::endl;
	std::cout << Bigger(C, D, (C > D) ? C : D) << std::endl;
}

