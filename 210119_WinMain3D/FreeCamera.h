#pragma once
#include "pch.h"
#include "Vector3.h"
#include "Matrix.h"

class FreeCamera
{
private:
    // camera Attributes
    Vector3 position;
    Vector3 front;
    Vector3 up;
    Vector3 right;
    Vector3 worldUp;
    // euler Angles
    float yaw;
    float pitch;
    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float fov;
    float zoomSpeed;
    float lastMouseZDelta;
    bool firstMouse = true;
    Vector3 center;
public:
    HRESULT Init();
    void Release();
    void Update();

    float GetFov() { return fov; }
    Vector3 GerFront() { return front; }
    Vector3 GetPosition() { return position; }
    void SetPosition(Vector3 vec) { this->position = vec; }
    void SetCenter(Vector3 center) { this->center = center; }
    Matrix GetViewMatrix();
};