#pragma once
#include "pch.h"

class Animation
{
private:
	vector<POINT> vecFrameList;		// key Frame ��ġ ����Ʈ
	vector<int> vecPlayList;		// �÷��� ����Ʈ

	int frameCount;		// ��ü ������ ��
	int frameHeight;	// ������ ���� ũ��
	int frameWidth;		// ������ ���� ũ��

	bool isLoop;		// �ݺ� �Ǵ��� ����
	int nowPlayIdx;		// ���� �÷��� ���� ������ �ε���
	bool isPlaying;		// ���� �÷��� ������ ����

	float keyFrameUpdateTime;	// ������Ʈ ���� �ð�
	float accumulateTime;		// ���� �ð�

public:
	HRESULT Init(int totalWidth, int totalHeight, int frameWidth, int frameHeight);
	void SetPlayFrame(bool isLoop = false, bool isReverse = false);
	void SetPlayFrame(int startFrame, int endFrame, bool isLoop = false, bool isReverse = false);
	void SetPlayFrame(int* arr, int arrLength, bool isLoop = false, bool isReverse = false);
	void UpdateFrame();

	void Start();
	void Stop();
	void Pause();
	void Resume();

	POINT GetFramePoint() {
		return vecFrameList[vecPlayList[nowPlayIdx]];
	}

	void SetKeyFrameUpdateTime(float time) { keyFrameUpdateTime = time; }

	Animation();
	~Animation();

	//new Animation;
	//new Animation();
};
