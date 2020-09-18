#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

int main()
{
	// p. 111 
	// LAB. 지뢰 찾기
	/*
	int arr[10][10] = {};
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (rand() % 100 < 30)
				arr[i][j] = 1;
			else
				arr[i][j] = 0;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (arr[i][j])
				cout << "# ";
			else
				cout << ". ";
		}
		cout << endl;
	}
	*/

	// p. 113
	// Exercise
	/*
	1. for(int x=0;x<10;x++){}이 종료되었을 때 x의 최종값은?
	=>10

	2. while(x<100) y++; 에서 y++는 언제 실행되는가?
	=>x가 100보다 작을 때

	3. 다음의 중첩 반복문은 몇번이나 반복되는가?
	for(i=0; i < 10; i++)
		for(k = 1; k <= 3; k++)
	=> 30번 반복됨

	4. do-while 반복 구조는 최소한 몇번 반복하는가?
	=> 1번

	5. 다음 코드의 실행 결과를 써라.
	short i;
	for(i = 1;i >= 0; i++)
		printf("%d\n", i);
	출력결과 : 
	1
	2
	3
	...
	32,767

	6. 다음 코드의 실행결과를 써라
	int i = -2;
	while(++i)
		printf("하이 \n");

	출력결과 :

	7. 다음 코드의 실행결과를 써라.
	i=0;
	for(;;)
	{
		if(i>10)
			break;
		if(i<6)
			continue;
		printf("%d", i);
		i++;
	}

	출력 결과 : 
	678910

	8. 다음 코드를 C++ 버전의 범위-기반 루프로 변경하여 보자.
	int test[10];
	for(int i in test)
		i = 0;
	*/
	// p. 115
	// Programming exercise
	// 1. 사용자로부터 2개의 문자열을 읽어서 같은지 다른지를 화면에 출력한다.
	/*
	string s1, s2;
	cout << "첫 번째 문자열: ";
	cin >> s1;
	cout << "두 번째 문자열: ";
	cin >> s2;
	
	if (s1 == s2)
		cout << "2개의 문자열은 같습니다." << endl;
	else
		cout << "2개의 문자열은 다릅니다." << endl;
	*/

	// 2. 5개의 음료(콜라, 물, 스프라이트, 주스, 커피)를 판매하는 자동판매기 머신을 구현하여보자.
	//	사용자가 1부터 5사이의 숫자를 입력하여 음료수를 선택할 수 있게 한다.
	//	사용자가 선택한 음료를 출력한다. 사용자가 1~5 이외의 숫자를 선택하면 "오류. 선택이 유효하지 않습니다.
	

	return 0;

}