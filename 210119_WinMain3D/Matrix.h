#pragma once
#include "pch.h"
class Matrix
{
private:
	class Row {
		vector<float> vecRow;
	public:
		Row();
		Row(int dimension);
		Row(std::initializer_list<float> l) : vecRow(l) {}
		~Row();

		int size();
		void Resize(int dimension);
		float& operator[](int index);
	};

	vector<Row> vecData;
public:
	void SetRandom();
	int size() { return vecData.size(); }

	Row& operator[](int index);

	bool operator==(Matrix& mat);
	bool operator!=(Matrix& mat);

	Matrix operator+(Matrix& mat);
	Matrix operator-(Matrix& mat);
	Matrix operator*(Matrix& mat);
	Matrix operator*(float f);

	Matrix Transpose();
	Matrix Inverse();
	Matrix Cofactor();
	Matrix Minor(int row, int col);
	float Determinent();

	void Resize(int dimension);

	Matrix();
	Matrix(int dimension);
	Matrix(std::initializer_list<Row> l) : vecData(l) {}
	
	~Matrix();
};

