#pragma once

#include "Mesh.h"
#include "Camera.h"
#include<array>

class CGameObject
{
public:
	CGameObject() { }
	virtual ~CGameObject();

public:
	bool						m_bActive = true;

	CMesh*						m_pMesh = NULL;

	//	�⺻������ ������� ���� �������� ideentity()
	XMFLOAT4X4					m_xmf4x4World = Matrix4x4::Identity();  //���� ��ȯ ���  (�������)

	//�ٿ�� ������Ƽ�� �ڽ��� �浹�˻縦 �� ����.
	BoundingOrientedBox			m_xmOOBB = BoundingOrientedBox(); //���� ������Ʈ�� ������ �ִ� �ٿ�� �ڽ��� ���� ��ǥ���̴�.

	CGameObject*				m_pObjectCollided = NULL; //�ٸ� �浹�� ������Ʈ�� ���� ������

	//������ ��
	DWORD						m_dwColor = RGB(255, 0, 0);

	XMFLOAT3					m_xmf3MovingDirection = XMFLOAT3(0.0f, 0.0f, 1.0f); //�����̴� ����
	float						m_fMovingSpeed = 0.0f; //�����̴� �ӵ�
	float						m_fMovingRange = 0.0f;

	XMFLOAT3					m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f); //ȸ����
	float						m_fRotationSpeed = 0.0f; //ȸ�� ����(���ǵ�)

public:
	void SetActive(bool bActive) { m_bActive = bActive; }
	void SetMesh(CMesh *pMesh) { m_pMesh = pMesh; if (pMesh) pMesh->AddRef(); }

	void SetColor(DWORD dwColor) { m_dwColor = dwColor; }

	void SetRotationTransform(XMFLOAT4X4 *pmxf4x4Transform);

	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3& xmf3Position);

	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	void SetMovingSpeed(float fSpeed) { m_fMovingSpeed = fSpeed; }
	void SetMovingRange(float fRange) { m_fMovingRange = fRange; }

	void SetRotationAxis(XMFLOAT3& xmf3RotationAxis) { m_xmf3RotationAxis = Vector3::Normalize(xmf3RotationAxis); }
	void SetRotationSpeed(float fSpeed) { m_fRotationSpeed = fSpeed; }


;


	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);

	//���� ��ü�� x-��, y-��, z-������ �̵��Ѵ�.
	void Move(XMFLOAT3& vDirection, float fSpeed);

	//���� ��ü�� x-��, y-��, z-���� �������� ȸ���Ѵ�.
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	void Rotate(XMFLOAT3& xmf3Axis, float fAngle);
	void RotateTowardsPlayer(XMFLOAT3 playerPosition);
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	void LookTo(XMFLOAT3& xmf3LookTo, XMFLOAT3& xmf3Up);
	void LookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);

	void UpdateBoundingBox();

	void Render(HDC hDCFrameBuffer, XMFLOAT4X4* pxmf4x4World, CMesh* pMesh);

	//�� -> ���� ��ȯ 
	virtual void OnUpdateTransform();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	void GenerateRayForPicking(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection);
	int PickObjectByRayIntersection(XMVECTOR& xmPickPosition, XMMATRIX& xmmtxView, float* pfHitDistance);
};

class CExplosiveObject : public CGameObject //���� ������Ʈ���� �Ļ���Ŵ
{
public:
	CExplosiveObject();
	virtual ~CExplosiveObject();

	bool						m_bBlowingUp = false;


	std::array<XMFLOAT4X4, EXPLOSION_DEBRISES> m_pxmf4x4Transforms;

	float						m_fElapsedTimes = 0.0f; //���� �����ϰ� �󸶳� �ð��� ��������.
	float						m_fDuration = 2.0f; //���ʵ��� ������ �� ������.
	float						m_fExplosionSpeed = 10.0f; //���ߵǴ� ���� ����ü �ӵ�
	float						m_fExplosionRotation = 720.0f; //ȸ��

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

public:
	static CMesh*				m_pExplosionMesh;
	static XMFLOAT3				m_pxmf3SphereVectors[EXPLOSION_DEBRISES]; //�� ���� ������Ʈ�� ��� �������� �߻��Ŵ

	static void PrepareExplosion();
};

class CFloorObject : public CGameObject //6���� ���� �ٿ�� �ڽ��� ������ �ִ�.
{
public:
	CFloorObject();
	virtual ~CFloorObject();

public:
	BoundingOrientedBox			m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(); //�ٿ�� �ڽ�

	std::array<XMFLOAT4,6>  m_pxmf4WallPlanes; //1���� ����� ��Ÿ��

	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
};


class CBulletObject : public CGameObject
{
public:
	CBulletObject(float fEffectiveRange);
	virtual ~CBulletObject();

public:
	virtual void Animate(float fElapsedTime);

	float						m_fBulletEffectiveRange = 50.0f;
	float						m_fMovingDistance = 0.0f;
	float						m_fRotationAngle = 0.0f;
	XMFLOAT3					m_xmf3FirePosition = XMFLOAT3(0.0f, 0.0f, 1.0f);

	float						m_fElapsedTimeAfterFire = 0.0f;
	float						m_fLockingDelayTime = 0.3f;
	float						m_fLockingTime = 4.0f;
	CGameObject*				m_pLockedObject = NULL;

	void SetFirePosition(XMFLOAT3 xmf3FirePosition);
	void Reset();
};

class CAxisObject : public CGameObject
{
public:
	CAxisObject() { }
	virtual ~CAxisObject() { }

	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
};

//-------------------------------------------------------------------------------------
//  �ѷ��ڽ���
//-------------------------------------------------------------------------------------
class CRollerCoasterRail : public CGameObject
{
public:
	CRollerCoasterRail() {}
	virtual ~CRollerCoasterRail() {}

	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
	
private:
	std::vector<std::pair<XMFLOAT3, XMFLOAT3>> m_vRailSegments;
};

//-------------------------------------------------------------------------------------
//  ��ũ
//-------------------------------------------------------------------------------------