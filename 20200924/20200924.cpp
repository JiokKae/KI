#include <iostream>
#include <string>
#include <ctime>
using namespace std;

/*
	함수 선언 및 구현
	반환형 함수이름(매개변수)
	{
		실행할 코드;
	}

	반환형 => 함수를 실행하고 끝낼 때 함수 바깥으로 배출할 데이터
		있을 수도 있고 없을 수도 있다. 상황에 따라 다르다.
		없을 경우에는 void

	함수 이름 => 말 그대로 함수 이름(이름 잘짓자)

	매개 변수 => 함수 밖에서 함수 안으로 데이터를 넣어주는 것

	샐힝할 코드 => 이 함수를 실행하면 실행되어야 할 코드 묶음
*/

// 함수 선언 및 구현
void Print(void)
{
	cout << "안녕하세요" << endl;
	cout << "저희 경일게임아카데미를 방문해 주셔서 감사합니다" << endl;
	cout << "....." << endl;
}

// 입력받은 두 수를 빼서 결과값을 반환하는 함수
int Minus(int a, int b)
{
	return a - b;
}

bool IsAdult(int age)
{
	return age >= 20;
}

int RandomRange(int num1, int num2)
{
	return rand() % (num2 - num1 + 1) + num1;
}

float Average(int a, int b)
{
	return float(a + b) / 2;
}

int main()
{
	/*
		삼항 연산자 => if, else 조건을 간략하게 줄여서
		
	*/
	/*
	// 함수 호출, 함수 실행 => 선언을 했으면 써야지
	Print();

	// 반복적으로 여기저기서 사용할 코드를 함수라는 녀석을 사용해서
	// 묶을 수 있다.

	int hp, b;
	int mp = 100;
	cin >> hp;
	cin >> b;
	cout << hp - b << endl;


	// 입력받은 두 수를 빼서 결과값을 반환하는 함수

	// 결과는 같다
	hp = hp - b;
	mp = mp - 10;
	// 아래는 함수를 활용한 방법
	hp = Minus(hp, b);
	mp = Minus(mp, 10);
	*/

	// 사람의 나이를 입력받아서 성인인지 미성년자인지를 출력하는 프로그램
	/*
	int age;
	cin >> age;

	bool isAdult = age >= 20 ? true : false;
	cout << "성인입니까 : " << isAdult << endl;
	*/

	// 실습 2. 두 정수를 입력 받아서 평균 값을 반환하는 함수	
	int a = 100, b = 33;
	cout << a << "와 " << b << "의 평균 값 : ";
	cout << Average(a, b) << endl;

	// 실습 3. 범위를 매개인자로 받아서 그 범위 내의 랜덤한 값을 반환하는 함수
	srand(time(NULL));
	cout << "3~10 random" << endl;
	for (int i = 0; i < 10; i++)
		cout << RandomRange(3, 10) << " ";
	cout << endl;

	// 오버로딩 : 매개인자의 수 또는 데이터 타입을 다르게 줘서
	// 같은 이름의 함수를 여러개 쓸 수 있게 하는 것
	// 조건
	// 1. 함수 이름 같아야 하고
	// 2. 매개인자의 수 또는 데이터 타입이 달라야함
	// 3. 반환형은 같아야 함



	return 0;
}
