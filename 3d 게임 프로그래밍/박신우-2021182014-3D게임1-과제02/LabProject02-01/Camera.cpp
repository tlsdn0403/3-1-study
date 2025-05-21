#include "stdafx.h"
#include "Camera.h"
#include "Mesh.h"
#include "Player.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CViewport::SetViewport(int nLeft, int nTop, int nWidth, int nHeight)  //입력한 매개변수 값으로 뷰포트 값 저장
{
	m_nLeft = nLeft; 
	m_nTop = nTop; 
	m_nWidth = nWidth; 
	m_nHeight = nHeight; 
}



CCamera::CCamera()
{
	m_xmf4x4View = Matrix4x4::Identity();
	m_xmf4x4Projection = Matrix4x4::Identity();
	m_d3dViewport = { 0, 0, FRAME_BUFFER_WIDTH , FRAME_BUFFER_HEIGHT, 0.0f, 1.0f };
	m_d3dScissorRect = { 0, 0, FRAME_BUFFER_WIDTH , FRAME_BUFFER_HEIGHT };
}
CCamera::~CCamera()
{
	// 필요하다면 자원 해제 코드 작성
}
void CCamera::SetViewport(int xTopLeft, int yTopLeft, int nWidth, int nHeight, float
	fMinZ, float fMaxZ)
{
	m_d3dViewport.TopLeftX = float(xTopLeft);
	m_d3dViewport.TopLeftY = float(yTopLeft);
	m_d3dViewport.Width = float(nWidth);
	m_d3dViewport.Height = float(nHeight);
	m_d3dViewport.MinDepth = fMinZ;
	m_d3dViewport.MaxDepth = fMaxZ;
}

void CCamera::SetScissorRect(LONG xLeft, LONG yTop, LONG xRight, LONG yBottom)
{
	m_d3dScissorRect.left = xLeft;
	m_d3dScissorRect.top = yTop;
	m_d3dScissorRect.right = xRight;
	m_d3dScissorRect.bottom = yBottom;
}
void CCamera::GenerateProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fAspectRatio, float fFOVAngle)
{
	m_xmf4x4Projection = Matrix4x4::PerspectiveFovLH(XMConvertToRadians(fFOVAngle),
		fAspectRatio, fNearPlaneDistance, fFarPlaneDistance);
}
void CCamera::GenerateViewMatrix(XMFLOAT3 xmf3Position, XMFLOAT3 xmf3LookAt, XMFLOAT3 xmf3Up)
{

	m_xmf4x4View = Matrix4x4::LookAtLH(xmf3Position, xmf3LookAt, xmf3Up);
}
void CCamera::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{

}

void CCamera::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	XMFLOAT4X4 xmf4x4View;
	XMStoreFloat4x4(&xmf4x4View, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4View)));
	//루트 파라메터 인덱스 1의
	pd3dCommandList->SetGraphicsRoot32BitConstants(1, 16, &xmf4x4View, 0);
	XMFLOAT4X4 xmf4x4Projection;
	XMStoreFloat4x4(&xmf4x4Projection,
		XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4Projection)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(1, 16, &xmf4x4Projection, 16);
}

