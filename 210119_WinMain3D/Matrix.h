#pragma once
#include "pch.h"

class Vector3;
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

	static Matrix Identity(int dimension);
	static Matrix Translation(float x, float y, float z);
	static Matrix RotationX(float angle);
	static Matrix RotationY(float angle);
	static Matrix RotationZ(float angle);
	static Matrix Scaling(float x, float y, float z);
	
	static Matrix View(Vector3& eye, Vector3& lookat, Vector3& up);
	static Matrix Projection(float fovY, float aspect, float nearZ, float farZ);
	static Matrix Viewport(float x, float y, float w, float h, float minZ, float maxZ);

	void Resize(int dimension);

	Matrix();
	Matrix(int dimension);
	Matrix(int row, int col);
	Matrix(std::initializer_list<Row> l) : vecData(l) {}
	
	~Matrix();
};

