// 201214_Graph.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <time.h>

using namespace std;

struct PEOPLE
{
	int nID;
	bool isHuman;
	vector<int> vecData;

	PEOPLE() : nID(0), isHuman(false) {};
};

struct Town
{
	int peopleCount;
	int human;
	vector<PEOPLE> vecPeople;

	Town() : peopleCount(0), human(1) {};
};

void Fopen_Town(const char* Filename, Town* town)
{
	FILE* fp = NULL;

	fopen_s(&fp, Filename, "r");

	fscanf_s(fp, "%d", &town->peopleCount);

	town->vecPeople.resize(town->peopleCount);

	while (true)
	{
		if (feof(fp))
			break;

		// 마을 사람 INDEX
		int nID;
		fscanf_s(fp, "%d", &nID);
		town->vecPeople[nID - 1].nID = nID;

		// 마을 사람이 알고 있는 정보
		int dataCount;
		fscanf_s(fp, "%d", &dataCount);
		town->vecPeople[nID - 1].vecData.resize(dataCount);

		int data;
		for (int i = 0; i < dataCount; i++)
		{
			fscanf_s(fp, "%d", &data);
			town->vecPeople[nID - 1].vecData[i] = data;
		}
	}

	fclose(fp);
}

// 너비 우선 탐색
void BFS(Town* town)
{
	queue<PEOPLE*> q;
	town->vecPeople[0].isHuman = true;
	q.push(&town->vecPeople[0]);
	int newHumanIndex;

	while (q.empty() == false)
	{
		for (int i = 0; i < q.front()->vecData.size(); i++)
		{
			newHumanIndex = q.front()->vecData[i] - 1;
			if (town->vecPeople[newHumanIndex].isHuman == false)
			{
				town->vecPeople[newHumanIndex].isHuman = true;
				town->human++;
				q.push(&town->vecPeople[newHumanIndex]);
			}
		}
		q.pop();
	}
}

// 깊이 우선 탐색
void DFS(Town* town)
{
   stack<PEOPLE*> s;
   town->vecPeople[0].isHuman = true;
   s.push(&town->vecPeople[0]);

   int i;
   int vecDataSize;
   int newHumanIndex;
   // 스택이 비어있을때 까지 반복
   while (s.empty() == false)
   {	
		// 스택 맨 위의 자식들 중
		vecDataSize = s.top()->vecData.size();
		for (i = 0; i < vecDataSize; i++)
		{
			newHumanIndex = s.top()->vecData[i] - 1;

			// 휴먼이 아닌 사람이 있을 때
			if (town->vecPeople[newHumanIndex].isHuman == false)
			{
				// 휴먼으로 설정하고 스택에 푸시
				town->vecPeople[newHumanIndex].isHuman = true;
				town->human++;
				s.push(&town->vecPeople[newHumanIndex]);
				break;
			}
		}
		// 만약 자식들중 휴먼이 아닌 사람이 없다면
		if (i == vecDataSize)
		{
			// 스택 맨위의 휴먼을 팝
			s.pop();
		}
	}
}

int main()
{
	clock_t start, end;

	Town town1_dfs;
	Town town1_bfs;
	Town town2_dfs;
	Town town2_bfs;

	Fopen_Town("마을1.txt", &town1_dfs);
	Fopen_Town("마을1.txt", &town1_bfs);
	Fopen_Town("마을2.txt", &town2_dfs);
	Fopen_Town("마을2.txt", &town2_bfs);

	DFS(&town1_dfs);
	BFS(&town1_bfs);

	start = clock();
	DFS(&town2_dfs);
	end = clock();
	printf("%fms\n", (double)(end - start));

	start = clock();
	BFS(&town2_bfs);
	end = clock();
	printf("%fms\n", (double)(end - start));
	

	cout << "마을1 깊이우선 사람 : " << town1_dfs.human << endl;
	cout << "마을1 너비우선 사람 : " << town1_bfs.human << endl;
	cout << "마을2 깊이우선 사람 : " << town2_dfs.human << endl;
	cout << "마을2 너비우선 사람 : " << town2_bfs.human << endl;


	// 결과 
//	cout << endl;

//	vector<PEOPLE>::iterator it;
//	for (it = vecPeople.begin(); it != vecPeople.end(); it++)
//	{
//		printf("%2d번 사람 ", it->nID);
//		cout << ((it->isHuman) ? "휴먼" : "외계인") << endl;
//	}
}
