#include <iostream>
#include <string>
using namespace std;

/*
	����ü

	�迭 / ����ü / �Լ� -> C++ ���� �ڵ� �߻�ȭ�� ���Ǵ� 3���
	��, �ڵ� �߻�ȭ�� ���� ����

	�߻�ȭ : ���� ����(���� ����)�� ����ȭ / ��ȣȭ / ����ȭ�� ���ؼ�
	������ ������ + �ڵ������� �䳻�� ��

	�߻�ȭ�� �߿��� ���� : �ڵ带 ¥�� ����� �������� ������� �̿��ϴ� �͵�
	��� ����� �ϴϱ� ����� �����ϱ� ������ �߿��ϴ�.

	�迭 : �Ӽ��� ������ �������� �����͸� ���� �̸��� �������� ǥ�������ν� �߻�ȭ��
	�Ѵ�.
	����ü : �����͸� Ư�� ����(������ ��Ģ����)�� ��� �߻�ȭ�� �Ѵ�.
	�Լ� : �ڵ带 Ư�� ��� ������ ��� �߻�ȭ�� �Ѵ�.

	����ü�� ���� ����?
	Ư�� �������� ������ ���� �������� ���� ��

	����
	������ �̸�, ������ HP, ������ ���ݷ�, ������ �̵���, ...

	����ü�� �����ϴ� ���
	����ü�� ����ϴ� �Լ� ������ �����Ѵ�. (�ش� �Լ��� ��)
*/

struct Monster	// ����� ���� ������
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
	// 1. �޸� ���� �������� ����.
	string monsterName[5];
	int monsterHP[5];
	float monsterMoveSpeed[5];
	float monsterAttackValue[5];

	Monster monster;
	Monster monsters[5];

	monsters[0].name = "���ذ�";
	monsters[0].HP = 100;
	monsters[0].moveSpeed = 3.0f;
	monsters[0].attackValue = 5.0f;

	/* 
	�ǽ�1. Priates(����)��� ����ü�� �ϳ� �����Ѵ�.
	������ �Ӽ� : �̸�, HP(int), ���ݷ�(int), ����(int), ���ǵ�(float)
	lupi��� �̸��� ����ü ������ ������ �Ŀ�
	lupi�� �� ���� �Ӽ��� ���� �Է��ϰ� ����غ���.

	+ ���ǵ尡 3.0 �̻��̸� 
	'�̸�'�� ���ǵ�� 5.0�Դϴ�. (����)
	'�̸�'�� ���ǵ�� 5.0�Դϴ�. (����)
	*/
	PiratesGroup strawHatPirates;
	strawHatPirates.name = "�������� ������";
	strawHatPirates.buffValue = 2.3f;
	
	strawHatPirates.members[0].name = "����";
	strawHatPirates.members[0].HP = 300;
	strawHatPirates.members[0].atk = 100;
	strawHatPirates.members[0].def = 50;
	strawHatPirates.members[0].speed = 4.0f;

	strawHatPirates.members[1].name = "����";
	strawHatPirates.members[1].HP = 250;
	strawHatPirates.members[1].atk = 120;
	strawHatPirates.members[1].def = 30;
	strawHatPirates.members[1].speed = 2.0f;

	strawHatPirates.members[2].name = "���";
	strawHatPirates.members[2].HP = 350;
	strawHatPirates.members[2].atk = 80;
	strawHatPirates.members[2].def = 70;
	strawHatPirates.members[2].speed = 6.0f;


	for (int i = 0; i < 3; i++)
	{
		cout << "�̸� : " << strawHatPirates.members[i].name << endl;
		cout << strawHatPirates.members[i].name << "�� ü���� " << strawHatPirates.members[i].HP << "�Դϴ�." << endl;
		cout << strawHatPirates.members[i].name << "�� ���ݷ��� " << strawHatPirates.members[i].atk << "�Դϴ�." << endl;
		cout << strawHatPirates.members[i].name << "�� ������ " << strawHatPirates.members[i].def << "�Դϴ�." << endl;
		if (strawHatPirates.members[i].speed >= 3.0f)
			cout << strawHatPirates.members[i].name << "�� ���ǵ�� " << strawHatPirates.members[i].speed << "�Դϴ�. (����)" << endl;
		else
			cout << strawHatPirates.members[i].name << "�� ���ǵ�� " << strawHatPirates.members[i].speed << "�Դϴ�. (����)" << endl;
		cout << endl;
	}
	
	/*
	�ǽ�2.
	�л��� ����üȭ �ؼ� ���� �Ӽ��� ��������.
	�̸�, ����, 1~4�г������ ����, �������ɿ���
	�л��� ������ cin���� �Է¹޴´�. (3��)

	+ �л��� ��ȣ�� �Է��ϸ�
	�ش� �л��� �������� ��µȴ�.

	+ �л��� �̸��� ����ϸ�
	�ش� �л��� �������� ��µȴ�.
	*/

	Student students[3];
	for (int i = 0; i < 3; i++)
	{
		cout << "�л��� �̸��� �Է��Ͻÿ� : ";
		cin >> students[i].name;
		cout << "�л��� ���̸� �Է��Ͻÿ� : ";
		cin >> students[i].age;
		cout << "�л��� ��� ������ �Է��Ͻÿ� : ";
		cin >> students[i].GPA;
		if (students[i].GPA >= 3.0f)
			students[i].canGraduate = true;
		else
			students[i].canGraduate = false;

	}
	
	int searchNumber;
	cout << "��ȸ�Ϸ��� �л��� ��ȣ�� �Է��Ͻÿ� : ";
	cin >> searchNumber;
	if (cin.fail() || searchNumber < 0 || searchNumber > 3 - 1)
	{
		cout << "Error : �߸��� �Է�" << endl;
		return 1;
	}
	cout << "�̸� : " << students[searchNumber].name << endl;
	cout << "���� : " << students[searchNumber].age << endl;
	cout << "��� ���� : " << students[searchNumber].GPA << endl;
	cout << boolalpha << "���� ���� ���� : " << students[searchNumber].canGraduate << endl;

	string searchName;
	cout << "��ȸ�Ϸ��� �л��� �̸��� �Է��Ͻÿ� : ";
	cin >> searchName;
	for (int i = 0; i < 3; i++)
	{
		if (students[i].name == searchName)
		{
			cout << "�̸� : " << students[i].name << endl;
			cout << "���� : " << students[i].age << endl;
			cout << "��� ���� : " << students[i].GPA << endl;
			cout << "���� ���� ���� : " << students[i].canGraduate << endl;
			break;
		}
	}
}
