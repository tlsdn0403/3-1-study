#pragma once
const ULONG MAX_SAMPLE_COUNT = 50; // 50ȸ�� ������ ó���ð��� �����Ͽ� ����Ѵ�.

class GameTimer{
private:

	bool m_bHardwareHasPerformanceCounter;
	float m_fTimeScale;
	float m_fTimeElapsed;//������ ������ ���� ������ �ð�
	__int64 m_nCurrentTime;//����ð�
	__int64 m_nLastTime;//������ ������ �ð�
	__int64 m_nPerformanceFrequency;//��ǻ���� performance Frequency
	float m_fFrameTime[MAX_SAMPLE_COUNT]; //������ �ð��� �����ϱ� ���� �迭
	ULONG m_nSampleCount;//������ ������ Ƚ��
	unsigned long m_nCurrentFrameRate; //������ ������ ����Ʈ
	unsigned long m_nFramesPerSecond; //�ʴ� ������ ��
	float m_fFPSTimeElapsed;//������ ����Ʈ ��� �ҿ� �ð�


public:

	GameTimer();
	virtual ~GameTimer();

	void Tick(float fLockFPS = 0.0f);
	unsigned long GetFrameRate(LPTSTR lpszString = NULL, int nCharacters = 0);
	float GetTimeElapsed();
};

// ������ ����Ʈ(Frame Rate)�� ����� ������ Ƚ�� ���� �� �������� �������ϴ� �ð��� 
// ����Ͽ� ����Ѵ�. �� Ƚ���� ��Ÿ���� ����� �����Ѵ�. 

