#include "stdafx.h"
#include "GameObject.h"
#include "Shader.h"

inline float RandF(float fMin, float fMax)
{
	return(fMin + ((float)rand() / (float)RAND_MAX) * (fMax - fMin));
}

XMVECTOR RandomUnitVectorOnSphere()
{
	XMVECTOR xmvOne = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR xmvZero = XMVectorZero();

	while (true)
	{
		XMVECTOR v = XMVectorSet(RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), 0.0f);
		if (!XMVector3Greater(XMVector3LengthSq(v), xmvOne)) return(XMVector3Normalize(v));
	}
}


GameObject::GameObject() {
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
}

GameObject::~GameObject() {
	if (m_pMesh) 
		m_pMesh->Release();
}
void GameObject::RotateTowardsPlayer(XMFLOAT3 playerPosition)
{
	// ������Ʈ�� ��ġ
	XMFLOAT3 objectPosition = GetPosition();

	// �÷��̾ ���� ���� ���� ���
	XMFLOAT3 directionToPlayer = Vector3::Subtract(playerPosition, objectPosition);
	directionToPlayer = Vector3::Normalize(directionToPlayer);


	directionToPlayer.x = -directionToPlayer.x; // x�� ���� ����


	// �����͸� y������
	XMFLOAT3 upVector = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// LookToLH�� ����Ͽ� ȸ�� ��� ���
	XMFLOAT4X4 rotationMatrix = Matrix4x4::LookToLH(objectPosition, directionToPlayer, upVector);

	// ������Ʈ�� ȸ�� ��ȯ ����
	SetRotationTransform(&rotationMatrix);
}
void GameObject::SetRotationTransform(XMFLOAT4X4* pmxf4x4Transform)
{
	m_xmf4x4World._11 = pmxf4x4Transform->_11; m_xmf4x4World._12 = pmxf4x4Transform->_12; m_xmf4x4World._13 = pmxf4x4Transform->_13;
	m_xmf4x4World._21 = pmxf4x4Transform->_21; m_xmf4x4World._22 = pmxf4x4Transform->_22; m_xmf4x4World._23 = pmxf4x4Transform->_23;
	m_xmf4x4World._31 = pmxf4x4Transform->_31; m_xmf4x4World._32 = pmxf4x4Transform->_32; m_xmf4x4World._33 = pmxf4x4Transform->_33;
}
void GameObject::InitializeBullets()
{

	{
		m_pBullets = new CBulletObject(m_fBulletEffectiveRange);
		XMFLOAT3 xmf3Position = GetPosition();

		m_pBullets->SetPosition(xmf3Position);
		m_pBullets->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 1.0f));
		m_pBullets->SetRotationSpeed(1.0f);
		m_pBullets->SetMovingSpeed(30.0f);
		m_pBullets->SetActive(false);
	}

}
void GameObject::Move(XMFLOAT3& xmf3Shift, float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Movement = Vector3::ScalarProduct(xmf3Shift, fDistance, false);
	xmf3Position = Vector3::Add(xmf3Position, xmf3Movement);
	SetPosition(xmf3Position);
}
void GameObject::Rotate(XMFLOAT3* pxmf3Axis, float fAngle)
{
	if (!pxmf3Axis) return;
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationAxis(*pxmf3Axis, fAngle);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}
void GameObject::SetShader(Shader *pShader) {
	if (m_pShader) m_pShader->Release();
	m_pShader = pShader;
	if (m_pShader) m_pShader->AddRef();
}

void GameObject::SetMesh(Mesh *pMesh) {
	if (m_pMesh) m_pMesh->Release();
	m_pMesh = pMesh;
	if (m_pMesh) m_pMesh->AddRef();
}

void GameObject::ReleaseUploadBuffers() {
	//���� ���۸� ���� ���ε� ���۸� �Ҹ��Ų��.
	if (m_pMesh) m_pMesh->ReleaseUploadBuffers();
}

void GameObject::Rotate(float fPitch, float fYaw, float fRoll) //x,y,z ������ ���ŭ
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationYawPitchRoll(fPitch, fYaw, fRoll);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);  //ȸ�� ����� ������ ���ؾ����� ������ �ǹ̰� �ȴ�.
}

