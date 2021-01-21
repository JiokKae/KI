#include "Test3DScene.h"
#include "FreeCamera.h"

HRESULT Test3DScene::Init()
{
    camera = new FreeCamera();
    camera->Init();

    // 로컬 스페이스 ( 모델링 스페이스) : 정육면체
    //vecVertexs.resize(8);
    vecVertexs = {
        { -1,  1, -1},
        {  1,  1, -1},
        { -1, -1, -1},
        {  1, -1, -1},

        { -1,  1,  1},
        {  1,  1,  1},
        { -1, -1,  1},
        {  1, -1,  1},
    };

    // 정육면체 면 : 6 -> 삼각형 : 12 -> 인덱스 : 36
    vecIndex.resize(36);
    // 앞면 삼각형
    vecIndex[ 0] = 0;   vecIndex[ 1] = 1;   vecIndex[ 2] = 2; // 첫번째
    vecIndex[ 3] = 2;   vecIndex[ 4] = 1;   vecIndex[ 5] = 3; // 두번째
    // 뒷면 삼각형                
    vecIndex[ 6] = 5;   vecIndex[ 7] = 4;   vecIndex[ 8] = 7; // 첫번째
    vecIndex[ 9] = 7;   vecIndex[10] = 4;   vecIndex[11] = 6; // 두번째
    // 왼면 삼각형                
    vecIndex[12] = 0;   vecIndex[13] = 2;   vecIndex[14] = 6; // 첫번째
    vecIndex[15] = 6;   vecIndex[16] = 4;   vecIndex[17] = 0; // 두번째
    // 오른면 삼각형
    vecIndex[18] = 3;   vecIndex[19] = 1;   vecIndex[20] = 5; // 첫번째
    vecIndex[21] = 5;   vecIndex[22] = 7;   vecIndex[23] = 3; // 두번째
    // 윗면 삼각형                
    vecIndex[24] = 0;   vecIndex[25] = 4;   vecIndex[26] = 5; // 첫번째
    vecIndex[27] = 5;   vecIndex[28] = 1;   vecIndex[29] = 0; // 두번째
    // 아랫면 삼각형                
    vecIndex[30] = 2;   vecIndex[31] = 3;   vecIndex[32] = 6; // 첫번째
    vecIndex[33] = 6;   vecIndex[34] = 3;   vecIndex[35] = 7; // 두번째

    int dp = 100;

    /*
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
    
    matrix[0] = Matrix::Identity(4);
    matrix[1] = Matrix::Translation(10, 5, -1);
    matrix[2] = Matrix::RotationX(45);
    matrix[3] = Matrix::RotationY(30);
    matrix[4] = Matrix::RotationZ(90);
    matrix[5] = Matrix::Scaling(2, 3, 1);
    
    Vector3 a = { 1, 2, 3 };
    
    Vector3 b = Vector3::TransformCoord(a, matrix[1]);
    Vector3 c = Vector3::TransformNormal(a, matrix[1]);
    Vector3 d = Vector3::TransformCoord(a, matrix[4]);
    Vector3 e = Vector3::TransformNormal(a, matrix[4]);
    int dp = 1000;
    */

    return S_OK;
}

void Test3DScene::Release()
{
    SAFE_RELEASE(camera);
}