void CCamera::ReleaseShaderVariables()
{
}
void CCamera::SetViewportsAndScissorRects(ID3D12GraphicsCommandList* pd3dCommandList)
{
	pd3dCommandList->RSSetViewports(1, &m_d3dViewport);
	pd3dCommandList->RSSetScissorRects(1, &m_d3dScissorRect);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// 이전 카메라
/////////////////////////////////////////////////////////////////////////////////////////////////////
CCamera_1::CCamera_1()
{
}

CCamera_1::~CCamera_1()
{
}

void CCamera_1::GenerateViewMatrix() //카메라가 움직이거나 회전을 하면 항상 호출이 되는 함수
{
	m_xmf3Look = Vector3::Normalize(m_xmf3Look);
	m_xmf3Right = Vector3::Normalize(Vector3::CrossProduct(m_xmf3Up, m_xmf3Look));
	m_xmf3Up = Vector3::Normalize(Vector3::CrossProduct(m_xmf3Look, m_xmf3Right));

	//카메라 변환행렬
	m_xmf4x4View._11 = m_xmf3Right.x; m_xmf4x4View._12 = m_xmf3Up.x; m_xmf4x4View._13 = m_xmf3Look.x;
	m_xmf4x4View._21 = m_xmf3Right.y; m_xmf4x4View._22 = m_xmf3Up.y; m_xmf4x4View._23 = m_xmf3Look.y;
	m_xmf4x4View._31 = m_xmf3Right.z; m_xmf4x4View._32 = m_xmf3Up.z; m_xmf4x4View._33 = m_xmf3Look.z;
	m_xmf4x4View._41 = -Vector3::DotProduct(m_xmf3Position, m_xmf3Right);
	m_xmf4x4View._42 = -Vector3::DotProduct(m_xmf3Position, m_xmf3Up);
	m_xmf4x4View._43 = -Vector3::DotProduct(m_xmf3Position, m_xmf3Look);

	m_xmf4x4ViewPerspectiveProject = Matrix4x4::Multiply(m_xmf4x4View, m_xmf4x4PerspectiveProject);
	m_xmf4x4OrthographicProject = Matrix4x4::Multiply(m_xmf4x4View, m_xmf4x4OrthographicProject);

	//카메라 변환행렬의 역행렬  -> (카메라 좌표를 월드좌표로 바꾸기 위한 행렬)
	m_xmf4x4InverseView._11 = m_xmf3Right.x; m_xmf4x4InverseView._12 = m_xmf3Right.y; m_xmf4x4InverseView._13 = m_xmf3Right.z;
	m_xmf4x4InverseView._21 = m_xmf3Up.x; m_xmf4x4InverseView._22 = m_xmf3Up.y; m_xmf4x4InverseView._23 = m_xmf3Up.z;
	m_xmf4x4InverseView._31 = m_xmf3Look.x; m_xmf4x4InverseView._32 = m_xmf3Look.y; m_xmf4x4InverseView._33 = m_xmf3Look.z;
	m_xmf4x4InverseView._41 = m_xmf3Position.x; m_xmf4x4InverseView._42 = m_xmf3Position.y; m_xmf4x4InverseView._43 = m_xmf3Position.z;

	//카메라 행렬변환을 갱신을 할 때마다 
	m_xmFrustumView.Transform(m_xmFrustumWorld, XMLoadFloat4x4(&m_xmf4x4InverseView)); // m_xmFrustumWorld 를 월드좌표계로 바꾸어 줌
}

void CCamera_1::SetLookAt(XMFLOAT3& xmf3Position, XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up)
{
	m_xmf3Position = xmf3Position;
	m_xmf4x4View = Matrix4x4::LookAtLH(m_xmf3Position, xmf3LookAt, xmf3Up);
	m_xmf3Right = Vector3::Normalize(XMFLOAT3(m_xmf4x4View._11, m_xmf4x4View._21, m_xmf4x4View._31));
	m_xmf3Up = Vector3::Normalize(XMFLOAT3(m_xmf4x4View._12, m_xmf4x4View._22, m_xmf4x4View._32));
	m_xmf3Look = Vector3::Normalize(XMFLOAT3(m_xmf4x4View._13, m_xmf4x4View._23, m_xmf4x4View._33));
}

void CCamera_1::SetLookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up)
{
	XMFLOAT4X4 xmf4x4View = Matrix4x4::LookAtLH(m_xmf3Position, xmf3LookAt, xmf3Up);
	//m_xmf3Right = Vector3::Normalize(XMFLOAT3(xmf4x4View._11, xmf4x4View._21, xmf4x4View._31));
	//m_xmf3Up = Vector3::Normalize(XMFLOAT3(xmf4x4View._12, xmf4x4View._22, xmf4x4View._32));
	//m_xmf3Look = Vector3::Normalize(XMFLOAT3(xmf4x4View._13, xmf4x4View._23, xmf4x4View._33));
}

void CCamera_1::SetViewport(int nLeft, int nTop, int nWidth, int nHeight)
{
	m_Viewport.SetViewport(nLeft, nTop, nWidth, nHeight);
	m_fAspectRatio = float(m_Viewport.m_nWidth) / float(m_Viewport.m_nHeight);
}

void CCamera_1::SetFOVAngle(float fFOVAngle)
{
	m_fFOVAngle = fFOVAngle;
	m_fProjectRectDistance = float(1.0f / tan(DegreeToRadian(fFOVAngle * 0.5f)));
}

void CCamera_1::GeneratePerspectiveProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fFOVAngle)
{
	float fAspectRatio = (float(m_Viewport.m_nWidth) / float(m_Viewport.m_nHeight));
	XMMATRIX xmmtxProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(fFOVAngle), fAspectRatio, fNearPlaneDistance, fFarPlaneDistance); //투영변환 행렬 생성
	XMStoreFloat4x4(&m_xmf4x4PerspectiveProject, xmmtxProjection);

	BoundingFrustum::CreateFromMatrix(m_xmFrustumView, xmmtxProjection);//카메라 좌표계의 바운딩 프러스텀을 생성해서 가지고 있는다.
}

