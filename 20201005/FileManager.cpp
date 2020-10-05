#include "FileManager.h"

FileManager::~FileManager()
{
	delete[] numDatas;
	numDatas = nullptr;
}

void FileManager::WriteFile(string fileName, int * arrName, int arrSize)
{
	ofstream fout;
	fout.open(fileName);

	// 쓰는 실행문
	for (int i = 0; i < arrSize; i++)
	{
		if (i < arrSize - 1)
		{
			fout << arrName[i] << ", ";
		}
		else 
		{
			fout << arrName[i];
		}
	}

	fout.close();
}

void FileManager::ReadFile(string fileName)
{
	ifstream fin;
	fin.open(fileName);

	char separate;		// 

	numDatas = new int[10];
	for (int i = 0; i < 10; i++)
	{
		fin >> numDatas[i];
		fin >> separate;
	}

	fin.close();
}

void FileManager::InputData()
{
}