void Test3DScene::Update()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
    {
        angleVelo -= 0.005f;
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
    {
        angleVelo += 0.005f;
    }
    else
    {
        angleVelo = Clamp(angleVelo - 0.05f, 0.0f, 1000000.0f);
    }
    angle.y += angleVelo;
    
    Vector3 front(0.0f, 0.0f, 1.0f);
    Matrix mat = Matrix::RotationY(angle.y);
    front = Vector3::TransformNormal(front, mat);

    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
    {
        position += front.Normalize() * 0.1f;
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
    {
        position -= front.Normalize() * 0.1f;
    }
    if (position.y == 0.0f && KeyManager::GetSingleton()->IsStayKeyDown(VK_SPACE))
    {
        veloY = 100.0f;
    }

    position.y += veloY * TimerManager::GetSingleton()->GetTimeElapsed();
    veloY -= (gravity - angleVelo / 4) * TimerManager::GetSingleton()->GetTimeElapsed();
    position.y = Clamp(position.y, 0.0f, 100000000.0f);

    Vector3 cameraPos = position - front * 5.0f + Vector3(0.0f, 1.0f, 0.0f);
    //camera->SetPosition(cameraPos);

    camera->SetCenter(position);

    Matrix matT = Matrix::Translation(position.x, position.y, position.z);
    Matrix matRX = Matrix::RotationX(angle.x);
    Matrix matRY = Matrix::RotationY(angle.y);
    Matrix matS = Matrix::Scaling(1.0f, 1.0f, 1.0f);
    matWorld = matRX * matRY * matS * matT;

    Vector3 eye =       {  0.0f,  1.0f, -5.0f };
    Vector3 lookAt =    {  0.0f,  0.0f,  0.0f };
    Vector3 up =        {  0.0f,  1.0f,  0.0f };
    matView = camera->GetViewMatrix();
    

    // 투영
    RECT rc;
    GetClientRect(g_hWnd, &rc);
    matProj = Matrix::Projection(RADIAN(camera->GetFov()), rc.right / (float)rc.bottom,
        1.0f, 1000.0f);

    //뷰 포트
    matViewport = Matrix::Viewport(0.0f, 0.0f, rc.right, rc.bottom, 0.0f, 1.0f);

    #pragma region 접어 
    /*
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
    */
    #pragma endregion
    camera->Update();
}

void Test3DScene::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

    Matrix matWVP = matWorld * matView * matProj * matViewport;
    Matrix matVPV = matView * matProj * matViewport;

    {
        HPEN old = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));

        Vector3 Start = { 0.0f, 0.0f, 0.0f };
        Vector3 End = { +10.0f, 0.0f, 0.0f };
        Start = Vector3::TransformCoord(Start, matVPV);
        End = Vector3::TransformCoord(End, matVPV);
        MoveToEx(hdc, Start.x, Start.y, NULL);
        LineTo(hdc, End.x, End.y);

        DeleteObject(SelectObject(hdc, old));
    }
    {
        HPEN old = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));

        Vector3 Start = { 0.0f, 0.0f, 0.0f };
        Vector3 End = { 0.0f, 10.0f, 0.0f };
        Start = Vector3::TransformCoord(Start, matVPV);
        End = Vector3::TransformCoord(End, matVPV);
        MoveToEx(hdc, Start.x, Start.y, NULL);
        LineTo(hdc, End.x, End.y);

        DeleteObject(SelectObject(hdc, old));
    }
    {
        HPEN old3 = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 255)));

        Vector3 Start = { 0.0f, 0.0f, 0.0f };
        Vector3 End = { 0.0f, 0.0f, 10.0f };
        Start = Vector3::TransformCoord(Start, matVPV);
        End = Vector3::TransformCoord(End, matVPV);
        MoveToEx(hdc, Start.x, Start.y, NULL);
        LineTo(hdc, End.x, End.y);

        DeleteObject(SelectObject(hdc, old3));
    }

    for (int boxI = 0; boxI < 5; boxI++)
    {
        Vector3 v1, v2, v3;
        for (int i = 0; i < vecIndex.size(); i += 3)
        {
            v1 = Vector3::TransformCoord(vecVertexs[vecIndex[i]] +      Vector3(0.0f, 0.0f, -2.5f) * boxI, matWVP);
            v2 = Vector3::TransformCoord(vecVertexs[vecIndex[i + 1]] +  Vector3(0.0f, 0.0f, -2.5f) * boxI, matWVP);
            v3 = Vector3::TransformCoord(vecVertexs[vecIndex[i + 2]] +  Vector3(0.0f, 0.0f, -2.5f) * boxI, matWVP);

            if (Vector3::Dot(Vector3::Cross(v2 - v1, v3 - v1), camera->GerFront()) > 0)
                continue;
            // 뷰스페이스 행렬 변환
            // 투영
            // 뷰포트

            if (i == 6 || i == 9)
            {
                HPEN old = (HPEN)SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));

                MoveToEx(hdc, v1.x, v1.y, NULL);
                LineTo(hdc, v2.x, v2.y);
                LineTo(hdc, v3.x, v3.y);
                LineTo(hdc, v1.x, v1.y);
                Ellipse(hdc, v1.x - 5, v1.y - 5, v1.x + 5, v1.y + 5);
                Ellipse(hdc, v2.x - 5, v2.y - 5, v2.x + 5, v2.y + 5);
                Ellipse(hdc, v3.x - 5, v3.y - 5, v3.x + 5, v3.y + 5);

                DeleteObject(SelectObject(hdc, old));
            }
            else
            {
                MoveToEx(hdc, v1.x, v1.y, NULL);
                LineTo(hdc, v2.x, v2.y);
                LineTo(hdc, v3.x, v3.y);
                LineTo(hdc, v1.x, v1.y);
                Ellipse(hdc, v1.x - 5, v1.y - 5, v1.x + 5, v1.y + 5);
                Ellipse(hdc, v2.x - 5, v2.y - 5, v2.x + 5, v2.y + 5);
                Ellipse(hdc, v3.x - 5, v3.y - 5, v3.x + 5, v3.y + 5);
            }

        }
    }
    

    /*
    char szText[128] = "";
    sprintf_s(szText, 128, "finish time = %.0fms", finish_time);
    TextOut(hdc, 0, 0, szText, strlen(szText));

    
    PrintMatrix(hdc, mat1, 50, 50);
    PrintMatrix(hdc, mat2, 100 + 50 * mat2.size(), 50);
    PrintMatrix(hdc, mat3, 150 + 100 * mat2.size(), 50);

    for (int i = 0; i < 6; i++)
    {
        PrintMatrix(hdc, matrix[i], 50 + i * 250, 550);
    }
    */
    char szText[128] = "";
    sprintf_s(szText, 128, "높이 = %.2f", position.y);
    TextOut(hdc, 1300, 300, szText, strlen(szText));
    sprintf_s(szText, 128, "회전률 = %.2f", angleVelo);
    TextOut(hdc, 1300, 400, szText, strlen(szText));
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
