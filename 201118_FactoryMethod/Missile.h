#pragma once
class Missile
{
public:
	virtual void Move() = 0; // ���� ���� �Լ�
	virtual void Notice() = 0;

public:
	Missile() {}
	~Missile() {}
};

// �߻�� ���� ������ ���ư��� �̻���
class NormalMissile : public Missile
{
	virtual void Move();
	virtual void Notice();

public:
	NormalMissile() {}
	~NormalMissile();
};

// ���� �ð� ������ ���� ���ӹ߻�Ǵ� �̻���
class LazerMissile :public Missile
{
	virtual void Move();
	virtual void Notice();

public:
	LazerMissile() {}
	~LazerMissile();
};

// Ÿ���� ���� ������ ����� �̻���
class HomingMissile : public Missile {
	virtual void Move();
	virtual void Notice();

public:
	HomingMissile() {}
	~HomingMissile();
};
