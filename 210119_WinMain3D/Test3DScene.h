#pragma once
#include "GameNode.h"
#include "Vector3.h"
#include "Matrix.h"

class FreeCamera;
class Test3DScene :
    public GameNode
{
    Matrix mat1, mat2, mat3;
    Matrix matrix[6];
    //---------------------------

    FreeCamera* camera;

    vector<Vector3> vecVertexs;
    vector<DWORD> vecIndex;
    Matrix matWorld;
    Matrix matView;
    Matrix matProj;
    Matrix matViewport;
    Vector3 angle;
    Vector3 position;
    float gravity = 9.8f;
    float veloY;
    float angleVelo;
    //---------------------------
    Vector3 cubeVertexs[8];
    Vector3 cubeAngle;

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

