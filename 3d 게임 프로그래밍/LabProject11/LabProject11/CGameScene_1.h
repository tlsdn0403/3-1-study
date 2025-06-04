#pragma once
#include"Player.h"
#include"Camera.h"
#include"GameObject.h"
class CGameScene_1
{
public:
	CGameScene_1(Player* pPlayer);
	virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignature);
	virtual ~CGameScene_1();
	void changeMovingState(bool b);
	void Animate(float fElapsedTime);
	bool checkMoving();
	void changeDir(DWORD d);
	void changeSpeed(float s);

	void moveCart();


	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera);
	

	virtual void ReleaseObjects();


private:
	DWORD dwDirection = 0;
	int							m_nObjects_1 = 3;
	GameObject** m_ppObjects_1 = NULL;
	Player* m_pPlayer = NULL;
	bool isMovingCart = false;
	int dirNum = 0;
	float speed = 0.1f;
#ifdef _WITH_DRAW_AXIS
	CGameObject* m_pWorldAxis = NULL;
#endif




};
