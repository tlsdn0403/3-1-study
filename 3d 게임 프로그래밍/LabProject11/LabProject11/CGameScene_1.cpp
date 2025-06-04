#include "stdafx.h"
#include "CGameScene_1.h"



#include"Scene.h"




CGameScene_1::CGameScene_1(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}
CGameScene_1::~CGameScene_1()
{
}
void CGameScene_1::changeMovingState(bool b)
{
	isMovingCart = b;
}
void CGameScene_1::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignature) {

}
void CGameScene_1::Animate(float fElapsedTime)
{
	for (int i = 0; i < m_nObjects_1; i++) m_ppObjects_1[i]->Animate(fElapsedTime);
	m_pPlayer->Animate(fElapsedTime);

	if (isMovingCart) {
		moveCart();
	}
}

bool CGameScene_1::checkMoving()
{
	return isMovingCart;
}

void CGameScene_1::changeDir(DWORD d)
{
	dwDirection = d;
}

void CGameScene_1::changeSpeed(float s)
{
	speed = s;
}


void CGameScene_1::moveCart()
{
	m_pPlayer->Move(dwDirection, speed);
	if (m_pPlayer->m_xmf3Position.x > 0.0f && dirNum == 0) {
		changeSpeed(0.05f);
		dirNum = 1;
		m_pPlayer->Rotate(-45.0f, 0.0f, 0.0f);
	}
	else if (m_pPlayer->m_xmf3Position.x > 11.5f && dirNum == 1) {

		m_pPlayer->Rotate(45.0f, 0.0f, 0.0f);
		m_pPlayer->Rotate(0.0f, 90.0f, 0.0f);
		dirNum = 2;
	}
	else if (m_pPlayer->m_xmf3Position.z < -10.0f && dirNum == 2) {
		dirNum = 3;
		m_pPlayer->Rotate(0.0f, 90.0f, 0.0f);
		m_pPlayer->Rotate(45.0f, 0.0f, 0.0f);
		changeSpeed(0.35f);
	}
	else if (m_pPlayer->m_xmf3Position.x < 0.0f && dirNum == 3) {
		dirNum = 4;
		m_pPlayer->Rotate(-45.0f, 0.0f, 0.0f);
		changeSpeed(0.25f);
	}
	else if (m_pPlayer->m_xmf3Position.x < -10.0f && dirNum == 4) {
		dirNum = 5;
		m_pPlayer->Rotate(0.0f, -45.0f, 0.0f);
		m_pPlayer->Rotate(22.5f, 0.0f, 0.0f);
		changeSpeed(0.30f);
	}
	else if (m_pPlayer->m_xmf3Position.x < -20.0f && dirNum == 5) {
		dirNum = 6;
		m_pPlayer->Rotate(-22.5f, 0.0f, 0.0f);
		m_pPlayer->Rotate(0.0f, 45.0f, 0.0f);
		changeSpeed(0.25f);
	}
	else if (m_pPlayer->m_xmf3Position.x < -30.0f && dirNum == 6) {
		dirNum = 7;
		m_pPlayer->Rotate(-22.5f, 0.0f, 0.0f);
		m_pPlayer->Rotate(0.0f, 42.0f, 0.0f);
		changeSpeed(0.15f);
	}
	else if (m_pPlayer->m_xmf3Position.x < -41.5f && dirNum == 7) {
		dirNum = 8;
		m_pPlayer->Rotate(0.0f, -42.0f, 0.0f);
		m_pPlayer->Rotate(22.5f, 0.0f, 0.0f);
		m_pPlayer->Rotate(0.0f, 90.0f, 0.0f);

		changeSpeed(0.1f);
	}
	else if (m_pPlayer->m_xmf3Position.z > 0.0f && dirNum == 8) {
		dirNum = 9;
		m_pPlayer->Rotate(0.0f, 90.0f, 0.0f);

		changeSpeed(0.1f);
	}
	else if (dirNum == 9) {
		if (m_pPlayer->m_xmf3Position.x > -10.0f) {
			dirNum = 1;
			CGameState::ChangeGameState(CGameState::GAME); // 게임 상태로 변경  
		}
	}
}
void CGameScene_1::Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera)
{
}
void CGameScene_1::ReleaseObjects()
{
	for (int i = 0; i < m_nObjects_1; i++) if (m_ppObjects_1[i]) delete m_ppObjects_1[i];
	if (m_ppObjects_1) delete[] m_ppObjects_1;
}




