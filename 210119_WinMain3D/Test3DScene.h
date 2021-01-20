#pragma once
#include "GameNode.h"
#include "Vector3.h"
#include "Matrix.h"

class Test3DScene :
    public GameNode
{
    Matrix mat1, mat2, mat3;
    float finish_time;
public:
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render(HDC hdc);

    void PrintMatrix(HDC hdc, Matrix mat, int posX, int posY);

    Test3DScene() {};
    virtual ~Test3DScene() {};
};

