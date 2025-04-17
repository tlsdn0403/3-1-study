#pragma once

#include"Player.h"
#include"Camera.h"
#include"GameObject.h"
class CGameScene_1
{
public:
	CGameScene_1(CPlayer* pPlayer);
	virtual ~CGameScene_1();

	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
	virtual void BuildObjects();
	void Animate(float fElapsedTime);
	virtual void ReleaseObjects();
private:
	int							m_nObjects_1 = 0;
	CGameObject** m_ppObjects_1 = NULL;
	CPlayer* m_pPlayer = NULL;


#ifdef _WITH_DRAW_AXIS
	CGameObject* m_pWorldAxis = NULL;
#endif


	

};