void GameObject::Rotate(XMFLOAT3& xmf3RotationAxis, float fAngle)
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationAxis(xmf3RotationAxis, fAngle);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void GameObject::Animate(float fTimeElapsed) {
	//������ ������Ʈ�� ȸ���� ��Ű�� �̵��� ��Ų��.
	if (m_fRotationSpeed != 0.0f) Rotate(m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
	if (m_fMovingSpeed != 0.0f) Move(m_xmf3MovingDirection, m_fMovingSpeed * fTimeElapsed);
	UpdateBoundingBox();
}

void GameObject::OnPrepareRender() {

}

void GameObject::Render(ID3D12GraphicsCommandList *pd3dCommandList, Camera *pCamera) {
	OnPrepareRender();
	
	// ��ü�� ������ ���̴� ����(��� ����)�� ����
	UpdateShaderVariables(pd3dCommandList);
	if (m_pShader) {
		m_pShader->UpdateShaderVariable(pd3dCommandList, &m_xmf4x4World);
		m_pShader->Render(pd3dCommandList, pCamera);
	}

	//���� ��ü�� �޽��� ����Ǿ� ������ �޽��� �������Ѵ�.
	if (m_pMesh)
		m_pMesh->Render(pd3dCommandList);
}


void GameObject::Revolve(const XMFLOAT3& center, const XMFLOAT3& axis, float angleDegrees)
{
	// 1. ���� ��ġ���� �߽��������� ����
	XMFLOAT3 pos = GetPosition();
	XMVECTOR vPos = XMLoadFloat3(&pos);
	XMVECTOR vCenter = XMLoadFloat3(&center);
	XMVECTOR vDir = vPos - vCenter;

	// 2. ȸ�� ��� ����
	XMMATRIX mRotate = XMMatrixRotationAxis(XMLoadFloat3(&axis), XMConvertToRadians(angleDegrees));

	// 3. ���� ȸ��
	vDir = XMVector3TransformNormal(vDir, mRotate);

	// 4. ȸ���� ���͸� �߽����� ����
	vPos = vCenter + vDir;

	// 5. ��ġ ����
	XMFLOAT3 newPos;
	XMStoreFloat3(&newPos, vPos);
	SetPosition(newPos);
}
void GameObject::CreateShaderVariables(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList){

}

void GameObject::UpdateShaderVariables(ID3D12GraphicsCommandList * pd3dCommandList){
	XMFLOAT4X4 xmf4x4World;
	// ���� ��ġ ����
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));
	
	// ��ü�� ���� ��ȯ ����� ��Ʈ ���(32-��Ʈ ��)�� ���Ͽ� ���̴� ����(��� ����)�� �����Ѵ�.
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0); 
}

