#pragma once
#include <string>
#include <fstream>
using namespace std;

class FileManager
{
private:
public:
	int* numDatas;	// ������ ������ �Է��� ���� �迭 ����



	~FileManager();

	void WriteFile(string fileName, int* arrName, int arrSize);
	void ReadFile(string fileName);
	void InputData();
};

