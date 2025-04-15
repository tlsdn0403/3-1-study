#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Player.h"



class StartScene {
public:
	virtual void Render(HDC hDCFrameBuffer);
};


class MenuScene {
private:
	std::vector<std::string> m_MenuItems = { "Tutorial", "Level-1", "Level-2", "Start", "End" };
	std::vector<RECT> m_MenuItemRects;

public:
	MenuScene();
	void Render(HDC hDCFrameBuffer);
	void OnMouseClick(int x, int y);
};


class CGameScene
{
public:
	CGameScene(CPlayer *pPlayer);
	virtual ~CGameScene();
	static enum GameState { TITLE, MENU, GAME };

private:
	int							m_nObjects = 0;
	CGameObject					**m_ppObjects = NULL;

	CWallsObject*				m_pWallsObject = NULL;

	CPlayer*					m_pPlayer = NULL;



	GameState CurrentState = MENU;

#ifdef _WITH_DRAW_AXIS
	CGameObject*				m_pWorldAxis = NULL;
#endif

public:
	

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	void ChangeGameState(GameState state);

	void CheckObjectByObjectCollisions();
	void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollision();
	void CheckObjectByBulletCollisions();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	GameState GetCurrentState() const { return CurrentState; }

	//매개변수  (마우스의 x좌표 , y좌표 , 플레이어가 가지고 있는 현재 카메라로)
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);


};

