#pragma once

#include "GameObject.h"
#include "Camera.h"

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	//방향벡터로 별도로 표현을 했다.
	//월드 변환 행렬로 조정을 하는것이 아니라, 이 벡터들을 직접 변경을 하고 이 벡터로부터 월드변환 행렬을 만들어 내는 것이 훨씬 수월하다.
	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3					m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT3					m_xmf3CameraOffset = XMFLOAT3(0.0f, 0.0f, 0.0f); //플레이어와 카메라간의 오프셋 
	XMFLOAT3					m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);

	float						m_fFriction = 125.0f; //마찰력

	//x,y,z축 각도
	float           			m_fPitch = 0.0f; //x축
	float           			m_fYaw = 0.0f;    //y축
	float           			m_fRoll = 0.0f;  //z 축

	CCamera*					m_pCamera = NULL;

public:
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void LookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);

	void Move(DWORD dwDirection, float fDistance);
	void Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity);
	void Move(float x, float y, float z);

	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);

	void SetCameraOffset(XMFLOAT3& xmf3CameraOffset);

	void Update(float fTimeElapsed = 0.016f);

	virtual void OnUpdateTransform();//비행기가 y축 방향이 아니라 z축 방향을 향하도록 만들어줌
	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	void SetCamera(CCamera* pCamera) { m_pCamera = pCamera; }
	CCamera* GetCamera() { return(m_pCamera); }
};

#define BULLETS					50

class CTankPlayer : public CPlayer
{
public:
	CTankPlayer();
	virtual ~CTankPlayer();

	float						m_fBulletEffectiveRange = 150.0f;
	CBulletObject*				m_ppBullets[BULLETS];

	void FireBullet(CGameObject* pLockedObject);

	virtual void OnUpdateTransform();//비행기가 y축 방향이 아니라 z축 방향을 향하도록 만들어줌
	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
};

class CCartPlayer : public CPlayer
{
public:
	CCartPlayer();
	virtual ~CCartPlayer();



	virtual void OnUpdateTransform();//비행기가 y축 방향이 아니라 z축 방향을 향하도록 만들어줌
	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
	virtual void Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity);
	virtual void Move(float x, float y, float z);

};

