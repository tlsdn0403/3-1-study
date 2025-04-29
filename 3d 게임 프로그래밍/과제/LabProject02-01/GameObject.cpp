#include "stdafx.h"
#include "GameObject.h"
#include "GraphicsPipeline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
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
//CGameObject::CGameObject()
//{
//
//}
CGameObject::CGameObject()
{
	
}
CGameObject::~CGameObject(void)
{
	if (m_pMesh) m_pMesh->Release();
	for (int i = 0; i < BULLETS_1; i++) if (m_pBullets) delete m_pBullets;
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3& xmf3Position)
{
	m_xmf4x4World._41 = xmf3Position.x;
	m_xmf4x4World._42 = xmf3Position.y;
	m_xmf4x4World._43 = xmf3Position.z;
}

XMFLOAT3 CGameObject::GetPosition()
{
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

XMFLOAT3 CGameObject::GetLook()
{
	XMFLOAT3 xmf3LookAt(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33);
	xmf3LookAt = Vector3::Normalize(xmf3LookAt);
	return(xmf3LookAt);
}

XMFLOAT3 CGameObject::GetUp()
{
	XMFLOAT3 xmf3Up(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23);
	xmf3Up = Vector3::Normalize(xmf3Up);
	return(xmf3Up);
}

XMFLOAT3 CGameObject::GetRight()
{
	XMFLOAT3 xmf3Right(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13);
	xmf3Right = Vector3::Normalize(xmf3Right);
	return(xmf3Right);
}

void CGameObject::SetRotationTransform(XMFLOAT4X4* pmxf4x4Transform)
{
	m_xmf4x4World._11 = pmxf4x4Transform->_11; m_xmf4x4World._12 = pmxf4x4Transform->_12; m_xmf4x4World._13 = pmxf4x4Transform->_13;
	m_xmf4x4World._21 = pmxf4x4Transform->_21; m_xmf4x4World._22 = pmxf4x4Transform->_22; m_xmf4x4World._23 = pmxf4x4Transform->_23;
	m_xmf4x4World._31 = pmxf4x4Transform->_31; m_xmf4x4World._32 = pmxf4x4Transform->_32; m_xmf4x4World._33 = pmxf4x4Transform->_33;
}

void CGameObject::MoveStrafe(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Right, fDistance));

	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveUp(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Up, fDistance));

	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveForward(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3LookAt = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3LookAt, fDistance));

	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::Rotate(float fPitch, float fYaw, float fRoll) //x,y,z 축으로 몇도만큼
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationYawPitchRoll(fPitch, fYaw, fRoll);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);  //회전 행렬의 좌측에 곱해야지만 자전의 의미가 된다.
}

void CGameObject::Rotate(XMFLOAT3& xmf3RotationAxis, float fAngle) 
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::RotationAxis(xmf3RotationAxis, fAngle);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}


void CGameObject::RotateTowardsPlayer(XMFLOAT3 playerPosition)
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


void CGameObject::Move(XMFLOAT3& vDirection, float fSpeed)  //방향벡터 , 속도
{
	//월드변환 행렬의 4번째 행이 포지션이니까.
	SetPosition(m_xmf4x4World._41 + vDirection.x * fSpeed, m_xmf4x4World._42 + vDirection.y * fSpeed, m_xmf4x4World._43 + vDirection.z * fSpeed);
}

void CGameObject::LookTo(XMFLOAT3& xmf3LookTo, XMFLOAT3& xmf3Up)
{
	XMFLOAT4X4 xmf4x4View = Matrix4x4::LookToLH(GetPosition(), xmf3LookTo, xmf3Up);
	m_xmf4x4World._11 = xmf4x4View._11; m_xmf4x4World._12 = xmf4x4View._21; m_xmf4x4World._13 = xmf4x4View._31;
	m_xmf4x4World._21 = xmf4x4View._12; m_xmf4x4World._22 = xmf4x4View._22; m_xmf4x4World._23 = xmf4x4View._32;
	m_xmf4x4World._31 = xmf4x4View._13; m_xmf4x4World._32 = xmf4x4View._23; m_xmf4x4World._33 = xmf4x4View._33;
}

