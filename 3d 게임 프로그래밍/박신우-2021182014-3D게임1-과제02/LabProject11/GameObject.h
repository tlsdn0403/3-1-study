#pragma once
#include "Mesh.h"
#include "Camera.h"
#include<array>
class Shader;
class CBulletObject; // 전방 선언
class GameObject{
public:
	GameObject();
	virtual ~GameObject();

private:
	int m_nReferences = 0;

public:
	void AddRef() { m_nReferences++; }
	void Release() {
		if (--m_nReferences <= 0)
			delete this;
	}

protected: 
	
	Mesh *m_pMesh = NULL;
	Shader *m_pShader = NULL;

public:
	void InitializeBullets();
	void SetMovingSpeed(float fSpeed) { m_fMovingSpeed = fSpeed; }
	void SetMovingRange(float fRange) { m_fMovingRange = fRange; }
	void SetRotationAxis(XMFLOAT3& xmf3RotationAxis) { m_xmf3RotationAxis = Vector3::Normalize(xmf3RotationAxis); }
	void SetRotationSpeed(float fSpeed) { m_fRotationSpeed = fSpeed; }

	CBulletObject* m_pBullets;


	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	XMFLOAT3					m_xmf3MovingDirection = XMFLOAT3(0.0f, 0.0f, 1.0f); //움직이는 방향
	XMFLOAT4X4 m_xmf4x4World;
	void ReleaseUploadBuffers();
	
	virtual void SetMesh(Mesh *pMesh);
	virtual void SetShader(Shader *pShader);
	
	virtual void Animate(float fTimeElapsed);
	virtual void OnPrepareRender();
	
virtual void Render(ID3D12GraphicsCommandList *pd3dCommandListt, Camera *pCamera);
	
	void Rotate(XMFLOAT3 *pxmf3Axis, float fAngle);

public:
	//바운딩 오리엔티드 박스로 충돌검사를 할 것임.
	BoundingOrientedBox			m_xmWorldOOBB = BoundingOrientedBox(); //게임 오브젝트가 가지고 있는 바운딩 박스는 월드 좌표계이다.
	BoundingOrientedBox			m_xmModelOOBB = BoundingOrientedBox(); //게임 오브젝트가 가지고 있는 바운딩 박스는 월드 좌표계이다.

	GameObject* m_pObjectCollided = NULL; //다른 충돌된 오브젝트에 대한 포인터
	float						m_fMovingSpeed = 0.0f; //움직이는 속도
	float						m_fMovingRange = 0.0f;

	XMFLOAT3					m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f); //회전축
	float						m_fRotationSpeed = 0.0f; //회전 각도(스피드)
	float						m_fBulletEffectiveRange = 150.0f;

	void RotateTowardsPlayer(XMFLOAT3 playerPosition);
	void UpdateBoundingBox();
	void SetRotationTransform(XMFLOAT4X4* pmxf4x4Transform);

	// 상수 버퍼를 생성
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	
	// 상수 버퍼의 내용을 갱신 
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	// 게임 객체의 월드 변환 행렬에서 위치 벡터, 방향 벡터 반환 
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();
	float getY() { return m_xmf4x4World._42; }
	// 게임 객체의 위치를 설정
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	// 게임 객체를 로컬 (x-축, y-축, z-축) 방향이동
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);
	void Move(XMFLOAT3& vDirection, float fSpeed);
	// 게임 객체를 회전 (x-축, y-축, z-축) 

	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	void Rotate(XMFLOAT3& xmf3RotationAxis, float fAngle);

	void Revolve(const XMFLOAT3& center, const XMFLOAT3& axis, float angleDegrees);



	//모델 좌표계의 픽킹 광선을 생성한다.
	void GenerateRayForPicking(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection);
	//카메라 좌표계의 한 점에 대한 모델 좌표계의 픽킹 광선을 생성하고 객체와의 교차를 검사한다
	int PickObjectByRayIntersection(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, float* pfHitDistance);
};
class CExplosiveObject : public GameObject //게임 오브젝트에서 파생시킴
{
public:
	CExplosiveObject();
	virtual ~CExplosiveObject();

	bool						m_bBlowingUp = false;
	bool	blowed = false;

	std::array<XMFLOAT4X4, EXPLOSION_DEBRISES> m_pxmf4x4Transforms;

	float						m_fElapsedTimes = 0.0f; //폭발 시작하고 얼마나 시간이 지났는지.
	float						m_fDuration = 2.0f; //몇초동안 폭발을 할 것인지.
	float						m_fExplosionSpeed = 10.0f; //폭발되는 작은 육면체 속도
	float						m_fExplosionRotation = 720.0f; //회전

	virtual void Animate(float fElapsedTime);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandListt, Camera* pCamera);

public:
	static Mesh* m_pExplosionMesh;
	static XMFLOAT3				m_pxmf3SphereVectors[EXPLOSION_DEBRISES]; //이 작은 오브젝트를 모든 방향으로 발사시킴






	static void PrepareExplosion(ID3D12Device* g_pd3dDevice, ID3D12GraphicsCommandList* g_pd3dCommandList);
};




class CFloorObject : public GameObject //6개의 평면과 바운딩 박스를 가지고 있다.
{
public:
	CFloorObject();
	virtual ~CFloorObject();

public:
	BoundingOrientedBox			m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(); //바운딩 박스

	std::array<XMFLOAT4, 6>  m_pxmf4WallPlanes; //1개의 평면을 나타냄

	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandListt, Camera* pCamera);
};





class RotatingObject : public GameObject {
public: 
	RotatingObject(); 
	virtual ~RotatingObject();

private: 
	XMFLOAT3 m_xmf3RotationAxis; float m_fRotationSpeed;

public: 
	void SetRotationSpeed(float fRotationSpeed) {m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) { m_xmf3RotationAxis = xmf3RotationAxis; }
		
	virtual void Animate(float fTimeElapsed);
};


class CBulletObject : public GameObject
{
public:
	CBulletObject(float fEffectiveRange);


	virtual ~CBulletObject();
	bool						m_bActive = false;
public:
	virtual void Animate(float fElapsedTime);
	void SetActive(bool bActive) { m_bActive = bActive; }
	float						m_fBulletEffectiveRange = 50.0f;
	float						m_fMovingDistance = 0.0f;
	float						m_fRotationAngle = 0.0f;
	XMFLOAT3					m_xmf3FirePosition = XMFLOAT3(0.0f, 0.0f, 1.0f);

	float						m_fElapsedTimeAfterFire = 0.0f;
	float						m_fLockingDelayTime = 0.3f;
	float						m_fLockingTime = 4.0f;
	GameObject* m_pLockedObject = NULL;

	void SetFirePosition(XMFLOAT3 xmf3FirePosition);
	void Reset();
};

