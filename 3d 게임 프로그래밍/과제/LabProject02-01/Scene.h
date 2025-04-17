#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Player.h"
class CGameState {
public:
	static enum GameState { TITLE, MENU, GAME , GAME_1};
	GameState GetCurrentState() const { return CurrentState; }
	static GameState CurrentState;
	static void ChangeGameState(GameState state);

public:

	CGameState() = default;

	CGameState(const GameState& CurrentState)
	{
	}
};

class StartScene {
public:
	virtual void Render(HDC hDCFrameBuffer);
	void OnMouseClick(int x, int y);
	bool isExploding = false;
	float angle = 0.0f;
private:
	
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


private:
	int							m_nObjects = 0;
	CGameObject					**m_ppObjects = NULL;

	CWallsObject*				m_pWallsObject = NULL;

	CPlayer*					m_pPlayer = NULL;





#ifdef _WITH_DRAW_AXIS
	CGameObject*				m_pWorldAxis = NULL;
#endif

public:
	

	virtual void BuildObjects();
	virtual void ReleaseObjects();



	void CheckObjectByObjectCollisions();
	void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollision();
	void CheckObjectByBulletCollisions();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);



	//�Ű�����  (���콺�� x��ǥ , y��ǥ , �÷��̾ ������ �ִ� ���� ī�޶��)
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);


};

