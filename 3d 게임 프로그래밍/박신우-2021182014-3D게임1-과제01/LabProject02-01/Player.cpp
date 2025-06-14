#include "stdafx.h"
#include "Player.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	if (m_pCamera) delete m_pCamera;
}

void CPlayer::SetPosition(float x, float y, float z)
{
	m_xmf3Position = XMFLOAT3(x, y, z);

	CGameObject::SetPosition(x, y, z);
}

void CPlayer::SetCameraOffset(XMFLOAT3& xmf3CameraOffset)
{
	m_xmf3CameraOffset = xmf3CameraOffset;
	m_pCamera->SetLookAt(Vector3::Add(m_xmf3Position, m_xmf3CameraOffset), m_xmf3Position, m_xmf3Up);  //카메라가 바라보는 지점.
	m_pCamera->GenerateViewMatrix();
}

void CPlayer::Move(DWORD dwDirection, float fDistance)
{
	if (dwDirection)
	{
		XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
		if (dwDirection & DIR_FORWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, fDistance);
		if (dwDirection & DIR_BACKWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, -fDistance);
		if (dwDirection & DIR_RIGHT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, fDistance);
		if (dwDirection & DIR_LEFT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, -fDistance);
		if (dwDirection & DIR_UP) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, fDistance);
		if (dwDirection & DIR_DOWN) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, -fDistance);

		Move(xmf3Shift, true);
	}
}

void CPlayer::Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity)
{
	if (bUpdateVelocity)
	{
		m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Shift);
	}
	else
	{
		m_xmf3Position = Vector3::Add(xmf3Shift, m_xmf3Position);
		m_pCamera->Move(xmf3Shift);
	}
}

void CPlayer::Move(float x, float y, float z)
{
	Move(XMFLOAT3(x, y, z), false);
}

void CPlayer::Rotate(float fPitch, float fYaw, float fRoll)
{
	m_pCamera->OrbitAroundPlayer(this,fPitch, fYaw, fRoll);
	if (fPitch != 0.0f)
	{
		XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Right), XMConvertToRadians(fPitch));
		m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, mtxRotate);
		m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, mtxRotate);
	}
	if (fYaw != 0.0f)
	{
		XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), XMConvertToRadians(fYaw));
		m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, mtxRotate);
		m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, mtxRotate);
	}
	if (fRoll != 0.0f)
	{
		XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Look), XMConvertToRadians(fRoll));
		m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, mtxRotate);
		m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, mtxRotate);
	}

	m_xmf3Look = Vector3::Normalize(m_xmf3Look);
	m_xmf3Right = Vector3::Normalize(Vector3::CrossProduct(m_xmf3Up, m_xmf3Look));
	m_xmf3Up = Vector3::Normalize(Vector3::CrossProduct(m_xmf3Look, m_xmf3Right));
}

void CPlayer::LookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up)
{
	XMFLOAT4X4 xmf4x4View = Matrix4x4::LookAtLH(m_xmf3Position, xmf3LookAt, xmf3Up);
	m_xmf3Right = Vector3::Normalize(XMFLOAT3(xmf4x4View._11, xmf4x4View._21, xmf4x4View._31));
	m_xmf3Up = Vector3::Normalize(XMFLOAT3(xmf4x4View._12, xmf4x4View._22, xmf4x4View._32));
	m_xmf3Look = Vector3::Normalize(XMFLOAT3(xmf4x4View._13, xmf4x4View._23, xmf4x4View._33));
}

void CPlayer::Update(float fTimeElapsed)
{
	Move(m_xmf3Velocity, false);

	m_pCamera->Update(this, m_xmf3Position, fTimeElapsed);
	m_pCamera->GenerateViewMatrix();

	XMFLOAT3 xmf3Deceleration = Vector3::Normalize(Vector3::ScalarProduct(m_xmf3Velocity, -1.0f));
	float fLength = Vector3::Length(m_xmf3Velocity);
	float fDeceleration = m_fFriction * fTimeElapsed;
	if (fDeceleration > fLength) fDeceleration = fLength;
	m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Deceleration, fDeceleration);
}

