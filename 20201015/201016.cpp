#include <windows.h>
#include <ctime>

#define MAX_BULLET_NUM 10
#define MAX_ENEMY_NUM 10
#define ATTACK_DELAY 1

HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPSTR		g_lpszClass = (LPSTR)TEXT("�������� ����");

//����
enum DIR { IDLE, LEFT, RIGHT, TOP, BOTTOM, STRDIR_CNT };

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

//�÷��̾�
struct Player
{
	int left, top, right, bottom;
	int currentBulletNum;
	int hp;
	int score;
	int attackDelay;
	bool isGameOver;
};

//��
struct Enemy
{
	int left, top, right, bottom;
	DIR currentDir;
	int moveSpeed;
	int hp;
	int score;
	bool isAlive;
};

//�Ѿ�
struct Bullet
{
	int left, top, right, bottom;
	DIR currentDir;
	bool isMove;
	int moveSpeed;
};

//��
struct Map
{
	int left, top, right, bottom;
};

//��ü ����
Player player;
Bullet bullet[MAX_BULLET_NUM];
Map map;
Enemy enemy[MAX_ENEMY_NUM];

//�÷��̾� �ʱ�ȭ
void PlayerInit(Player &player)
{
	player.left = 500;
	player.top = 325;
	player.right = 600;
	player.bottom = 425;
	player.currentBulletNum = 0;
	player.hp = 2;
	player.score = 0;
	player.attackDelay = 0.5;
	player.isGameOver = false;
}

//�Ѿ� �ʱ�ȭ
void BulletInit(Bullet &bullet)
{
	bullet.left = 535;
	bullet.top = 360;
	bullet.right = 565;
	bullet.bottom = 390;
	bullet.moveSpeed = 5;
	bullet.currentDir = DIR::IDLE;
	bullet.isMove = false;
}

//�� �ʱ�ȭ
void MapInit(Map &map)
{
	map.left = 170;
	map.top = 0;
	map.right = 930;
	map.bottom = 750;
}

//���� �ʱ�ȭ
void EnemyInit(Enemy &enemy)
{
	enemy.currentDir = (DIR)(rand() % 4 + 1);

	if (enemy.currentDir == DIR::TOP)
	{
		enemy.top = 650;
		enemy.bottom = 750;
		enemy.left = 500;
		enemy.right = 600;
	}
	else if (enemy.currentDir == DIR::BOTTOM)
	{
		enemy.top = 0;
		enemy.bottom = 100;
		enemy.left = 500;
		enemy.right = 600;
	}
	else if (enemy.currentDir == DIR::LEFT)
	{
		enemy.top = 325;
		enemy.bottom = 425;
		enemy.left = 830;
		enemy.right = 930;
	}
	else if (enemy.currentDir == DIR::RIGHT)
	{
		enemy.top = 325;
		enemy.bottom = 425;
		enemy.left = 170;
		enemy.right = 270;
	}

	enemy.score = 100;
	enemy.hp = 2;
	enemy.moveSpeed = 2;
	enemy.isAlive = false;
}

//���
void Render()
{

}

//�� ����
void CreateMap(HDC hdc)
{
	MoveToEx(hdc, map.left, map.top, NULL);
	LineTo(hdc, map.right, map.top);
	LineTo(hdc, map.right, map.bottom);
	LineTo(hdc, map.left, map.bottom);
	LineTo(hdc, map.left, map.top);
}

//�߻� (Ű �Է�)
void Fire(WPARAM wParam)
{
	
	if (GetAsyncKeyState(VK_UP))
	{
		bullet[player.currentBulletNum].currentDir = DIR::TOP;
		bullet[player.currentBulletNum].isMove = true;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		bullet[player.currentBulletNum].currentDir = DIR::BOTTOM;
		bullet[player.currentBulletNum].isMove = true;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		bullet[player.currentBulletNum].currentDir = DIR::LEFT;
		bullet[player.currentBulletNum].isMove = true;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		bullet[player.currentBulletNum].currentDir = DIR::RIGHT;
		bullet[player.currentBulletNum].isMove = true;
	}
	
	/*
	switch (wParam)
	{
	case VK_UP:
		bullet[player.currentBulletNum].currentDir = DIR::TOP;
		break;
	case VK_DOWN:
		bullet[player.currentBulletNum].currentDir = DIR::BOTTOM;
		break;
	case VK_LEFT:
		bullet[player.currentBulletNum].currentDir = DIR::LEFT;
		break;
	case VK_RIGHT:
		bullet[player.currentBulletNum].currentDir = DIR::RIGHT;
		break;
	default:
		break;
	}
	*/
	//�Ѿ� ������ ���� ����
	

	player.currentBulletNum++;

	//�Ѿ� ��ȣ �ʱ�ȭ
	if (player.currentBulletNum >= MAX_BULLET_NUM)
	{
		player.currentBulletNum = 0;
	}
}

