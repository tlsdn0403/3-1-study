#pragma once

#include "Mesh.h"
//depth�� ���� �����ʾƼ� �ٷ��� �Ⱦ��� �׳� ���Ǹ� ����
class CViewport  //left, top , width , height �� ���� 
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
	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); //������ǥ�迡���� ī�޶��� ��ġ
	XMFLOAT3					m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3					m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	float						m_fFOVAngle = 90.0f;
	float						m_fProjectRectDistance = 1.0f;

	float						m_fAspectRatio = float(FRAMEBUFFER_WIDTH) / float(FRAMEBUFFER_HEIGHT);

	BoundingFrustum				m_xmFrustumView = BoundingFrustum();	//ī�޶� ��ǥ���� �ٿ�� ��������

	BoundingFrustum				m_xmFrustumWorld = BoundingFrustum(); //���� ��ǥ���� �ٿ�� ��������

	XMFLOAT4X4					m_xmf4x4InverseView = Matrix4x4::Identity();

public:
	XMFLOAT4X4					m_xmf4x4View = Matrix4x4::Identity();
	XMFLOAT4X4					m_xmf4x4PerspectiveProject = Matrix4x4::Identity();
	XMFLOAT4X4					m_xmf4x4ViewPerspectiveProject = Matrix4x4::Identity();

	XMFLOAT4X4					m_xmf4x4OrthographicProject = Matrix4x4::Identity();
	XMFLOAT4X4					m_xmf4x4ViewOrthographicProject = Matrix4x4::Identity();

	CViewport					m_Viewport; //left, top , width , height �� ���� 

public:
	void SetFOVAngle(float fFOVAngle);
	//ī�޶��� ��ġ(Position)�� ����(Right, Up, Look) ���͸� ������� �� ��� ����
	void GenerateViewMatrix();

	//���� ���� ���(Perspective Projection Matrix)�� ����
	void GeneratePerspectiveProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fFOVAngle);

	//���� ���� ��� ����. ��� ��ü�� ũ�� ��ȭ ���� �׷���.
	void GenerateOrthographicProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fWidth, float hHeight);
	//ȭ�鿡�� ī�޶� �������� ����Ʈ ������ ��ġ�� ũ�⸦ ����
	void SetViewport(int xTopLeft, int yTopLeft, int nWidth, int nHeight);

	//ī�޶� ��� ������ �ٶ󺸰� ���� ����
	void SetLookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);
	//ī�޶� ��ġ�� ������ ä, �ٶ󺸴� ��ġ�� �� ���͸� ����
	void SetLookAt(XMFLOAT3& vPosition, XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);

	void Move(XMFLOAT3& xmf3Shift);
	void Move(float x, float y, float z);
	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
	void Update(CPlayer* pPlayer, XMFLOAT3& xmf3LookAt, float fTimeElapsed = 0.016f);


	bool IsInFrustum(BoundingOrientedBox& xmBoundingBox);// �ȿ� ������ �׸��� �ȿ� ������ �ȱ׸���
};
