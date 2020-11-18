#pragma once
class Missile
{
public:
	virtual void Move() = 0; // 순수 가상 함수
	virtual void Notice() = 0;

public:
	Missile() {}
	~Missile() {}
};

// 발사된 최초 각도로 날아가는 미사일
class NormalMissile : public Missile
{
	virtual void Move();
	virtual void Notice();

public:
	NormalMissile() {}
	~NormalMissile();
};

// 일정 시간 딜레이 없이 연속발사되는 미사일
class LazerMissile :public Missile
{
	virtual void Move();
	virtual void Notice();

public:
	LazerMissile() {}
	~LazerMissile();
};

// 타겟을 향해 각도가 봐뀌는 미사일
class HomingMissile : public Missile {
	virtual void Move();
	virtual void Notice();

public:
	HomingMissile() {}
	~HomingMissile();
};
