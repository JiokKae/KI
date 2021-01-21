#include "Matrix.h"
#include "Vector3.h"

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

Matrix Matrix::operator *(Matrix& mat)
{
	Matrix ret(vecData.size(), vecData[0].size());
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

Matrix Matrix::Identity(int dimension)
{
	Matrix ret(dimension);
	for (int i = 0; i < dimension; i++)
		ret[i][i] = 1;

	return ret;
}

Matrix Matrix::Translation(float x, float y, float z)
{
	Matrix ret = Matrix::Identity(4);
	ret[3][0] = x;
	ret[3][1] = y;
	ret[3][2] = z;

	return ret;
}

Matrix Matrix::RotationX(float angle)
{
	Matrix ret = Matrix::Identity(4);
	ret[1][1] = ret[2][2] = cos(RADIAN(angle));
	ret[1][2] = sin(RADIAN(angle));
	ret[2][1] = -sin(RADIAN(angle));

	return ret;
}

Matrix Matrix::RotationY(float angle)
{
	Matrix ret = Matrix::Identity(4);
	ret[0][0] = ret[2][2] = cos(RADIAN(angle));
	ret[0][2] = -sin(RADIAN(angle));
	ret[2][0] = sin(RADIAN(angle));

	return ret;
}

Matrix Matrix::RotationZ(float angle)
{
	Matrix ret = Matrix::Identity(4);
	ret[0][0] = ret[1][1] = cos(RADIAN(angle));
	ret[0][1] = sin(RADIAN(angle));
	ret[1][0] = -sin(RADIAN(angle));

	return ret;
}

Matrix Matrix::Scaling(float x, float y, float z)
{
	Matrix ret = Matrix::Identity(4);
	ret[0][0] = x;
	ret[1][1] = y;
	ret[2][2] = z;

	return ret;
}

Matrix Matrix::View(Vector3& eye, Vector3& lookat, Vector3& up)
{
	Vector3 camX, camY, camZ;
	camZ = Vector3(lookat - eye).Normalize();
	camX = Vector3::Cross(up, camZ).Normalize();
	camY = Vector3::Cross(camZ, camX).Normalize();

	Matrix ret = Matrix::Identity(4);
	ret[0][0] = camX.x;	ret[0][1] = camY.x;	ret[0][2] = camZ.x;
	ret[1][0] = camX.y;	ret[1][1] = camY.y;	ret[1][2] = camZ.y;
	ret[2][0] = camX.z;	ret[2][1] = camY.z;	ret[2][2] = camZ.z;
	ret[3][0] = -Vector3::Dot(camX, eye);
	ret[3][1] = -Vector3::Dot(camY, eye);
	ret[3][2] = -Vector3::Dot(camZ, eye);

	return ret;
}

Matrix Matrix::Projection(float fovY, float aspect, float nearZ, float farZ)
{
	Matrix ret = Matrix::Identity(4);

	float h = 1.0f / tanf(fovY / 2.0f);
	float w = h / aspect;

	ret[0][0] = w;
	ret[1][1] = h;
	ret[2][2] = farZ / (farZ - nearZ);
	ret[3][2] = (-nearZ * farZ) / (farZ - nearZ);
	ret[2][3] = 1.0f;
	ret[3][3] = 0.0f;

	return ret;

	float const tanHalfFovY = tan(fovY / 2.0f);

	Matrix Result(4);
	Result[0][0] = 1.0f / (aspect * tanHalfFovY);
	Result[1][1] = 1.0f / (tanHalfFovY);
	Result[2][3] = 1.0f;

	Result[2][2] = farZ / (farZ - nearZ);
	Result[3][2] = -(farZ * nearZ) / (farZ - nearZ);

	return Result;
}

Matrix Matrix::Viewport(float x, float y, float w, float h, float minZ, float maxZ)
{
	Matrix ret = Matrix::Identity(4);
	ret[0][0] = w / 2.0f;
	ret[1][1] = -h / 2.0f;
	ret[2][2] = maxZ - minZ;
	ret[3][0] = x + w / 2.0f;
	ret[3][1] = y + h / 2.0f;
	ret[3][2] = minZ;

	return ret;
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

Matrix::Matrix(int row, int col)
{
	vecData.resize(row);
	for (Row& row : vecData)
	{
		row.Resize(col);
	}
}

Matrix::~Matrix()
{
}
