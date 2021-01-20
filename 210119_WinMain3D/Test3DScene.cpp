#include "Test3DScene.h"

HRESULT Test3DScene::Init()
{
    float starttime = timeGetTime();

    mat1.Resize(4);
    mat1.SetRandom();
    mat1 = {
        {1, 7, 4, 0},
        {9, 4, 8, 8},
        {2, 4, 5, 5},
        {1, 7, 1, 1}
    };
    mat2 = mat1.Inverse();
    mat3 = mat1 * mat2;

    finish_time = timeGetTime() - starttime;

    return S_OK;
}

void Test3DScene::Release()
{
}

void Test3DScene::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown('1'))
    {
        float starttime = timeGetTime();

        mat1.Resize(2);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown('2'))
    {
        float starttime = timeGetTime();

        mat1.Resize(3);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown('3'))
    {
        float starttime = timeGetTime();

        mat1.Resize(4);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown('4'))
    {
        float starttime = timeGetTime();

        mat1.Resize(5);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown('5'))
    {
        float starttime = timeGetTime();

        mat1.Resize(6);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown('6'))
    {
        float starttime = timeGetTime();

        mat1.Resize(7);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown('7'))
    {
        float starttime = timeGetTime();

        mat1.Resize(8);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown('8'))
    {
        float starttime = timeGetTime();

        mat1.Resize(9);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown('9'))
    {
        float starttime = timeGetTime();

        mat1.Resize(10);
        mat1.SetRandom();
        mat2 = mat1.Inverse();
        mat3 = mat1 * mat2;

        finish_time = timeGetTime() - starttime;
    }
}

void Test3DScene::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

    char szText[128] = "";
    sprintf_s(szText, 128, "finish time = %.0fms", finish_time);
    TextOut(hdc, 0, 0, szText, strlen(szText));

    PrintMatrix(hdc, mat1, 50, 50);
    PrintMatrix(hdc, mat2, 100 + 50 * mat2.size(), 50);
    PrintMatrix(hdc, mat3, 150 + 100 * mat2.size(), 50);
    
    for (int i = 0; i < mat1.size(); i++)
    {
        PrintMatrix(hdc, mat1.Minor(i, 0), i * (50 * mat2.size()), 50 + 500);
    }
    
}

void Test3DScene::PrintMatrix(HDC hdc, Matrix mat, int posX, int posY)
{
    char szText[128] = "";
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            HBRUSH old = (HBRUSH)SelectObject(hdc, CreateSolidBrush(int(16777215 * (mat[i][j] + 5) / 9.0f) ));

            Rectangle(hdc, j * 50 + posX, i * 50 + posY, j * 50 + posX + 50, i * 50 + posY + 50);
            sprintf_s(szText, 128, "%.2f", mat[i][j]);
            TextOut(hdc, j * 50 + posX, i * 50 + posY, szText, strlen(szText));

            DeleteObject(SelectObject(hdc, old));
        }
    }
}
