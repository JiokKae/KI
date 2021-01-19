#include "Matrix.h"

Matrix::Row::Row()
{
}

Matrix::Row::Row(int dimension)
{
	vecRow.reserve(dimension);
}

Matrix::Row::~Row()
{
}

int Matrix::Row::size()
{
	return vecRow.size();
}

void Matrix::Row::Resize(int dimension)
{
	vecRow.resize(dimension);
}

float& Matrix::Row::operator[](int index)
{
	return vecRow[index];
}

Matrix::Row& Matrix::operator[](int index)
{
	return vecData[index];
}

bool Matrix::operator==(Matrix& mat)
{
	for (int i = 0; i < vecData.size(); i++)
	{
		for (int j = 0; j < vecData[i].size(); j++)
		{
			if (vecData[i][j] != mat[i][j])
				return false;
		}
	}
	return true;
}

bool Matrix::operator!=(Matrix& mat)
{
	return !((*this) == mat);
}

Matrix Matrix::operator+(Matrix& mat)
{
	Matrix ret(vecData.size());
	for (int i = 0; i < vecData.size(); i++)
	{
		for (int j = 0; j < vecData[i].size(); j++)
		{
			ret[i][j] = vecData[i][j] + mat[i][j];
		}
	}
	return ret;
}

Matrix Matrix::operator-(Matrix& mat)
{
	Matrix ret(vecData.size());
	for (int i = 0; i < vecData.size(); i++)
	{
		for (int j = 0; j < vecData[i].size(); j++)
		{
			ret[i][j] = vecData[i][j] - mat[i][j];
		}
	}
	return ret;
}

Matrix Matrix::operator*(Matrix& mat)
{
	Matrix ret(vecData.size());
	for (int i = 0; i < vecData.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			float sum = 0;
			for (int k = 0; k < vecData[i].size(); k++)
			{
				sum += vecData[i][k] * mat[k][j];
			}
			ret[i][j] = sum;
		}
	}
	return ret;
}

Matrix Matrix::operator*(float f)
{
	Matrix ret(vecData.size());
	for (int i = 0; i < vecData.size(); i++)
	{
		for (int j = 0; j < vecData[i].size(); j++)
		{
			ret[i][j] = vecData[i][j] * f;
		}
	}
	return ret;
}

Matrix Matrix::Transpose()
{
	Matrix ret(vecData.size());
	for (int i = 0; i < vecData.size(); i++)
	{
		for (int j = 0; j < vecData[i].size(); j++)
		{
			ret[i][j] = vecData[j][i];
		}
	}
	return ret;
}

Matrix::Matrix()
{
}

Matrix::Matrix(int dimension)
{
	vecData.resize(dimension);
	for (Row& row : vecData)
	{
		row.Resize(dimension);
	}
}

Matrix::~Matrix()
{
}
