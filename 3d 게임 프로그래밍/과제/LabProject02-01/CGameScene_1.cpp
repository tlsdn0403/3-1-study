#include "stdafx.h"
#include "CGameScene_1.h"
#include "GraphicsPipeline.h"



CGameScene_1::CGameScene_1(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}
CGameScene_1::~CGameScene_1()
{
}
void CGameScene_1::BuildObjects() {
	CTankMesh* pCubeMesh = new CTankMesh(4.0f, 4.0f, 4.0f);

	m_nObjects_1 = 2;
	m_ppObjects_1 = new CGameObject * [m_nObjects_1];

	m_ppObjects_1[0] = new CGameObject();
	m_ppObjects_1[0]->SetMesh(pCubeMesh);
	m_ppObjects_1[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects_1[0]->SetPosition(-13.5f, 0.0f, +14.0f);
	m_ppObjects_1[0]->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 0.0f));
	m_ppObjects_1[0]->SetRotationSpeed(90.0f);
	m_ppObjects_1[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects_1[0]->SetMovingSpeed(0.0f);

	m_ppObjects_1[1] = new CGameObject();
	m_ppObjects_1[1]->SetMesh(pCubeMesh);
	m_ppObjects_1[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects_1[1]->SetPosition(+13.5f, 0.0f, +14.0f);
	m_ppObjects_1[1]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 1.0f));
	m_ppObjects_1[1]->SetRotationSpeed(180.0f);
	m_ppObjects_1[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects_1[1]->SetMovingSpeed(0.0f);
}
void CGameScene_1::Animate(float fElapsedTime)
{
	for (int i = 0; i < m_nObjects_1; i++) m_ppObjects_1[i]->Animate(fElapsedTime);
}
void CGameScene_1::ReleaseObjects()
{
	for (int i = 0; i < m_nObjects_1; i++) if (m_ppObjects_1[i]) delete m_ppObjects_1[i];
	if (m_ppObjects_1) delete[] m_ppObjects_1;
}

void CGameScene_1::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);
	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	for (int i = 0; i < m_nObjects_1; i++) m_ppObjects_1[i]->Render(hDCFrameBuffer, pCamera);
}
