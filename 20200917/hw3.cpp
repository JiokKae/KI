#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

int main()
{
	// p. 111 
	// LAB. ���� ã��
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
	1. for(int x=0;x<10;x++){}�� ����Ǿ��� �� x�� ��������?
	=>10

	2. while(x<100) y++; ���� y++�� ���� ����Ǵ°�?
	=>x�� 100���� ���� ��

	3. ������ ��ø �ݺ����� ����̳� �ݺ��Ǵ°�?
	for(i=0; i < 10; i++)
		for(k = 1; k <= 3; k++)
	=> 30�� �ݺ���

	4. do-while �ݺ� ������ �ּ��� ��� �ݺ��ϴ°�?
	=> 1��

	5. ���� �ڵ��� ���� ����� ���.
	short i;
	for(i = 1;i >= 0; i++)
		printf("%d\n", i);
	��°�� : 
	1
	2
	3
	...
	32,767

	6. ���� �ڵ��� �������� ���
	int i = -2;
	while(++i)
		printf("���� \n");

	��°�� :

	7. ���� �ڵ��� �������� ���.
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

	��� ��� : 
	678910

	8. ���� �ڵ带 C++ ������ ����-��� ������ �����Ͽ� ����.
	int test[10];
	for(int i in test)
		i = 0;
	*/
	// p. 115
	// Programming exercise
	// 1. ����ڷκ��� 2���� ���ڿ��� �о ������ �ٸ����� ȭ�鿡 ����Ѵ�.
	/*
	string s1, s2;
	cout << "ù ��° ���ڿ�: ";
	cin >> s1;
	cout << "�� ��° ���ڿ�: ";
	cin >> s2;
	
	if (s1 == s2)
		cout << "2���� ���ڿ��� �����ϴ�." << endl;
	else
		cout << "2���� ���ڿ��� �ٸ��ϴ�." << endl;
	*/

	// 2. 5���� ����(�ݶ�, ��, ��������Ʈ, �ֽ�, Ŀ��)�� �Ǹ��ϴ� �ڵ��Ǹű� �ӽ��� �����Ͽ�����.
	//	����ڰ� 1���� 5������ ���ڸ� �Է��Ͽ� ������� ������ �� �ְ� �Ѵ�.
	//	����ڰ� ������ ���Ḧ ����Ѵ�. ����ڰ� 1~5 �̿��� ���ڸ� �����ϸ� "����. ������ ��ȿ���� �ʽ��ϴ�.
	

	return 0;

}