#pragma once
#include <vector>

using namespace std;

class Missile;
class MissileFactory
{
private:
	vector<Missile*>	missileDatas;

public:
	void NewMissile();
	virtual Missile* CreateMissile() = 0;
	MissileFactory() {}
	virtual ~MissileFactory();
};

class NormalMissileFactory :public MissileFactory 
{
	virtual Missile* CreateMissile();

public:
	NormalMissileFactory() {}
	virtual ~NormalMissileFactory();
};

class LazerMissileFactory :public MissileFactory
{
	virtual Missile* CreateMissile();

public:
	LazerMissileFactory() {}
	virtual ~LazerMissileFactory();
};

class HomingMissileFactory :public MissileFactory
{
	virtual Missile* CreateMissile();

public:
	HomingMissileFactory() {}
	virtual ~HomingMissileFactory();
};