void CCamera_1::GenerateOrthographicProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fWidth, float hHeight)
{
	XMMATRIX xmmtxProjection = XMMatrixOrthographicLH(fWidth, hHeight, fNearPlaneDistance, fFarPlaneDistance);
	XMStoreFloat4x4(&m_xmf4x4OrthographicProject, xmmtxProjection);
}

bool CCamera_1::IsInFrustum(BoundingOrientedBox& xmBoundingBox)
{
	//월드좌표계의 프러스텀을 업데이트를 했다면 IsInFrustum을 호출하는 바운딩 박스는 월드좌표계의 바운딩 박스라고 하면 프러스텀안에 있으면 true를 리턴하고 그렇지 않으면 false
	//어떤 오브젝트의 월드 좌표계의 바운딩 박스가 이 프러스텀안에 있는지 없는지 판단.
	return(m_xmFrustumWorld.Intersects(xmBoundingBox));
}

void CCamera_1::Move(XMFLOAT3& xmf3Shift)
{
	m_xmf3Position = Vector3::Add(m_xmf3Position, xmf3Shift);
}

void CCamera_1::Move(float x, float y, float z)
{
	Move(XMFLOAT3(x, y, z));
}

void CCamera_1::Rotate(float fPitch, float fYaw, float fRoll)
{
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
}

//오프셋을 고려해서 카메라가 자전이 아닌 공전을 하도록 만듦
void CCamera_1::OrbitAroundPlayer(CPlayer* pPlayer, float fPitch, float fYaw, float fRoll)
{
	// 플레이어와 카메라의 상대적 오프셋 
	XMFLOAT3 xmf3Offset = pPlayer->m_xmf3CameraOffset;

	// 오프셋 벡터를 회전
	if (fPitch != 0.0f || fYaw != 0.0f || fRoll != 0.0f)
	{
		XMMATRIX mtxRotate = XMMatrixIdentity();
		if (fPitch != 0.0f)
		{
			mtxRotate *= XMMatrixRotationAxis(XMLoadFloat3(&pPlayer->m_xmf3Right), XMConvertToRadians(fPitch));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, mtxRotate);
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, mtxRotate);
		}
		if (fYaw != 0.0f)
		{
			mtxRotate *= XMMatrixRotationAxis(XMLoadFloat3(&pPlayer->m_xmf3Up), XMConvertToRadians(fYaw));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, mtxRotate);
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, mtxRotate);
		}
		if (fRoll != 0.0f)
		{
			mtxRotate *= XMMatrixRotationAxis(XMLoadFloat3(&pPlayer->m_xmf3Look), XMConvertToRadians(fRoll));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, mtxRotate);
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, mtxRotate);
		}

		xmf3Offset = Vector3::TransformCoord(xmf3Offset, mtxRotate);
	}


	// 카메라가 항상 플레이어를 바라보도록 방향을 갱신
	SetLookAt(pPlayer->m_xmf3Position, pPlayer->m_xmf3Up);
}
void CCamera_1::Update(CPlayer* pPlayer, XMFLOAT3& xmf3LookAt, float fTimeElapsed)
{
	XMFLOAT4X4 mtxRotate = Matrix4x4::Identity();
	mtxRotate._11 = pPlayer->m_xmf3Right.x; mtxRotate._21 = pPlayer->m_xmf3Up.x; mtxRotate._31 = pPlayer->m_xmf3Look.x;
	mtxRotate._12 = pPlayer->m_xmf3Right.y; mtxRotate._22 = pPlayer->m_xmf3Up.y; mtxRotate._32 = pPlayer->m_xmf3Look.y;
	mtxRotate._13 = pPlayer->m_xmf3Right.z; mtxRotate._23 = pPlayer->m_xmf3Up.z; mtxRotate._33 = pPlayer->m_xmf3Look.z;

	XMFLOAT3 xmf3Offset = Vector3::TransformCoord(pPlayer->m_xmf3CameraOffset, mtxRotate);
	XMFLOAT3 xmf3Position = Vector3::Add(pPlayer->m_xmf3Position, xmf3Offset);
	XMFLOAT3 xmf3Direction = Vector3::Subtract(xmf3Position, m_xmf3Position);
	float fLength = Vector3::Length(xmf3Direction);
	xmf3Direction = Vector3::Normalize(xmf3Direction);

	float fTimeLagScale = fTimeElapsed * (1.0f / 0.25f);
	float fDistance = fLength * fTimeLagScale;
	if (fDistance > fLength) fDistance = fLength;
	if (fLength < 0.01f) fDistance = fLength;
	if (fDistance > 0)
	{
		m_xmf3Position = Vector3::Add(m_xmf3Position, xmf3Direction, fDistance);
		SetLookAt(pPlayer->m_xmf3Position, pPlayer->m_xmf3Up);
	}
}
