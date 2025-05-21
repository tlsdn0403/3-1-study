#pragma once

#include "GameObject.h"
#include "Camera.h"
#include "Player.h"
class CGameState {
public:
	static enum GameState { TITLE, MENU, GAME , GAME_1, WIN,LOSS};
	GameState GetCurrentState() const { return CurrentState; }
	static GameState CurrentState;
	static void ChangeGameState(GameState state);

public:

	CGameState() = default;

	CGameState(const GameState& CurrentState)
	{
	}
};

class WinScene {
public:
	virtual void Render(HDC hDCFrameBuffer);
	void OnMouseClick(int x, int y);
	bool isExploding = false;
	float angle = 0.0f;
private:

};
class LossScene {
public:
	virtual void Render(HDC hDCFrameBuffer);
	void OnMouseClick(int x, int y);
	bool isExploding = false;
	float angle = 0.0f;
private:

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

#define MAX_OBJECTS       6
class CGameScene_2
{
public:
	CGameScene_2(CPlayer *pPlayer);
	virtual ~CGameScene_2();

	int colNum = 0;
private:
	int							m_nObjects = 0;
	CGameObject_1					**m_ppObjects = NULL;
	CGameObject_1**                m_pObstacle = NULL;
	CFloorObject*				m_pFloorObject = NULL;

	CPlayer*					m_pPlayer = NULL;





#ifdef _WITH_DRAW_AXIS
	CGameObject*				m_pWorldAxis = NULL;
#endif

public:
	

	virtual void BuildObjects();
	virtual void ReleaseObjects();


	void RotateTanksToFacePlayer();
	void CheckObjectByObjectCollisions();
	void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollision();
	void CheckObjectByBulletCollisions();
	void FireBullet();
	void CheckTankIsBlowed();
	void CheckPlayerByBulletCollisions();
	void CheckBulletByWallCollisions();
	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera_1* pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);


	
	//매개변수  (마우스의 x좌표 , y좌표 , 플레이어가 가지고 있는 현재 카메라로)
	CGameObject_1* PickObjectPointedByCursor(int xClient, int yClient, CCamera_1* pCamera);


};

class CScene
{
public:
	CScene();
	~CScene();
	//씬에서 마우스와 키보드 메시지를 처리한다.
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
		* pd3dCommandList);
	void ReleaseObjects();
	bool ProcessInput(UCHAR* pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);
	void ReleaseUploadBuffers();
	//그래픽 루트 시그너쳐를 생성한다.
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();
protected:
	//씬은 게임 객체들의 집합이다. 게임 객체는 셰이더를 포함한다.
	CGameObject** m_ppObjects = NULL;
	int m_nObjects = 0;
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
};