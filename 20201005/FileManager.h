#pragma once
#include <string>
#include <fstream>
using namespace std;

class FileManager
{
private:
public:
	int* numDatas;	// 정수형 데이터 입력을 위한 배열 변수



	~FileManager();

	void WriteFile(string fileName, int* arrName, int arrSize);
	void ReadFile(string fileName);
	void InputData();
};