void CPlayer::Animate(float fElapsedTime)
{
	OnUpdateTransform();

	CGameObject::Animate(fElapsedTime);
}

void CPlayer::OnUpdateTransform()
{
	m_xmf4x4World._11 = m_xmf3Right.x; m_xmf4x4World._12 = m_xmf3Right.y; m_xmf4x4World._13 = m_xmf3Right.z;
	m_xmf4x4World._21 = m_xmf3Up.x; m_xmf4x4World._22 = m_xmf3Up.y; m_xmf4x4World._23 = m_xmf3Up.z;
	m_xmf4x4World._31 = m_xmf3Look.x; m_xmf4x4World._32 = m_xmf3Look.y; m_xmf4x4World._33 = m_xmf3Look.z;
	m_xmf4x4World._41 = m_xmf3Position.x; m_xmf4x4World._42 = m_xmf3Position.y; m_xmf4x4World._43 = m_xmf3Position.z;
}

void CPlayer::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGameObject::Render(hDCFrameBuffer, pCamera);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//    탱크 플레이어
/////////////////////////////////////////////////////////////////////////////////////////////
CTankPlayer::CTankPlayer()
{

	for (int i = 0; i < BULLETS; i++)
	{
		m_ppBullets[i] = new CBulletObject(m_fBulletEffectiveRange);
		m_ppBullets[i]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 1.0f));
		m_ppBullets[i]->SetRotationSpeed(1.0f);
		m_ppBullets[i]->SetMovingSpeed(120.0f);
		m_ppBullets[i]->SetActive(false);
	}
}

CTankPlayer::~CTankPlayer()
{
	for (int i = 0; i < BULLETS; i++) if (m_ppBullets[i]) delete m_ppBullets[i];
}

//void CTankPlayer::Animate(float fElapsedTime)
//{
//	CPlayer::Animate(fElapsedTime);
//
//	for (int i = 0; i < BULLETS; i++)
//	{
//		if (m_ppBullets[i]->m_bActive) m_ppBullets[i]->Animate(fElapsedTime);
//	}
//}

void CTankPlayer::OnUpdateTransform() 
{
	CPlayer::OnUpdateTransform();
	//z축 방향을 가르키도록 바꾸어줌
	m_xmf4x4World = Matrix4x4::Multiply(XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(0.0f), 0.0f), m_xmf4x4World); 
        // 기존 코드에서 미사일 발사 위치와 방향을 수정하여 정확한 방향으로 발사되도록 변경합니다.
}

void CTankPlayer::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CPlayer::Render(hDCFrameBuffer, pCamera);
	RenderShield(hDCFrameBuffer, pCamera);
	for (int i = 0; i < BULLETS; i++) if (m_ppBullets[i]->m_bActive) m_ppBullets[i]->Render(hDCFrameBuffer, pCamera);
}

//void CAirplanePlayer::FireBullet(CGameObject* pLockedObject)
//{
///*
//	if (pLockedObject) 
//	{
//		LookAt(pLockedObject->GetPosition(), XMFLOAT3(0.0f, 1.0f, 0.0f));
//		OnUpdateTransform();
//	}
//*/
//
//	CBulletObject* pBulletObject = NULL;
//	for (int i = 0; i < BULLETS; i++)
//	{
//		if (!m_ppBullets[i]->m_bActive)
//		{
//			pBulletObject = m_ppBullets[i];
//			break;
//		}
//	}
//
//	if (pBulletObject)
//	{
//		XMFLOAT3 xmf3Position = GetPosition();
//		XMFLOAT3 xmf3Direction = GetUp();
//		XMFLOAT3 xmf3FirePosition = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Direction, 6.0f, false));
//
//		pBulletObject->m_xmf4x4World = m_xmf4x4World;
//
//		pBulletObject->SetFirePosition(xmf3FirePosition);
//		pBulletObject->SetMovingDirection(xmf3Direction);
//		pBulletObject->SetColor(RGB(255, 0, 0));
//		pBulletObject->SetActive(true);
//
//		if (pLockedObject)
//		{
//			pBulletObject->m_pLockedObject = pLockedObject;
//			pBulletObject->SetColor(RGB(0, 0, 255));
//		}
//	}
//}
void CTankPlayer::FireBullet(CGameObject* pLockedObject)
{
	CBulletObject* pBulletObject = NULL;
	for (int i = 0; i < BULLETS; i++)
	{
		if (!m_ppBullets[i]->m_bActive)
		{
			pBulletObject = m_ppBullets[i];
			break;
		}
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



		CMissileMesh* pBulletMesh = new CMissileMesh(2.0f, 2.0f, 4.0f);
		pBulletObject->SetMesh(pBulletMesh);

		if (pLockedObject)
		{
			pBulletObject->m_pLockedObject = pLockedObject;
			pBulletObject->SetColor(RGB(0, 0, 255));
		}
	}
}