//�Ѿ� ������
void BulletMove(int num)
{
	if (bullet[num].currentDir == DIR::TOP)
	{
		bullet[num].top -= bullet[num].moveSpeed;
		bullet[num].bottom -= bullet[num].moveSpeed;
	}
	else if (bullet[num].currentDir == DIR::BOTTOM)
	{
		bullet[num].top += bullet[num].moveSpeed;
		bullet[num].bottom += bullet[num].moveSpeed;
	}
	else if (bullet[num].currentDir == DIR::LEFT)
	{
		bullet[num].left -= bullet[num].moveSpeed;
		bullet[num].right -= bullet[num].moveSpeed;
	}
	else if (bullet[num].currentDir == DIR::RIGHT)
	{
		bullet[num].left += bullet[num].moveSpeed;
		bullet[num].right += bullet[num].moveSpeed;
	}
}

//�� ������
void EnemyMove(int num)
{
	if (enemy[num].currentDir == DIR::TOP)
	{
		enemy[num].top -= enemy[num].moveSpeed;
		enemy[num].bottom -= enemy[num].moveSpeed;
	}
	else if (enemy[num].currentDir == DIR::BOTTOM)
	{
		enemy[num].top += enemy[num].moveSpeed;
		enemy[num].bottom += enemy[num].moveSpeed;
	}
	else if (enemy[num].currentDir == DIR::LEFT)
	{
		enemy[num].left -= enemy[num].moveSpeed;
		enemy[num].right -= enemy[num].moveSpeed;
	}
	else if (enemy[num].currentDir == DIR::RIGHT)
	{
		enemy[num].left += enemy[num].moveSpeed;
		enemy[num].right += enemy[num].moveSpeed;
	}
}

//�浹�� �� ũ�� �۾���
void Hit(Enemy &enemy)
{
	if (enemy.hp > 0)
	{
		enemy.top += 15;
		enemy.bottom -= 15;
		enemy.left += 15;
		enemy.right -= 15;

		enemy.hp--;
	}
	else
	{
		player.score += enemy.score;
		EnemyInit(enemy);
	}
	
}

//�浹�� �÷��̾� ũ�� �۾���
void Hit(Player &player)
{
	if (player.hp > 0)
	{
		player.top += 15;
		player.bottom -= 15;
		player.left += 15;
		player.right -= 15;

		player.hp--;
	}
	else
	{
		player.isGameOver = true;
	}

}

//�ʰ� �Ѿ� �浹üũ
void CheckCollision(Map map, Bullet &bullet)
{
	//�浹 �Ǹ� �Ѿ� �ʱ�ȭ
	if (bullet.currentDir == DIR::TOP && bullet.top <= map.top)
	{
		BulletInit(bullet);
	}

	if (bullet.currentDir == DIR::BOTTOM && bullet.bottom >= map.bottom)
	{
		BulletInit(bullet);
	}

	if (bullet.currentDir == DIR::LEFT && bullet.left <= map.left)
	{
		BulletInit(bullet);
	}

	if (bullet.currentDir == DIR::RIGHT && bullet.right >= map.right)
	{
		BulletInit(bullet);
	}
}

// �÷��̾�� �� �浹üũ
void CheckCollision(Enemy &enemy, Player &player)
{
	if (enemy.currentDir == DIR::TOP && enemy.top <= player.bottom)
	{
		EnemyInit(enemy);
		Hit(player);
	}

	if (enemy.currentDir == DIR::BOTTOM && enemy.bottom >= player.top)
	{
		EnemyInit(enemy);
		Hit(player);
	}

	if (enemy.currentDir == DIR::LEFT && enemy.left <= player.right)
	{
		EnemyInit(enemy);
		Hit(player);
	}

	if (enemy.currentDir == DIR::RIGHT && enemy.right > player.left)
	{
		EnemyInit(enemy);
		Hit(player);
	}
}

//���� �Ѿ�
void CheckCollision(Enemy &enemy, Bullet &bullet)
{
	if (enemy.isAlive)
	{
		if (enemy.currentDir == DIR::TOP && enemy.top <= bullet.bottom)
		{
			Hit(enemy);
			BulletInit(bullet);
		}

		if (enemy.currentDir == DIR::BOTTOM && enemy.bottom >= bullet.top)
		{
			Hit(enemy);
			BulletInit(bullet);
		}

		if (enemy.currentDir == DIR::LEFT && enemy.left <= bullet.right)
		{
			Hit(enemy);
			BulletInit(bullet);
		}

		if (enemy.currentDir == DIR::RIGHT && enemy.right > bullet.left)
		{
			Hit(enemy);
			BulletInit(bullet);
		}
	}
}

