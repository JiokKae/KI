/*
	파일 입출력
	1) 소스 파일 외부에 데이터를 기록할 텍스트 파일을 생성, 데이터를 입력 (출력)
	2) 외부에 있는 텍스트 파일의 데이터를 읽어들인다. (입력)

	3) 사용처
		3-1) 게임의 세이브 / 로드할 때
		3-2) 게임의 특정 데이터 (몬스터 정보, 맵 정보, 아이템 정보, 상점 정보 등등)를
			소스 코드 안에 넣지 않고 외부 파일에서 불러오고 싶을 때

		코드 외부에서 게임의 데이터만 수정해서 게임의 내용을 추가 / 삭제 / 수정할 수 있어야 한다.
		-> Data Driven Development (데이터 중심의 개발 방식)
*/

#include <iostream>
#include "FileManager.h"

class A;
class A;
class A;

int main()
{
	FileManager fileManager;
	//int testArray[10] = { 2,223,746,98,720,39,86,7,32,46987 };
	//fileManager.WriteFile("TestData.txt", testArray, 10);

	fileManager.ReadFile("TestData.txt");
	for (int i = 0; i < 10; i++)
	{
		cout << fileManager.numDatas[i] << endl;
	}
	
}

