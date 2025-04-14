#pragma once

#include "Mesh.h"
//depth를 쓰고 있지않아서 다렉꺼 안쓰고 그냥 정의를 했음
class CViewport  //left, top , width , height 값 저장 
{
public:
	CViewport() { }
	virtual ~CViewport() { }

	int							m_nLeft = 0;
	int							m_nTop = 0;
	int							m_nWidth = 0;
	int							m_nHeight = 0;

	void SetViewport(int nLeft, int nTop, int nWidth, int nHeight);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CPlayer;

class CCamera
{
public:
	CCamera();
	virtual ~CCamera();

private:
	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); //월드좌표계에서의 카메라의 위치
	XMFLOAT3					m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3					m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	float						m_fFOVAngle = 90.0f;
	float						m_fProjectRectDistance = 1.0f;

	float						m_fAspectRatio = float(FRAMEBUFFER_WIDTH) / float(FRAMEBUFFER_HEIGHT);

	BoundingFrustum				m_xmFrustumView = BoundingFrustum();	//카메라 좌표계의 바운딩 프러스텀

	BoundingFrustum				m_xmFrustumWorld = BoundingFrustum(); //월드 좌표계의 바운딩 프러스텀

	XMFLOAT4X4					m_xmf4x4InverseView = Matrix4x4::Identity();

public:
	XMFLOAT4X4					m_xmf4x4View = Matrix4x4::Identity();
	XMFLOAT4X4					m_xmf4x4PerspectiveProject = Matrix4x4::Identity();
	XMFLOAT4X4					m_xmf4x4ViewPerspectiveProject = Matrix4x4::Identity();

	XMFLOAT4X4					m_xmf4x4OrthographicProject = Matrix4x4::Identity();
	XMFLOAT4X4					m_xmf4x4ViewOrthographicProject = Matrix4x4::Identity();

	CViewport					m_Viewport; //left, top , width , height 값 저장 

public:
	void SetFOVAngle(float fFOVAngle);
	//카메라의 위치(Position)와 방향(Right, Up, Look) 벡터를 기반으로 뷰 행렬 생성
	void GenerateViewMatrix();

	//원근 투영 행렬(Perspective Projection Matrix)을 생성
	void GeneratePerspectiveProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fFOVAngle);

	//직교 투영 행렬 생성. 모든 객체가 크기 변화 없이 그려짐.
	void GenerateOrthographicProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fWidth, float hHeight);
	//화면에서 카메라가 렌더링할 뷰포트 영역의 위치와 크기를 설정
	void SetViewport(int xTopLeft, int yTopLeft, int nWidth, int nHeight);

	//카메라가 어느 방향을 바라보게 할지 설정
	void SetLookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);
	//카메라 위치는 유지한 채, 바라보는 위치와 업 벡터만 변경
	void SetLookAt(XMFLOAT3& vPosition, XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);

	void Move(XMFLOAT3& xmf3Shift);
	void Move(float x, float y, float z);
	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
	void Update(CPlayer* pPlayer, XMFLOAT3& xmf3LookAt, float fTimeElapsed = 0.016f);


	bool IsInFrustum(BoundingOrientedBox& xmBoundingBox);// 안에 있으면 그리고 안에 없으면 안그리고
};