void GameObject::ReleaseShaderVariables(){

}
void GameObject::UpdateBoundingBox()
{
	if (m_pMesh) {
		// 1. ����ǥ�� OBB (��ŷ��)
		m_xmModelOOBB = m_pMesh->m_xmOOBB; // Mesh �������� ���� OBB

		// 2. ������ǥ�� OBB (�浹��, �Ѿ� ��)
		m_pMesh->m_xmOOBB.Transform(m_xmWorldOOBB, XMLoadFloat4x4(&m_xmf4x4World));
		XMStoreFloat4(&m_xmWorldOOBB.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmWorldOOBB.Orientation)));
	}
}
XMFLOAT3 GameObject::GetPosition(){
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

// ���� ��ü�� ���� z-�� ���͸� ��ȯ
XMFLOAT3 GameObject::GetLook(){
	XMFLOAT3 Look(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33);
	return(Vector3::Normalize(Look));
}

// ���� ��ü�� ���� y-�� ���͸� ��ȯ
XMFLOAT3 GameObject::GetUp(){
	XMFLOAT3 UP(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23);
	return(Vector3::Normalize(UP));
}

// ���� ��ü�� ���� x-�� ���͸� ��ȯ
XMFLOAT3 GameObject::GetRight(){
	XMFLOAT3 RIGHT(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13);
	return(Vector3::Normalize(RIGHT));
}

RotatingObject::RotatingObject() {
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 90.0f;
}

// ���� ��ü�� ���� x-�� �������� �̵�
void GameObject::MoveStrafe(float fDistance) {
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
	GameObject::SetPosition(xmf3Position);
}

// ���� ��ü�� ���� y-�� �������� �̵�
void GameObject::MoveUp(float fDistance) {
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
	GameObject::SetPosition(xmf3Position);
}

// ���� ��ü�� ���� z-�� �������� �̵�
void GameObject::MoveForward(float fDistance) {
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
	GameObject::SetPosition(xmf3Position);
}

// ���� ��ü�� �־��� ������ ȸ��
//void GameObject::Rotate(float fPitch, float fYaw, float fRoll) {
//	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch), XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
//	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
//}

RotatingObject::~RotatingObject() {

}

void RotatingObject::Animate(float fTimeElapsed) {
	GameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
}

void GameObject::SetPosition(float x, float y, float z){
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;

}

void GameObject::SetPosition(XMFLOAT3 xmf3Position){
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}


void GameObject::GenerateRayForPicking(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection)
{
	//ī�޶� ��ǥ�踦 �� ��ǥ��� �ٲ��ִ� ����� �ǹ̰� �ȴ�.
	XMMATRIX xmmtxToModel = XMMatrixInverse(NULL, XMLoadFloat4x4(&m_xmf4x4World) * xmmtxView);  //���庯ȯ ��İ� ī�޶� ��ȯ ����� ���Ѱ��� ������� ���Ѵ�.  

	XMFLOAT3 xmf3CameraOrigin(0.0f, 0.0f, 0.0f);
	xmvPickRayOrigin = XMVector3TransformCoord(XMLoadFloat3(&xmf3CameraOrigin), xmmtxToModel); //ī�޶� ��ǥ���� 0,0,0�� �� ��ǥ��� �ٲ��ִ� ��ȯ.
	xmvPickRayDirection = XMVector3TransformCoord(xmvPickPosition, xmmtxToModel); //��ŷ �����ǵ� �� ��ǥ��� �ٲ��ش�.

	xmvPickRayDirection = XMVector3Normalize(xmvPickRayDirection - xmvPickRayOrigin); //�� ��ǥ���� ������ ����
}

int GameObject::PickObjectByRayIntersection(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, float* pfHitDistance) //������ , ī�޶� ��ȯ���
{
	int nIntersected = 0;
	if (m_pMesh)
	{
		XMVECTOR xmvPickRayOrigin, xmvPickRayDirection;
		//�츮�� �浹�̶�� �ϴ� ���� ������ǥ�Կ��� �� ���̴�.
		GenerateRayForPicking(xmvPickPosition, xmmtxView, xmvPickRayOrigin, xmvPickRayDirection); //������ ������ǥ���� ���ͷ� �����.
		//xmvPickRayOrigin�� xmvPickRayDirection�� ������ǥ���� ���Ͱ� �ȴ�.

		//�ٿ�� �ڽ��� ���� �浹�˻縦 �����ϰ� �ٿ�� �ڽ� �ȿ� �ִ� �޽��� ���ؼ� �浹 �˻縦 �ϰڴ�.
		nIntersected = m_pMesh->CheckRayIntersection(xmvPickRayOrigin, xmvPickRayDirection, pfHitDistance);  //���⼭�� ����ǥ�Կ��� ��ŷ�� �ϰڴ�.
	}
	return(nIntersected);
}

//------------------------------------------------------------------------------------------------------------------------
//  ���� ������Ʈ
//------------------------------------------------------------------------------------------------------------------------


XMFLOAT3 CExplosiveObject::m_pxmf3SphereVectors[EXPLOSION_DEBRISES];
Mesh* CExplosiveObject::m_pExplosionMesh = NULL;

CExplosiveObject::CExplosiveObject()
{
}

CExplosiveObject::~CExplosiveObject()
{
}

void CExplosiveObject::PrepareExplosion(ID3D12Device* g_pd3dDevice , ID3D12GraphicsCommandList* g_pd3dCommandList)
{
    for (int i = 0; i < EXPLOSION_DEBRISES; i++) XMStoreFloat3(&m_pxmf3SphereVectors[i], ::RandomUnitVectorOnSphere());


    m_pExplosionMesh = new CubeMeshDiffused(g_pd3dDevice, g_pd3dCommandList, 0.5f, 0.5f, 0.5f);
}

void CExplosiveObject::Animate(float fElapsedTime)
{
    if (m_bBlowingUp)
    {
        m_fElapsedTimes += fElapsedTime;
        if (m_fElapsedTimes <= m_fDuration)
        {
            XMFLOAT3 xmf3Position = GetPosition();
            for (int i = 0; i < EXPLOSION_DEBRISES; i++)
            {
                m_pxmf4x4Transforms[i] = Matrix4x4::Identity();
                m_pxmf4x4Transforms[i]._41 = xmf3Position.x + m_pxmf3SphereVectors[i].x * m_fExplosionSpeed * m_fElapsedTimes;
                m_pxmf4x4Transforms[i]._42 = xmf3Position.y + m_pxmf3SphereVectors[i].y * m_fExplosionSpeed * m_fElapsedTimes;
                m_pxmf4x4Transforms[i]._43 = xmf3Position.z + m_pxmf3SphereVectors[i].z * m_fExplosionSpeed * m_fElapsedTimes;
                m_pxmf4x4Transforms[i] = Matrix4x4::Multiply(Matrix4x4::RotationAxis(m_pxmf3SphereVectors[i], m_fExplosionRotation * m_fElapsedTimes), m_pxmf4x4Transforms[i]);
            }
        }
        else
        {
            m_bBlowingUp = false;
            blowed = true;
            m_fElapsedTimes = 0.0f;
        }
    }
    else
    {
        GameObject::Animate(fElapsedTime);
    }
}

void CExplosiveObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera)
{
	if (m_bBlowingUp)
	{
		for (int i = 0; i < EXPLOSION_DEBRISES; i++)
		{
			XMFLOAT4X4 xmf4x4World = m_pxmf4x4Transforms[i];
			// XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&xmf4x4World))); // ���̴����� �˾Ƽ� ó���� ���� ����

			if (m_pShader)
			{
				m_pShader->UpdateShaderVariable(pd3dCommandList, &xmf4x4World);
				m_pShader->Render(pd3dCommandList, pCamera);
			}
			if (m_pExplosionMesh)
				m_pExplosionMesh->Render(pd3dCommandList);
		}
	}
	else
	{
		GameObject::Render(pd3dCommandList, pCamera);
	}
}

