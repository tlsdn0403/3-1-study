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

	Mesh** m_ppMeshes = NULL;
	int m_nMeshes = 0;

	Mesh * m_pMesh = NULL;
private:
	int m_nReferences = 0;

public:
	void AddRef() { m_nReferences++; }
	void Release() {
		if (--m_nReferences <= 0)
			delete this;
	}

protected: 
	
	
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
	
	void SetMesh(int nIndex, Mesh* pMesh);
	void SetMesh( Mesh* pMesh);
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

class CHeightMapTerrain : public GameObject
{
public:
	CHeightMapTerrain(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
		* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, LPCTSTR pFileName, int
		nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT4
		xmf4Color);
	virtual ~CHeightMapTerrain();
private:
	CHeightMapImage* m_pHeightMapImage;
		//높이 맵의 가로와 세로 크기이다.
		int m_nWidth;
		int m_nLength;
		//지형을 실제로 몇 배 확대할 것인가를 나타내는 스케일 벡터이다.
		XMFLOAT3
			m_xmf3Scale;
public:
	//지형의 높이를 계산하는 함수이다(월드 좌표계). 높이 맵의 높이에 스케일의 y를 곱한 값이다.
	float GetHeight(float x, float z) {
		return(m_pHeightMapImage->GetHeight(x /
			m_xmf3Scale.x, z / m_xmf3Scale.z) * m_xmf3Scale.y);
	}
	//지형의 법선 벡터를 계산하는 함수이다(월드 좌표계). 높이 맵의 법선 벡터를 사용한다.
	XMFLOAT3 GetNormal(float x, float z) {
		return(m_pHeightMapImage->GetHeightMapNormal(int(x / m_xmf3Scale.x), int(z /
			m_xmf3Scale.z)));
	}
	int GetHeightMapWidth() { return(m_pHeightMapImage->GetHeightMapWidth()); }
	int GetHeightMapLength() { return(m_pHeightMapImage->GetHeightMapLength()); }
	XMFLOAT3 GetScale() { return(m_xmf3Scale); }
	//지형의 크기(가로/세로)를 반환한다. 높이 맵의 크기에 스케일을 곱한 값이다.
	float GetWidth() { return(m_nWidth * m_xmf3Scale.x); }
	float GetLength() { return(m_nLength * m_xmf3Scale.z); }
};
	