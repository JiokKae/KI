#include "FreeCamera.h"

HRESULT FreeCamera::Init()
{
	position = Vector3( 0.0f,  1.0f, -5.0f );
	front = Vector3(0.0f, 0.0f, 1.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);

	yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	pitch = 0.0f;
	fov = 45.0f;

	movementSpeed = 1.5f;
	this->mouseSensitivity = 0.01f;
	zoomSpeed = 2.0f;

	return S_OK;
}

void FreeCamera::Release()
{
}

void FreeCamera::Update()
{
	// fov
	float offset = lastMouseZDelta - g_mousezDelta;
	lastMouseZDelta = g_mousezDelta;
	fov += offset / 120.0f * zoomSpeed;
	fov = Clamp(fov, 1.0f, 45.0f);

	float cameraSpeed = movementSpeed * TimerManager::GetSingleton()->GetTimeElapsed(); // adjust accordingly

	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
		position += front * cameraSpeed;

	if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
		position -= front * cameraSpeed;

	if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
		position += Vector3::Cross(front, up).Normalize() * cameraSpeed;

	if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
		position -= Vector3::Cross(front, up).Normalize() * cameraSpeed;

	RECT winRect = GetWindowRect();

	float xoffset = g_ptMouse.x - WINSIZE_X / 2;
	float yoffset = - g_ptMouse.y + WINSIZE_Y / 2; // y 좌표의 범위는 밑에서부터 위로가기 때문에 반대로 바꿉니다.
	SetCursorPos(winRect.left + WINSIZE_X / 2, winRect.top + WINSIZE_Y / 2);
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	position.x = Clamp(position.x + xoffset, -5.0f, 5.0f);
	position.y = Clamp(position.y + yoffset, -5.0f, 5.0f);

	front.x = -cos(RADIAN(pitch)) * cos(RADIAN(yaw));
	front.y = sin(RADIAN(pitch));
	front.z = cos(RADIAN(pitch)) * sin(RADIAN(yaw));
	front = front.Normalize();
}

Matrix FreeCamera::GetViewMatrix()
{
	return Matrix::View(position, center, up);
}
