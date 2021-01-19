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
		~Row();

		int size();
		void Resize(int dimension);
		float& operator[](int index);
	};

	vector<Row> vecData;
public:
	Row& operator[](int index);

	bool operator==(Matrix& mat);
	bool operator!=(Matrix& mat);

	Matrix operator+(Matrix& mat);
	Matrix operator-(Matrix& mat);
	Matrix operator*(Matrix& mat);
	Matrix operator*(float f);

	Matrix Transpose();
	Matrix();
	Matrix(int dimension);
	~Matrix();
};