//------------------------------------------------------------------------------------------------------------------------
//  �ٴ�
//------------------------------------------------------------------------------------------------------------------------


CFloorObject::CFloorObject()
{
}

CFloorObject::~CFloorObject()
{
}

void CFloorObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera)
{
    // �� ���(��)�� ������
    for (int i = 0; i < 6; ++i)
    {
        // �� ����� ��ġ�� ���⿡ �°� ���� ����� �����ؾ� ��
        // ����: ����� ������ ��ġ�� �̿��� ��ȯ ����� �����
        XMFLOAT4 plane = m_pxmf4WallPlanes[i];

        // ����� ���� ����
        XMFLOAT3 normal(plane.x, plane.y, plane.z);
        // ��� ���� �� �� (���� * d)
        XMFLOAT3 position(normal.x * plane.w, normal.y * plane.w, normal.z * plane.w);

        // ���� ��� ���� (���� ������ z������ �ϴ� ���� ���)
        XMMATRIX mWorld = XMMatrixIdentity();

        // ������ (0,1,0)�̸� �ٴ�, (0,-1,0)�̸� õ��, (1,0,0) ���� ��
        // �� ����� ���⿡ ���� ȸ�� ����� ����
        if (normal.x == 1.0f)      mWorld = XMMatrixRotationZ(XMConvertToRadians(-90.0f));
        else if (normal.x == -1.0f) mWorld = XMMatrixRotationZ(XMConvertToRadians(90.0f));
        else if (normal.y == 1.0f)  mWorld = XMMatrixIdentity();
        else if (normal.y == -1.0f) mWorld = XMMatrixRotationX(XMConvertToRadians(180.0f));
        else if (normal.z == 1.0f)  mWorld = XMMatrixRotationX(XMConvertToRadians(90.0f));
        else if (normal.z == -1.0f) mWorld = XMMatrixRotationX(XMConvertToRadians(-90.0f));

        // ��ġ ����
        mWorld.r[3] = XMVectorSet(position.x, position.y, position.z, 1.0f);

        // ���� ����� float4x4�� ��ȯ
        XMFLOAT4X4 xmf4x4World;
        XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(mWorld));
        pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);

        if (m_pShader)
        {
            m_pShader->UpdateShaderVariable(pd3dCommandList, &xmf4x4World);
            m_pShader->Render(pd3dCommandList, pCamera);
        }
        if (m_pMesh)
            m_pMesh->Render(pd3dCommandList);
    }
}


