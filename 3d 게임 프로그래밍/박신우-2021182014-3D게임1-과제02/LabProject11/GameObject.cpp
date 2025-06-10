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
	// 오브젝트의 위치
	XMFLOAT3 objectPosition = GetPosition();

	// 플레이어를 향한 방향 벡터 계산
	XMFLOAT3 directionToPlayer = Vector3::Subtract(playerPosition, objectPosition);
	directionToPlayer = Vector3::Normalize(directionToPlayer);


	directionToPlayer.x = -directionToPlayer.x; // x축 방향 반전


	// 업벡터를 y축으로
	XMFLOAT3 upVector = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// LookToLH를 사용하여 회전 행렬 계산
	XMFLOAT4X4 rotationMatrix = Matrix4x4::LookToLH(objectPosition, directionToPlayer, upVector);

	// 오브젝트의 회전 변환 설정
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
	//정점 버퍼를 위한 업로드 버퍼를 소멸시킨다.
	if (m_pMesh) m_pMesh->ReleaseUploadBuffers();
}

void GameObject::Rotate(float fPitch, float fYaw, float fRoll) //x,y,z 축으로 몇도만큼
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationYawPitchRoll(fPitch, fYaw, fRoll);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);  //회전 행렬의 좌측에 곱해야지만 자전의 의미가 된다.
}

void GameObject::Rotate(XMFLOAT3& xmf3RotationAxis, float fAngle)
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationAxis(xmf3RotationAxis, fAngle);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void GameObject::Animate(float fTimeElapsed) {
	//각각의 오브젝트를 회전을 시키고 이동을 시킨다.
	if (m_fRotationSpeed != 0.0f) Rotate(m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
	if (m_fMovingSpeed != 0.0f) Move(m_xmf3MovingDirection, m_fMovingSpeed * fTimeElapsed);
	UpdateBoundingBox();
}

void GameObject::OnPrepareRender() {

}

void GameObject::Render(ID3D12GraphicsCommandList *pd3dCommandList, Camera *pCamera) {
	OnPrepareRender();
	
	// 객체의 정보를 셰이더 변수(상수 버퍼)로 복사
	UpdateShaderVariables(pd3dCommandList);
	if (m_pShader) {
		m_pShader->UpdateShaderVariable(pd3dCommandList, &m_xmf4x4World);
		m_pShader->Render(pd3dCommandList, pCamera);
	}

	//게임 객체에 메쉬가 연결되어 있으면 메쉬를 렌더링한다.
	if (m_pMesh)
		m_pMesh->Render(pd3dCommandList);
}


void GameObject::Revolve(const XMFLOAT3& center, const XMFLOAT3& axis, float angleDegrees)
{
	// 1. 현재 위치에서 중심점까지의 벡터
	XMFLOAT3 pos = GetPosition();
	XMVECTOR vPos = XMLoadFloat3(&pos);
	XMVECTOR vCenter = XMLoadFloat3(&center);
	XMVECTOR vDir = vPos - vCenter;

	// 2. 회전 행렬 생성
	XMMATRIX mRotate = XMMatrixRotationAxis(XMLoadFloat3(&axis), XMConvertToRadians(angleDegrees));

	// 3. 벡터 회전
	vDir = XMVector3TransformNormal(vDir, mRotate);

	// 4. 회전된 벡터를 중심점에 더함
	vPos = vCenter + vDir;

	// 5. 위치 설정
	XMFLOAT3 newPos;
	XMStoreFloat3(&newPos, vPos);
	SetPosition(newPos);
}
void GameObject::CreateShaderVariables(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList){

}

void GameObject::UpdateShaderVariables(ID3D12GraphicsCommandList * pd3dCommandList){
	XMFLOAT4X4 xmf4x4World;
	// 현재 위치 저장
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));
	
	// 객체의 월드 변환 행렬을 루트 상수(32-비트 값)를 통하여 셰이더 변수(상수 버퍼)로 복사한다.
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0); 
}

