#pragma once

#include"Player.h"
#include"Camera.h"
#include"GameObject.h"
class CGameScene_1
{
public:
	CGameScene_1(CPlayer* pPlayer);
	virtual ~CGameScene_1();
	void changeMovingState(bool b);
	void Animate(float fElapsedTime);
	bool checkMoving();
	void changeDir(DWORD d);
	void changeSpeed(float s);

	void moveCart();

	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
	virtual void BuildObjects();

	virtual void ReleaseObjects();
	

private:
	DWORD dwDirection = 0;
	int							m_nObjects_1 = 3;
	CGameObject** m_ppObjects_1 = NULL;
	CPlayer* m_pPlayer = NULL;
	bool isMovingCart = false;
	int dirNum = 0;
	float speed = 0.1f;
#ifdef _WITH_DRAW_AXIS
	CGameObject* m_pWorldAxis = NULL;
#endif


	

};