CBulletObject::CBulletObject(float fEffectiveRange)
{
	m_fBulletEffectiveRange = fEffectiveRange;
}

CBulletObject::~CBulletObject()
{
}

void CBulletObject::SetFirePosition(XMFLOAT3 xmf3FirePosition)
{
	m_xmf3FirePosition = xmf3FirePosition;
	SetPosition(xmf3FirePosition);
}

void CBulletObject::Reset()
{
	m_pLockedObject = NULL;
	m_fElapsedTimeAfterFire = 0;
	m_fMovingDistance = 0;
	m_fRotationAngle = 0.0f;

	m_bActive = false;
}

void CBulletObject::Animate(float fElapsedTime)
{
	m_fElapsedTimeAfterFire += fElapsedTime;

	float fDistance = m_fMovingSpeed * fElapsedTime;

	if ((m_fElapsedTimeAfterFire > m_fLockingDelayTime) && m_pLockedObject)
	{
		XMFLOAT3 xmf3Position = GetPosition();
		XMVECTOR xmvPosition = XMLoadFloat3(&xmf3Position);

		XMFLOAT3 xmf3LockedObjectPosition = m_pLockedObject->GetPosition();
		XMVECTOR xmvLockedObjectPosition = XMLoadFloat3(&xmf3LockedObjectPosition);
		XMVECTOR xmvToLockedObject = xmvLockedObjectPosition - xmvPosition;
		xmvToLockedObject = XMVector3Normalize(xmvToLockedObject);

		XMVECTOR xmvMovingDirection = XMLoadFloat3(&m_xmf3MovingDirection);
		xmvMovingDirection = XMVector3Normalize(XMVectorLerp(xmvMovingDirection, xmvToLockedObject, 0.25f));
		XMStoreFloat3(&m_xmf3MovingDirection, xmvMovingDirection);
	}
#ifdef _WITH_VECTOR_OPERATION
	XMFLOAT3 xmf3Position = GetPosition();

	m_fRotationAngle += m_fRotationSpeed * fElapsedTime;
	if (m_fRotationAngle > 360.0f) m_fRotationAngle = m_fRotationAngle - 360.0f;

	XMFLOAT4X4 mtxRotate1 = Matrix4x4::RotationYawPitchRoll(0.0f, m_fRotationAngle, 0.0f);

	XMFLOAT3 xmf3RotationAxis = Vector3::CrossProduct(m_xmf3RotationAxis, m_xmf3MovingDirection, true);
	float fDotProduct = Vector3::DotProduct(m_xmf3RotationAxis, m_xmf3MovingDirection);
	float fRotationAngle = ::IsEqual(fDotProduct, 1.0f) ? 0.0f : (float)XMConvertToDegrees(acos(fDotProduct));
	XMFLOAT4X4 mtxRotate2 = Matrix4x4::RotationAxis(xmf3RotationAxis, fRotationAngle);

	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate1, mtxRotate2);

	XMFLOAT3 xmf3Movement = Vector3::ScalarProduct(m_xmf3MovingDirection, fDistance, false);
	xmf3Position = Vector3::Add(xmf3Position, xmf3Movement);
	SetPosition(xmf3Position);
#else
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationYawPitchRoll(0.0f, m_fRotationSpeed * fElapsedTime, 0.0f);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
	XMFLOAT3 xmf3Movement = Vector3::ScalarProduct(m_xmf3MovingDirection, fDistance, false);
	XMFLOAT3 xmf3Position = GetPosition();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Movement);
	SetPosition(xmf3Position);
	m_fMovingDistance += fDistance;
#endif

	UpdateBoundingBox();

	if ((m_fMovingDistance > m_fBulletEffectiveRange) || (m_fElapsedTimeAfterFire > m_fLockingTime))
		Reset();
}