void GameObject::ReleaseShaderVariables(){

}
void GameObject::UpdateBoundingBox()
{
	if (m_pMesh) {
		// 1. 모델좌표계 OBB (피킹용)
		m_xmModelOOBB = m_pMesh->m_xmOOBB; // Mesh 생성시의 로컬 OBB

		// 2. 월드좌표계 OBB (충돌용, 총알 등)
		m_pMesh->m_xmOOBB.Transform(m_xmWorldOOBB, XMLoadFloat4x4(&m_xmf4x4World));
		XMStoreFloat4(&m_xmWorldOOBB.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmWorldOOBB.Orientation)));
	}
}
XMFLOAT3 GameObject::GetPosition(){
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

// 게임 객체의 로컬 z-축 벡터를 반환
XMFLOAT3 GameObject::GetLook(){
	XMFLOAT3 Look(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33);
	return(Vector3::Normalize(Look));
}

// 게임 객체의 로컬 y-축 벡터를 반환
XMFLOAT3 GameObject::GetUp(){
	XMFLOAT3 UP(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23);
	return(Vector3::Normalize(UP));
}

// 게임 객체의 로컬 x-축 벡터를 반환
XMFLOAT3 GameObject::GetRight(){
	XMFLOAT3 RIGHT(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13);
	return(Vector3::Normalize(RIGHT));
}

RotatingObject::RotatingObject() {
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 90.0f;
}

// 게임 객체를 로컬 x-축 방향으로 이동
void GameObject::MoveStrafe(float fDistance) {
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
	GameObject::SetPosition(xmf3Position);
}

// 게임 객체를 로컬 y-축 방향으로 이동
void GameObject::MoveUp(float fDistance) {
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
	GameObject::SetPosition(xmf3Position);
}

// 게임 객체를 로컬 z-축 방향으로 이동
void GameObject::MoveForward(float fDistance) {
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
	GameObject::SetPosition(xmf3Position);
}

// 게임 객체를 주어진 각도로 회전
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
	//카메라 좌표계를 모델 좌표계로 바꿔주는 행렬의 의미가 된다.
	XMMATRIX xmmtxToModel = XMMatrixInverse(NULL, XMLoadFloat4x4(&m_xmf4x4World) * xmmtxView);  //월드변환 행렬과 카메라 변환 행렬을 곱한거의 역행렬을 구한다.  

	XMFLOAT3 xmf3CameraOrigin(0.0f, 0.0f, 0.0f);
	xmvPickRayOrigin = XMVector3TransformCoord(XMLoadFloat3(&xmf3CameraOrigin), xmmtxToModel); //카메라 좌표계의 0,0,0을 모델 좌표계로 바꿔주는 변환.
	xmvPickRayDirection = XMVector3TransformCoord(xmvPickPosition, xmmtxToModel); //피킹 포지션도 모델 좌표계로 바꿔준다.

	xmvPickRayDirection = XMVector3Normalize(xmvPickRayDirection - xmvPickRayOrigin); //모델 좌표계의 광선의 방향
}

int GameObject::PickObjectByRayIntersection(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, float* pfHitDistance) //포지션 , 카메라 변환행렬
{
	int nIntersected = 0;
	if (m_pMesh)
	{
		XMVECTOR xmvPickRayOrigin, xmvPickRayDirection;
		//우리는 충돌이라고 하는 것을 월드좌표게에서 할 것이다.
		GenerateRayForPicking(xmvPickPosition, xmmtxView, xmvPickRayOrigin, xmvPickRayDirection); //광선을 월드좌표게의 벡터로 만든다.
		//xmvPickRayOrigin과 xmvPickRayDirection은 월드좌표게의 벡터가 된다.

		//바운딩 박스에 대한 충돌검사를 먼저하고 바운딩 박스 안에 있는 메쉬에 대해서 충돌 검사를 하겠다.
		nIntersected = m_pMesh->CheckRayIntersection(xmvPickRayOrigin, xmvPickRayDirection, pfHitDistance);  //여기서는 모델좌표게에서 피킹을 하겠다.
	}
	return(nIntersected);
}

//------------------------------------------------------------------------------------------------------------------------
//  폭발 오브젝트
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
			// XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&xmf4x4World))); // 셰이더에서 알아서 처리할 수도 있음

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
//  바닥
//------------------------------------------------------------------------------------------------------------------------


CFloorObject::CFloorObject()
{
}

CFloorObject::~CFloorObject()
{
}

void CFloorObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera)
{
    // 각 평면(벽)을 렌더링
    for (int i = 0; i < 6; ++i)
    {
        // 각 평면의 위치와 방향에 맞게 월드 행렬을 생성해야 함
        // 예시: 평면의 법선과 위치를 이용해 변환 행렬을 만든다
        XMFLOAT4 plane = m_pxmf4WallPlanes[i];

        // 평면의 법선 벡터
        XMFLOAT3 normal(plane.x, plane.y, plane.z);
        // 평면 위의 한 점 (법선 * d)
        XMFLOAT3 position(normal.x * plane.w, normal.y * plane.w, normal.z * plane.w);

        // 월드 행렬 생성 (법선 방향을 z축으로 하는 단위 행렬)
        XMMATRIX mWorld = XMMatrixIdentity();

        // 법선이 (0,1,0)이면 바닥, (0,-1,0)이면 천장, (1,0,0) 등은 벽
        // 각 평면의 방향에 따라 회전 행렬을 적용
        if (normal.x == 1.0f)      mWorld = XMMatrixRotationZ(XMConvertToRadians(-90.0f));
        else if (normal.x == -1.0f) mWorld = XMMatrixRotationZ(XMConvertToRadians(90.0f));
        else if (normal.y == 1.0f)  mWorld = XMMatrixIdentity();
        else if (normal.y == -1.0f) mWorld = XMMatrixRotationX(XMConvertToRadians(180.0f));
        else if (normal.z == 1.0f)  mWorld = XMMatrixRotationX(XMConvertToRadians(90.0f));
        else if (normal.z == -1.0f) mWorld = XMMatrixRotationX(XMConvertToRadians(-90.0f));

        // 위치 적용
        mWorld.r[3] = XMVectorSet(position.x, position.y, position.z, 1.0f);

        // 월드 행렬을 float4x4로 변환
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