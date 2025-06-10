#pragma once
#include "Mesh.h"
#include "Camera.h"
#include<array>
class Shader;
class CBulletObject; // ���� ����
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
	XMFLOAT3					m_xmf3MovingDirection = XMFLOAT3(0.0f, 0.0f, 1.0f); //�����̴� ����
	XMFLOAT4X4 m_xmf4x4World;
	void ReleaseUploadBuffers();
	
	virtual void SetMesh(Mesh *pMesh);
	virtual void SetShader(Shader *pShader);
	
	virtual void Animate(float fTimeElapsed);
	virtual void OnPrepareRender();
	
virtual void Render(ID3D12GraphicsCommandList *pd3dCommandListt, Camera *pCamera);
	
	void Rotate(XMFLOAT3 *pxmf3Axis, float fAngle);

public:
	//�ٿ�� ������Ƽ�� �ڽ��� �浹�˻縦 �� ����.
	BoundingOrientedBox			m_xmWorldOOBB = BoundingOrientedBox(); //���� ������Ʈ�� ������ �ִ� �ٿ�� �ڽ��� ���� ��ǥ���̴�.
	BoundingOrientedBox			m_xmModelOOBB = BoundingOrientedBox(); //���� ������Ʈ�� ������ �ִ� �ٿ�� �ڽ��� ���� ��ǥ���̴�.

	GameObject* m_pObjectCollided = NULL; //�ٸ� �浹�� ������Ʈ�� ���� ������
	float						m_fMovingSpeed = 0.0f; //�����̴� �ӵ�
	float						m_fMovingRange = 0.0f;

	XMFLOAT3					m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f); //ȸ����
	float						m_fRotationSpeed = 0.0f; //ȸ�� ����(���ǵ�)
	float						m_fBulletEffectiveRange = 150.0f;

	void RotateTowardsPlayer(XMFLOAT3 playerPosition);
	void UpdateBoundingBox();
	void SetRotationTransform(XMFLOAT4X4* pmxf4x4Transform);

	// ��� ���۸� ����
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	
	// ��� ������ ������ ���� 
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	// ���� ��ü�� ���� ��ȯ ��Ŀ��� ��ġ ����, ���� ���� ��ȯ 
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();
	float getY() { return m_xmf4x4World._42; }
	// ���� ��ü�� ��ġ�� ����
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	// ���� ��ü�� ���� (x-��, y-��, z-��) �����̵�
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);
	void Move(XMFLOAT3& vDirection, float fSpeed);
	// ���� ��ü�� ȸ�� (x-��, y-��, z-��) 

	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
	void Rotate(XMFLOAT3& xmf3RotationAxis, float fAngle);

	void Revolve(const XMFLOAT3& center, const XMFLOAT3& axis, float angleDegrees);



	//�� ��ǥ���� ��ŷ ������ �����Ѵ�.
	void GenerateRayForPicking(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection);
	//ī�޶� ��ǥ���� �� ���� ���� �� ��ǥ���� ��ŷ ������ �����ϰ� ��ü���� ������ �˻��Ѵ�
	int PickObjectByRayIntersection(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, float* pfHitDistance);
};
class CExplosiveObject : public GameObject //���� ������Ʈ���� �Ļ���Ŵ
{
public:
	CExplosiveObject();
	virtual ~CExplosiveObject();

	bool						m_bBlowingUp = false;
	bool	blowed = false;

	std::array<XMFLOAT4X4, EXPLOSION_DEBRISES> m_pxmf4x4Transforms;

	float						m_fElapsedTimes = 0.0f; //���� �����ϰ� �󸶳� �ð��� ��������.
	float						m_fDuration = 2.0f; //���ʵ��� ������ �� ������.
	float						m_fExplosionSpeed = 10.0f; //���ߵǴ� ���� ����ü �ӵ�
	float						m_fExplosionRotation = 720.0f; //ȸ��

	virtual void Animate(float fElapsedTime);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandListt, Camera* pCamera);

public:
	static Mesh* m_pExplosionMesh;
	static XMFLOAT3				m_pxmf3SphereVectors[EXPLOSION_DEBRISES]; //�� ���� ������Ʈ�� ��� �������� �߻��Ŵ






	static void PrepareExplosion(ID3D12Device* g_pd3dDevice, ID3D12GraphicsCommandList* g_pd3dCommandList);
};




class CFloorObject : public GameObject //6���� ���� �ٿ�� �ڽ��� ������ �ִ�.
{
public:
	CFloorObject();
	virtual ~CFloorObject();

public:
	BoundingOrientedBox			m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(); //�ٿ�� �ڽ�

	std::array<XMFLOAT4, 6>  m_pxmf4WallPlanes; //1���� ����� ��Ÿ��

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