void CTankPlayer::ActivateShield(float fDuration)  
{  
   m_bShieldActive = true;  
   m_fShieldDuration = fDuration;  
   m_fShieldElapsedTime = 0.0f;  
}  

void CTankPlayer::UpdateShield(float fElapsedTime)  
{  
   if (m_bShieldActive)  
   {  
       m_fShieldElapsedTime += fElapsedTime;  
       if (m_fShieldElapsedTime >= m_fShieldDuration)  
       {  
           m_bShieldActive = false;  
       }  
   }  
}  

void CTankPlayer::RenderShield(HDC hDCFrameBuffer, CCamera* pCamera)  
{  

     if (m_bShieldActive)  
     {  
         // 쉴드의 위치를 캐릭터의 현재 위치로 설정
         XMFLOAT3 shieldPosition = GetPosition();  

         // 쉴드 메쉬 생성 및 위치 설정
         CCubeMesh* shieldMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);  
         XMFLOAT4X4 shieldWorldMatrix = Matrix4x4::Identity();  
         shieldWorldMatrix._41 = shieldPosition.x;  
         shieldWorldMatrix._42 = shieldPosition.y;  
         shieldWorldMatrix._43 = shieldPosition.z;  

         // 쉴드 렌더링
         shieldMesh->Render(hDCFrameBuffer);  

         // 메모리 해제
         delete shieldMesh;  
     }  
}  

void CTankPlayer::Animate(float fElapsedTime)  
{  
   CPlayer::Animate(fElapsedTime);  

   UpdateShield(fElapsedTime);  

   for (int i = 0; i < BULLETS; i++)  
   {  
       if (m_ppBullets[i]->m_bActive) m_ppBullets[i]->Animate(fElapsedTime);  
   }  
}


/////////////////////////////////////////////////////////////////////////////////////////////
//    롤러코스터 카트 플레이어
/////////////////////////////////////////////////////////////////////////////////////////////

CCartPlayer::CCartPlayer()
{
}

CCartPlayer::~CCartPlayer()
{
}

void CCartPlayer::Animate(float fElapsedTime)
{
	CPlayer::Animate(fElapsedTime);

}

void CCartPlayer::OnUpdateTransform()
{
	CPlayer::OnUpdateTransform();
	//z축 방향을 가르키도록 바꾸어줌
	m_xmf4x4World = Matrix4x4::Multiply(XMMatrixRotationRollPitchYaw(XMConvertToRadians(0.0f), 0.0f, 0.0f), m_xmf4x4World);
	//90도를 라디안값으로 바꿔줘야 함
}

void CCartPlayer::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CPlayer::Render(hDCFrameBuffer, pCamera);


}
void CCartPlayer::Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity)
{
	if (bUpdateVelocity)
	{
		m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Shift);
	}
	else
	{
		m_xmf3Position = Vector3::Add(xmf3Shift, m_xmf3Position);
		m_pCamera->Move(xmf3Shift);
	}
}
void CCartPlayer::Move(float x, float y, float z)
{
	Move(XMFLOAT3(x, y, z), true);
}