int APIENTRY WinMain(HINSTANCE _hInstnace, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	g_hInstance = _hInstnace;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 900, NULL, NULL, g_hInstance, NULL);

	ShowWindow(g_hWnd, nCmdShow);

	MSG message;

	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//Ÿ�̸� ����
	KillTimer(g_hWnd, 0);
	KillTimer(g_hWnd, 1);
	KillTimer(g_hWnd, 2);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	srand(time(NULL));
	PAINTSTRUCT ps;
	HDC hdc;
	
	static HANDLE hMAinTimer;
	static HANDLE hEnemySpawnTimer;
	static HANDLE hTimer;
	static int min = 0;
	static int sec = 0;
	static int currentEnemyNum = 0;
	static char str[64];

	switch (iMessage)
	{
	case WM_CREATE:
		hMAinTimer = (HANDLE)SetTimer(hWnd, 0, 1000/70, NULL); // 1.������ �ڵ�, 2.�̺�Ʈ ���̵�, 3.ȣ�� �ֱ� ms(�� ȣ���ұ�?), 4.ȣ�� �Լ� ������
		hEnemySpawnTimer = (HANDLE)SetTimer(hWnd, 1, 1000, NULL);
		hTimer = (HANDLE)SetTimer(hWnd, 2, 1000, NULL);

		PlayerInit(player);
		MapInit(map);

		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			BulletInit(bullet[i]);
		}

		for (int i = 0; i < MAX_ENEMY_NUM; i++)
		{
			EnemyInit(enemy[i]);
		}

		break;
	case WM_TIMER:
		if (!player.isGameOver)
		{
			switch (wParam)
			{
			case 0:

				if (!bullet[player.currentBulletNum].isMove)
				{
					Fire(wParam);
				}
				//�Ѿ� �̵� �� �ʰ� �浹Ȯ��
				for (int i = 0; i < MAX_BULLET_NUM; i++)
				{
					BulletMove(i);
					CheckCollision(map, bullet[i]);
				}

				//�� ������
				for (int i = 0; i < MAX_ENEMY_NUM; i++)
				{
					if (enemy[i].isAlive)
					{
						EnemyMove(i);
					}

					CheckCollision(enemy[i], player);
				}

				for (int i = 0; i < MAX_ENEMY_NUM; i++)
				{
					for (int j = 0; j < MAX_BULLET_NUM; j++)
					{
						CheckCollision(enemy[i], bullet[j]);
					}
				}
				break;
			case 1:
				enemy[currentEnemyNum].isAlive = true;
				currentEnemyNum++;

				if (currentEnemyNum >= MAX_ENEMY_NUM)
				{
					currentEnemyNum = 0;
				}
				break;
			case 2:
				sec++;

				if (sec >= 60)
				{
					min++;
					sec = 0;
				}
			default:
				break;
			}
			InvalidateRect(hWnd, NULL, false);
			break;
		}
	case WM_KEYDOWN:
		
		break;
	case WM_PAINT:

#pragma region ������۸� ����ó�� ó��
		static HDC hdc, MemDC, tmpDC;
		static HBITMAP BackBit, oldBackBit;
		static RECT bufferRT;
		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &bufferRT);
		MemDC = CreateCompatibleDC(hdc);
		BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
		PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
#pragma endregion ������۸� ����ó�� ��

		///
		//���� ���
		wsprintf(str, "Timer: %d�� %d��", min, sec);
		TextOut(hdc, 20, 50, str, strlen(str));

		//���� ���
		wsprintf(str, "Score: %d" , player.currentBulletNum);
		TextOut(hdc, 20, 20, str, strlen(str));

		//�� ����
		CreateMap(hdc);

		// �÷��̾� ����
		Rectangle(hdc, player.left, player.top, player.right, player.bottom);
		Render();
		
		//�Ѿ� ����
		for (int i = 0; i < MAX_BULLET_NUM; i++)
		{
			Rectangle(hdc, bullet[i].left, bullet[i].top, bullet[i].right, bullet[i].bottom);
		}
		
		//�� ����
		for (int i = 0; i < MAX_ENEMY_NUM; i++)
		{
			if (enemy[i].isAlive)
			{
				Rectangle(hdc, enemy[i].left, enemy[i].top, enemy[i].right, enemy[i].bottom);
			}
		}

		//���ӿ��� ���
		if (player.isGameOver)
		{
			wsprintf(str, "GAME OVER");
			TextOut(hdc, 500, 300, str, strlen(str));
			
		}
		///

#pragma region ������۸� ��ó�� ó��

		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		GetClientRect(hWnd, &bufferRT);
		BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);
#pragma endregion ������۸� ��ó�� ��
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}