#pragma once

#include "Player.h"
#include "Scene.h"
#include "Timer.h"
#include"CGameScene_1.h"

class CGameFramework
{
public:
	CGameFramework() { }
	~CGameFramework() { }

private:
	HINSTANCE					m_hInstance = NULL;
	HWND						m_hWnd = NULL;

	bool						m_bActive = true;

	RECT						m_rcClient;

    HDC							m_hDCFrameBuffer = NULL;
    HBITMAP						m_hBitmapFrameBuffer = NULL;
    HBITMAP						m_hBitmapSelect = NULL;

	CPlayer*					m_pPlayer = NULL;
	
	CGameState* pGameState = new CGameState();;
	StartScene*					pStartScene = NULL;
	MenuScene* pMenuScene = NULL;
	CGameScene*						m_pScene = NULL;
	CGameScene_1*					m_pScene_1 = nullptr;


	CGameObject*				m_pLockedObject = NULL;

	CGameTimer					m_GameTimer;

	POINT						m_ptOldCursorPos;

	_TCHAR						m_pszFrameRate[50];


public:
	void OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void BuildFrameBuffer();
	void ClearFrameBuffer(DWORD dwColor);
	void PresentFrameBuffer();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput(); //사용자 입력을 받아드림
	void AnimateObjects();
	void FrameAdvance();

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void SetActive(bool bActive) { m_bActive = bActive; }


	void ChoiceGameMode();

};

