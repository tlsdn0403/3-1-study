#pragma once
#define ASPECT_RATIO (float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT))

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


struct VS_CB_CAMERA_INFO
{
	XMFLOAT4X4 m_xmf4x4View;
	XMFLOAT4X4 m_xmf4x4Projection;
};

class CCamera
{
protected:
	//ī�޶� ��ȯ ���
	XMFLOAT4X4 m_xmf4x4View;
	//���� ��ȯ ���
	XMFLOAT4X4 m_xmf4x4Projection;
	//����Ʈ�� ���� �簢��
	D3D12_VIEWPORT m_d3dViewport;
	D3D12_RECT m_d3dScissorRect;
public:
	CCamera();
	virtual ~CCamera();
	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
		* pd3dCommandList);
	virtual void ReleaseShaderVariables();
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);
	void GenerateViewMatrix(XMFLOAT3 xmf3Position, XMFLOAT3 xmf3LookAt, XMFLOAT3 xmf3Up);
	void GenerateProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float
		fAspectRatio, float fFOVAngle);
	void SetViewport(int xTopLeft, int yTopLeft, int nWidth, int nHeight, float fMinZ =
		0.0f, float fMaxZ = 1.0f);
	void SetScissorRect(LONG xLeft, LONG yTop, LONG xRight, LONG yBottom);
	virtual void SetViewportsAndScissorRects(ID3D12GraphicsCommandList* pd3dCommandList);
};


class CCamera_1
{
public:
	CCamera_1();
	virtual ~CCamera_1();

private:
	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); //������ǥ�迡���� ī�޶��� ��ġ
	XMFLOAT3					m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3					m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	float						m_fFOVAngle = 90.0f;
	float						m_fProjectRectDistance = 1.0f;

	float						m_fAspectRatio = float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT);

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
	void OrbitAroundPlayer(CPlayer* pPlayer, float fPitch, float fYaw, float fRoll);
	void Update(CPlayer* pPlayer, XMFLOAT3& xmf3LookAt, float fTimeElapsed = 0.016f);


	bool IsInFrustum(BoundingOrientedBox& xmBoundingBox);// �ȿ� ������ �׸��� �ȿ� ������ �ȱ׸���
};
