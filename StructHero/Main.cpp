#include "StructHeroGame.h"

/*
/////////////////////////////////////////////////////////////////////
//
//	게임 설명
//
/////////////////////////////////////////////////////////////////////

순서도 먼저 그리자.
영웅은 절차적 2: 영웅은 구조적

가로*세로 사이즈 설정할 수 있도록 만들자. (동적할당)

맵 크기에 따라 난이도 변경
5*5 = 25 이하 난이도 1
10*10 = 100 이하 난이도 2
15 * 15 = 225 이하 난이도 3

WASD 이동

배열 / 구조체 / 함수를 최대한 활용해보자.

전투는 가위바위보

타일 : (Vector2Int) 좌표 / (int) 타입 / (char) 모양
타일에 종류가 있다(숲 늪 땅) 마다 만나는 몬스터도 다르다.

플레이어 : (string) 이름 / (int) 최대 HP / (int) HP / (int) 경험치 / (int) 레벨 / (int) 골드 / (Vector2Int) 좌표

포션 : (string) 이름 / (int) 가격 / (int) 회복치

몬스터 : (string) 이름 / (int) 최대 HP / (int) HP / (int) 획득 경험치 / (int) 획득 골드
몬스터는 포켓몬스터처럼 랜덤 인카운터 방식 (타일 이동시 확률 적용)

상점 : (Potion*) 아이템 종류
*/

int main()
{
	// 변수 선언
	StructHeroGame game;	// 게임

	// 로고 출력
	game.PrintLogo();

	// 용사 이름 입력
	game.InputHeroName();

	// 맵의 크기 설정
	game.InputMapSize();

	// 게임 초기화
	game.Init();

	while (true)
	{
		system("cls");
		game.PrintTopbar();
		game.PrintMap();
		if (game.IsOver())
		{
			game.PrintGameEnd();
			GetEnter();
			break;
		}
		game.InputProcess();
	}

	return 0;
}
