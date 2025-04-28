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

	//	기본적으로 단위행렬 값을 가지도록 ideentity()
	XMFLOAT4X4					m_xmf4x4World = Matrix4x4::Identity();  //월드 변환 행렬  (단위행렬)

	//바운딩 오리엔티드 박스로 충돌검사를 할 것임.
	BoundingOrientedBox			m_xmOOBB = BoundingOrientedBox(); //게임 오브젝트가 가지고 있는 바운딩 박스는 월드 좌표계이다.

	CGameObject*				m_pObjectCollided = NULL; //다른 충돌된 오브젝트에 대한 포인터

	//선분의 색
	DWORD						m_dwColor = RGB(255, 0, 0);

	XMFLOAT3					m_xmf3MovingDirection = XMFLOAT3(0.0f, 0.0f, 1.0f); //움직이는 방향
	float						m_fMovingSpeed = 0.0f; //움직이는 속도
	float						m_fMovingRange = 0.0f;

	XMFLOAT3					m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f); //회전축
	float						m_fRotationSpeed = 0.0f; //회전 각도(스피드)

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

	//게임 객체를 x-축, y-축, z-축으로 이동한다.
	void Move(XMFLOAT3& vDirection, float fSpeed);

	//게임 객체를 x-축, y-축, z-축을 기준으로 회전한다.
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

	//모델 -> 월드 변환 
	virtual void OnUpdateTransform();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

	void GenerateRayForPicking(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection);
	int PickObjectByRayIntersection(XMVECTOR& xmPickPosition, XMMATRIX& xmmtxView, float* pfHitDistance);
};

class CExplosiveObject : public CGameObject //게임 오브젝트에서 파생시킴
{
public:
	CExplosiveObject();
	virtual ~CExplosiveObject();

	bool						m_bBlowingUp = false;


	std::array<XMFLOAT4X4, EXPLOSION_DEBRISES> m_pxmf4x4Transforms;

	float						m_fElapsedTimes = 0.0f; //폭발 시작하고 얼마나 시간이 지났는지.
	float						m_fDuration = 2.0f; //몇초동안 폭발을 할 것인지.
	float						m_fExplosionSpeed = 10.0f; //폭발되는 작은 육면체 속도
	float						m_fExplosionRotation = 720.0f; //회전

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);

public:
	static CMesh*				m_pExplosionMesh;
	static XMFLOAT3				m_pxmf3SphereVectors[EXPLOSION_DEBRISES]; //이 작은 오브젝트를 모든 방향으로 발사시킴

	static void PrepareExplosion();
};

class CFloorObject : public CGameObject //6개의 평면과 바운딩 박스를 가지고 있다.
{
public:
	CFloorObject();
	virtual ~CFloorObject();

public:
	BoundingOrientedBox			m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(); //바운딩 박스

	std::array<XMFLOAT4,6>  m_pxmf4WallPlanes; //1개의 평면을 나타냄

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
//  롤러코스터
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
//  탱크
//-------------------------------------------------------------------------------------