void CGameObject::LookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up)
{
	XMFLOAT4X4 xmf4x4View = Matrix4x4::LookAtLH(GetPosition(), xmf3LookAt, xmf3Up);
	m_xmf4x4World._11 = xmf4x4View._11; m_xmf4x4World._12 = xmf4x4View._21; m_xmf4x4World._13 = xmf4x4View._31;
	m_xmf4x4World._21 = xmf4x4View._12; m_xmf4x4World._22 = xmf4x4View._22; m_xmf4x4World._23 = xmf4x4View._32;
	m_xmf4x4World._31 = xmf4x4View._13; m_xmf4x4World._32 = xmf4x4View._23; m_xmf4x4World._33 = xmf4x4View._33;
}

void CGameObject::UpdateBoundingBox()
{
	if (m_pMesh)  //m_pMesh가 널을 가르키지 않을 때
	{
		m_pMesh->m_xmOOBB.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
		XMStoreFloat4(&m_xmOOBB.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBB.Orientation)));
	}
}


void CGameObject::OnUpdateTransform()
{
	m_xmf4x4World = Matrix4x4::Multiply(XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(0.0f), 0.0f), m_xmf4x4World); 

}


void CGameObject::Animate(float fElapsedTime)
{
	//각각의 오브젝트를 회전을 시키고 이동을 시킨다.
	if (m_fRotationSpeed != 0.0f) Rotate(m_xmf3RotationAxis, m_fRotationSpeed * fElapsedTime);
	if (m_fMovingSpeed != 0.0f) Move(m_xmf3MovingDirection, m_fMovingSpeed * fElapsedTime);
	AutoFire(fElapsedTime); // 자동 발사 추가  
	UpdateBoundingBox();
	for (int i = 0; i < BULLETS_1; i++)
	{	
		if (m_pBullets && m_pBullets->m_bActive) m_pBullets->Animate(fElapsedTime);
	}
}

void CGameObject::Render(HDC hDCFrameBuffer, XMFLOAT4X4* pxmf4x4World, CMesh* pMesh)
{
	if (pMesh)//메쉬가 있으면
	{
		CGraphicsPipeline::SetWorldTransform(pxmf4x4World); //그 메쉬를 월드변환 행렬을 사용을 해서 변환

		HPEN hPen = ::CreatePen(PS_SOLID, 0, m_dwColor);
		HPEN hOldPen = (HPEN)::SelectObject(hDCFrameBuffer, hPen);

		pMesh->Render(hDCFrameBuffer); //재귀호출 형태

		::SelectObject(hDCFrameBuffer, hOldPen);
		::DeleteObject(hPen);
	}


}

void CGameObject::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	//바운딩 박스가 카메라 절두체 안에 있으면 랜더하고, 아니면 안한다.
	//월드 좌표게에서의 프러스텀 컬링을 한다.
	/*if (pCamera->IsInFrustum(m_xmOOBB))*/ 
	CGameObject::Render(hDCFrameBuffer, &m_xmf4x4World, m_pMesh);

		if (m_pBullets && m_pBullets->m_bActive)
			m_pBullets->Render(hDCFrameBuffer, pCamera);

}

void CGameObject::GenerateRayForPicking(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection)
{
	//카메라 좌표계를 모델 좌표계로 바꿔주는 행렬의 의미가 된다.
	XMMATRIX xmmtxToModel = XMMatrixInverse(NULL, XMLoadFloat4x4(&m_xmf4x4World) * xmmtxView);  //월드변환 행렬과 카메라 변환 행렬을 곱한거의 역행렬을 구한다.  

	XMFLOAT3 xmf3CameraOrigin(0.0f, 0.0f, 0.0f);
	xmvPickRayOrigin = XMVector3TransformCoord(XMLoadFloat3(&xmf3CameraOrigin), xmmtxToModel); //카메라 좌표계의 0,0,0을 모델 좌표계로 바꿔주는 변환.
	xmvPickRayDirection = XMVector3TransformCoord(xmvPickPosition, xmmtxToModel); //피킹 포지션도 모델 좌표계로 바꿔준다.

	xmvPickRayDirection = XMVector3Normalize(xmvPickRayDirection - xmvPickRayOrigin); //모델 좌표계의 광선의 방향
}

