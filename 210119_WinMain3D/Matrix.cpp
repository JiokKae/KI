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

void Matrix::SetRandom()
{
	for (int i = 0; i < vecData.size(); i++)
	{
		for (int j = 0; j < vecData[i].size(); j++)
		{
			vecData[i][j] = rand() % 10 - 5;
		}
	}
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
			if (abs(vecData[i][j] - mat[i][j]) > EPSILON)
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

Matrix Matrix::Inverse()
{
	Matrix InverseMat(size());
	Matrix ConfactorMatT = Cofactor().Transpose();
	float detThis = Determinent();
	for (int i = 0; i < size(); i++)
	{
		for (int j = 0; j < vecData[i].size(); j++)
		{
			InverseMat[i][j] = ConfactorMatT[i][j] / detThis;
		}
	}

	return InverseMat;
}

Matrix Matrix::Cofactor()
{
	Matrix CofactorMat(size());

	for (int i = 0; i < size(); i++)
	{
		for (int j = 0; j < vecData[i].size(); j++)
		{
			CofactorMat[i][j] = (((i+j)&1)? -1:1) * Minor(i, j).Determinent();
		}
	}

	return CofactorMat;
}

Matrix Matrix::Minor(int row, int col)
{
	Matrix minorMat(size() - 1);

	int minorRow = 0, minorCol = 0;
	for (int i = 0; i < size(); i++)
	{
		if (row == i) continue;

		minorCol = 0;
		for (int j = 0; j < vecData[i].size(); j++)
		{
			if (col == j) continue;

			minorMat[minorRow][minorCol++] = vecData[i][j];
		}

		minorRow++;
	}

	return minorMat;
}

float Matrix::Determinent()
{
	if (size() == 1)
	{
		return vecData[0][0];
	}
	else if (size() == 2)
	{
		return (vecData[0][0] * vecData[1][1] - vecData[0][1] * vecData[1][0]);
	}
	
	float det = 0.0f;
	for (int i = 0; i < size(); i++)
	{
		float minorDet = Minor(i, 0).Determinent();
		det += vecData[i][0] * ((i & 1) ? -1 : 1) * minorDet;
	}
	return det;
}

void Matrix::Resize(int dimension)
{
	vecData.resize(dimension);
	for (Row& row : vecData)
	{
		row.Resize(dimension);
	}
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
