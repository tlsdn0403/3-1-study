#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Player.h"

class CGameScene
{
public:
	CGameScene(CPlayer *pPlayer);
	virtual ~CGameScene();

private:
	int							m_nObjects = 0;
	CGameObject					**m_ppObjects = NULL;

	CPlayer*					m_pPlayer = NULL;

public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
};