int CGameObject::PickObjectByRayIntersection(XMVECTOR& xmvPickPosition, XMMATRIX& xmmtxView, float* pfHitDistance) //포지션 , 카메라 변환행렬
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
void  CGameObject::FireBullet()
{
	CBulletObject* pBulletObject = NULL;


        if (m_pBullets && !m_pBullets->m_bActive)
		{
			pBulletObject = m_pBullets;

		}
	
	
	if (pBulletObject)
	{
		XMFLOAT3 xmf3Position = GetPosition();
		XMFLOAT3 xmf3Direction = Vector3::ScalarProduct(GetLook(), 1.0f); // 방향 반전
		XMFLOAT3 xmf3FirePosition = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Direction, 6.0f, false));

		pBulletObject->m_xmf4x4World = m_xmf4x4World;

		pBulletObject->SetFirePosition(xmf3FirePosition);
		pBulletObject->SetMovingDirection(xmf3Direction);
		pBulletObject->SetColor(RGB(255, 0, 0));
		pBulletObject->SetActive(true);



		CMissileMesh* pBulletMesh = new CMissileMesh(1.0f, 1.0f, 1.0f);
		pBulletObject->SetMesh(pBulletMesh);


	}
}

void CGameObject::AutoFire(float fElapsedTime)  
{  
  static float fFireCooldown = 0.0f; // 쿨다운 시간  
  static float fInitialDelay = 2.0f; // 초기 지연 시간  

  if (fInitialDelay > 0.0f)  
  {  
      fInitialDelay -= fElapsedTime;  
      return; // 초기 지연 시간 동안 발사하지 않음  
  }  

  fFireCooldown -= fElapsedTime;  

  if (fFireCooldown <= 0.0f)  
  {  
      FireBullet(); // 총알 발사  
      fFireCooldown = 1.0f; // 쿨다운 초기화 (1초)  
  }  
}
void CGameObject::InitializeBullets()
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


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CFloorObject::CFloorObject()
{
}

CFloorObject::~CFloorObject()
{
}

void CFloorObject::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGameObject::Render(hDCFrameBuffer, &m_xmf4x4World, m_pMesh);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
XMFLOAT3 CExplosiveObject::m_pxmf3SphereVectors[EXPLOSION_DEBRISES];
CMesh* CExplosiveObject::m_pExplosionMesh = NULL;

CExplosiveObject::CExplosiveObject()
{
}

CExplosiveObject::~CExplosiveObject()
{
}

void CExplosiveObject::PrepareExplosion()
{
	for (int i = 0; i < EXPLOSION_DEBRISES; i++) XMStoreFloat3(&m_pxmf3SphereVectors[i], ::RandomUnitVectorOnSphere());

	m_pExplosionMesh = new CCubeMesh(0.5f, 0.5f, 0.5f);
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
		CGameObject::Animate(fElapsedTime);
	}
}

void CExplosiveObject::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	if (m_bBlowingUp)
	{
		for (int i = 0; i < EXPLOSION_DEBRISES; i++)
		{
			CGameObject::Render(hDCFrameBuffer , &m_pxmf4x4Transforms[i], m_pExplosionMesh);
		}
	}
	else
	{
		CGameObject::Render(hDCFrameBuffer, pCamera);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
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

	if ((m_fMovingDistance > m_fBulletEffectiveRange) || (m_fElapsedTimeAfterFire > m_fLockingTime)) Reset();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CAxisObject::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetWorldTransform(&m_xmf4x4World);

	m_pMesh->Render(hDCFrameBuffer);
}


void CRollerCoasterRail::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGameObject::Render(hDCFrameBuffer, &m_xmf4x4World, m_pMesh);
	/*CGraphicsPipeline::SetWorldTransform(&m_xmf4x4World);
	m_pMesh->Render(hDCFrameBuffer);*/
}



CShieldObject::CShieldObject(float fShieldDuration, float fShieldRadius)
	: m_fShieldDuration(fShieldDuration), m_fShieldRadius(fShieldRadius)
{
	m_bActive = false;
}

CShieldObject::~CShieldObject()
{
}

void CShieldObject::ActivateShield()
{
	m_bActive = true;
	m_fElapsedTime = 0.0f;
}

void CShieldObject::DeactivateShield()
{
	m_bActive = false;
}

void CShieldObject::Animate(float fElapsedTime)
{
	if (m_bActive)
	{
		m_fElapsedTime += fElapsedTime;
		if (m_fElapsedTime >= m_fShieldDuration)
		{
			DeactivateShield();
		}
	}
}

void CShieldObject::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	if (m_bActive)
	{
		// 쉴드 렌더링 로직 추가 (예: 원형으로 표시)  
		Ellipse(hDCFrameBuffer,
			static_cast<int>(m_xmf4x4World._41 - m_fShieldRadius),
			static_cast<int>(m_xmf4x4World._42 - m_fShieldRadius),
			static_cast<int>(m_xmf4x4World._41 + m_fShieldRadius),
			static_cast<int>(m_xmf4x4World._42 + m_fShieldRadius));
	}
}