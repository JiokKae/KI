#include <iostream>
#include <string>
using namespace std;

/*
	구조체

	배열 / 구조체 / 함수 -> C++ 언어에서 코드 추상화에 사용되는 3요소
	즉, 코드 추상화를 위한 도구

	추상화 : 실제 현상(현실 세계)을 간략화 / 기호화 / 보편화를 통해서
	데이터 적으로 + 코드적으로 흉내낸 것

	추상화가 중요한 이유 : 코드를 짜는 사람도 컴파일이 결과물을 이용하는 것도
	모두 사람이 하니까 사람이 인지하기 좋은게 중요하다.

	배열 : 속성이 동일한 여러개의 데이터를 같은 이름과 연번으로 표현함으로써 추상화를
	한다.
	구조체 : 데이터를 특정 단위(동일한 규칙하의)로 묶어서 추상화를 한다.
	함수 : 코드를 특정 기능 단위로 묶어서 추상화를 한다.

	구조체를 언제 쓸까?
	특정 변수들이 무언가의 하위 개념으로 묶일 때

	몬스터
	몬스터의 이름, 몬스터의 HP, 몬스터의 공격력, 몬스터의 이동력, ...

	구조체를 정의하는 방법
	구조체를 사용하는 함수 이전에 정의한다. (해당 함수의 밖)
*/

struct Monster	// 사용자 정의 데이터
{
	string name;
	int HP;
	float moveSpeed;
	float attackValue;
};

struct Pirates
{
	string name;
	int HP;
	int atk;
	int def;
	float speed;
};

struct PiratesGroup
{
	string name;
	float buffValue;
	Pirates members[3];
};

struct Student {
	string name;
	int age;
	float GPA;
	bool canGraduate;
};

int main()
{
	// 1. 메모리 공간 관점에서 보자.
	string monsterName[5];
	int monsterHP[5];
	float monsterMoveSpeed[5];
	float monsterAttackValue[5];

	Monster monster;
	Monster monsters[5];

	monsters[0].name = "오준경";
	monsters[0].HP = 100;
	monsters[0].moveSpeed = 3.0f;
	monsters[0].attackValue = 5.0f;

	/* 
	실습1. Priates(해적)라는 구조체를 하나 정의한다.
	해적의 속성 : 이름, HP(int), 공격력(int), 방어력(int), 스피드(float)
	lupi라는 이름의 구조체 변수를 선언한 후에
	lupi의 각 하위 속성의 값을 입력하고 출력해보자.

	+ 스피드가 3.0 이상이면 
	'이름'의 스피드는 5.0입니다. (빠름)
	'이름'의 스피드는 5.0입니다. (빠름)
	*/
	PiratesGroup strawHatPirates;
	strawHatPirates.name = "밀집모자 해적단";
	strawHatPirates.buffValue = 2.3f;
	
	strawHatPirates.members[0].name = "루피";
	strawHatPirates.members[0].HP = 300;
	strawHatPirates.members[0].atk = 100;
	strawHatPirates.members[0].def = 50;
	strawHatPirates.members[0].speed = 4.0f;

	strawHatPirates.members[1].name = "조로";
	strawHatPirates.members[1].HP = 250;
	strawHatPirates.members[1].atk = 120;
	strawHatPirates.members[1].def = 30;
	strawHatPirates.members[1].speed = 2.0f;

	strawHatPirates.members[2].name = "상디";
	strawHatPirates.members[2].HP = 350;
	strawHatPirates.members[2].atk = 80;
	strawHatPirates.members[2].def = 70;
	strawHatPirates.members[2].speed = 6.0f;


	for (int i = 0; i < 3; i++)
	{
		cout << "이름 : " << strawHatPirates.members[i].name << endl;
		cout << strawHatPirates.members[i].name << "의 체력은 " << strawHatPirates.members[i].HP << "입니다." << endl;
		cout << strawHatPirates.members[i].name << "의 공격력은 " << strawHatPirates.members[i].atk << "입니다." << endl;
		cout << strawHatPirates.members[i].name << "의 방어력은 " << strawHatPirates.members[i].def << "입니다." << endl;
		if (strawHatPirates.members[i].speed >= 3.0f)
			cout << strawHatPirates.members[i].name << "의 스피드는 " << strawHatPirates.members[i].speed << "입니다. (빠름)" << endl;
		else
			cout << strawHatPirates.members[i].name << "의 스피드는 " << strawHatPirates.members[i].speed << "입니다. (보통)" << endl;
		cout << endl;
	}
	
	/*
	실습2.
	학생을 구조체화 해서 다음 속성을 결정하자.
	이름, 나이, 1~4학년까지의 학점, 졸업가능여부
	학생의 정보를 cin으로 입력받는다. (3명)

	+ 학생의 번호를 입력하면
	해당 학생의 프로필이 출력된다.

	+ 학생의 이름을 출력하면
	해당 학생의 프로필이 출력된다.
	*/

	Student students[3];
	for (int i = 0; i < 3; i++)
	{
		cout << "학생의 이름을 입력하시오 : ";
		cin >> students[i].name;
		cout << "학생의 나이를 입력하시오 : ";
		cin >> students[i].age;
		cout << "학생의 평균 평점을 입력하시오 : ";
		cin >> students[i].GPA;
		if (students[i].GPA >= 3.0f)
			students[i].canGraduate = true;
		else
			students[i].canGraduate = false;

	}
	
	int searchNumber;
	cout << "조회하려는 학생의 번호를 입력하시오 : ";
	cin >> searchNumber;
	if (cin.fail() || searchNumber < 0 || searchNumber > 3 - 1)
	{
		cout << "Error : 잘못된 입력" << endl;
		return 1;
	}
	cout << "이름 : " << students[searchNumber].name << endl;
	cout << "나이 : " << students[searchNumber].age << endl;
	cout << "평균 평점 : " << students[searchNumber].GPA << endl;
	cout << boolalpha << "졸업 가능 여부 : " << students[searchNumber].canGraduate << endl;

	string searchName;
	cout << "조회하려는 학생의 이름을 입력하시오 : ";
	cin >> searchName;
	for (int i = 0; i < 3; i++)
	{
		if (students[i].name == searchName)
		{
			cout << "이름 : " << students[i].name << endl;
			cout << "나이 : " << students[i].age << endl;
			cout << "평균 평점 : " << students[i].GPA << endl;
			cout << "졸업 가능 여부 : " << students[i].canGraduate << endl;
			break;
		}
	}
}
