#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	// 배열 선언
	// 변수를 여러개 선언하지 않고도 하나의 변수로 열을 만들어서 관리할 수 있다.
	//int num[5]; // 5개의 int형 변수를 배열로 선언

	//// 선언 이후에 [인덱스]를 하게 되면 해당 변수에 접근

	//num[0] = 10;
	//num[1] = 5;
	//num[2] = 3;
	//num[3] = 5;
	//num[4] = 6;

	//cout << num[0] << endl;
	//cout << num[1] << endl;
	//cout << num[2] << endl;
	//cout << num[3] << endl;
	//cout << num[4] << endl;

	//srand(time(0));

	//// for문을 사용해서 0번째 인덱스부터 4번째 인덱스까지 출력
	//for (int i = 0; i < 5; i++)
	//{
	//	num[i] = rand() % 100 * 10;
	//	cout << num[i] << endl;
	//}

	int guguData[8][9] = {};
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			guguData[i][j] = (i + 2) * (j + 1);
			cout << guguData[i][j] << "\t";
		}
		cout << endl << endl;
	}
}
////
//
//#include <stdio.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <string.h>
//int solution(const char* s);
//int main()
//{
//	printf("%d", solution("asddsazxcxzqweewqwerew"));
//}
//// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
//int solution(const char* s) {
//	int answer = 0;
//	int size = strlen(s);
//	int i;
//	int topi, bottomi;
//	bool tEnd, bEnd;
//	bool outOfSize;
//	int j;
//
//	for (i = 0; i < size; i++)
//	{
//		topi = bottomi = i;
//		tEnd = bEnd = false;
//		outOfSize = false;
//		while (!tEnd || !bEnd)
//		{
//			if (!tEnd)
//			{
//				if (topi - 1 > 0)
//				{
//					if (s[topi] == s[topi - 1])
//						topi--;
//					else
//						tEnd = true;
//				}
//				else
//				{
//					outOfSize = true;
//					tEnd = true;
//				}
//			}
//			if (!bEnd)
//			{
//				if (bottomi + 1 < size)
//				{
//					if (s[bottomi] == s[bottomi + 1])
//					{
//						/*printf("b비교 : %c == %c? \n", s[bottomi], s[bottomi+1]);*/
//						bottomi++;
//					}
//					else
//						bEnd = true;
//				}
//				else
//				{
//					outOfSize = true;
//					bEnd = true;
//				}
//			}
//		}
//
//		do {
//			if (outOfSize)
//				break;
//			if (topi - 1 < 0 || bottomi + 1 > size)
//				break;
//			/*printf("tb비교 : %c == %c? \n", s[topi - 1], s[bottomi + 1]);*/
//			if (s[topi - 1] == s[bottomi + 1])
//			{
//				topi--;
//				bottomi++;
//			}
//			else
//				break;
//		} while (true);
//
//		if (bottomi - topi + 1 > answer) {
//			answer = bottomi - topi + 1;
//		}
//		/*for(j = topi; j <= bottomi; j++)
//		    printf("%c",s[j]);
//		printf("\ntop = %d bottom = %d\n",topi, bottomi);*/
//	}
//
//	return answer;
//}
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#pragma warning (disable:4996)
//
//void initPan(char **pan, int size)
//{
//	int i, j;
//	for (i = 0; i < size; i++)
//		for (j = 0; j < size; j++)
//			pan[i][j] = 'O';
//}
//
//void printPan(char **pan, int size) 
//{
//	int i, j;
//	system("cls");
//	for (i = 0; i < size; i++)
//	{
//		for (j = 0; j < size; j++)
//		{
//			printf("%3c ", pan[i][j]);
//		}
//		printf("\n\n");
//	}
//}
//
//int putQueen(char **pan, int x, int y, int size)
//{
//	int i;
//	int x1, x2;
//	if (pan[x][y] != 'O')
//		return 0;
//	x1 = x + y;
//	x2 = x - y;
//	for (i = 0; i < size; i++)
//	{
//		
//		pan[i][y] = 'X';
//		pan[x][i] = 'X';
//		if (x1 - i >= 0)
//			pan[x1-i][i] = 'X';
//		if (x2 + i < size)
//			pan[x2 + i][i] = 'X';
//	}
//	pan[x][y] = 'Q';
//
//	return 1;
//}
//void main()
//{
//	int size = 5;
//	char **pan;
//	int i;
//	int x, y;
//
//	// 할당
//	pan = (char**)calloc(size, sizeof(char*));
//	for (i = 0; i < size; i++)
//		pan[i] = (char*)calloc(size, sizeof(char));
//
//	initPan(pan, size);
//	printPan(pan, size);
//	for (i = 0; i < size; i++)
//	{
//		printf("퀸 배치하기 : ");
//		scanf("%d %d", &x, &y);
//		if (putQueen(pan, x-1, y-1, size))
//			i--;
//		printPan(pan, size);
//	}
//	
//	
//
//	// 해제
//	for (i = 0; i < size; i++)
//		free(pan[i]);
//	free(pan);
//}