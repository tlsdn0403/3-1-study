#pragma once
#include<memory>
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CVertex
{
public:
	CVertex() { m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	CVertex(float x, float y, float z) { m_xmf3Position = XMFLOAT3(x, y, z); }
	~CVertex() { }

	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
};

class CDiffusedVertex : public CVertex
{
protected:
	//������ �����̴�.
	XMFLOAT4 m_xmf4Diffuse;
public:
	CDiffusedVertex() {
		m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); m_xmf4Diffuse =
			XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	CDiffusedVertex(float x, float y, float z, XMFLOAT4 xmf4Diffuse) {
		m_xmf3Position =
			XMFLOAT3(x, y, z); m_xmf4Diffuse = xmf4Diffuse;
	}
	CDiffusedVertex(XMFLOAT3 xmf3Position, XMFLOAT4 xmf4Diffuse) {
		m_xmf3Position =
			xmf3Position; m_xmf4Diffuse = xmf4Diffuse;
	}
	~CDiffusedVertex() {}
};

class CPolygon
{
public:
	CPolygon() { }
	CPolygon(int nVertices);
	~CPolygon();
	int							m_nVertices = 0;
	CVertex						*m_pVertices = NULL;
	void SetVertex(int nIndex, CVertex& vertex);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMesh
{
public:
	CMesh() { }
	CMesh(int nPolygons);
	CMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual ~CMesh();

private:
	//�ν��Ͻ�(Instancing)�� ���Ͽ� �޽��� ���� ��ü�鿡 ������ �� �ִ�. 
	//���� ������(Reference Count)�� �޽��� �����Ǵ� ���� ��ü�� ������ ��Ÿ����
	int							m_nReferences = 1;

public:
	//�޽��� ���� ��ü�� ������ ������ �������� 1�� ������Ų��. 
	void AddRef() { m_nReferences++; }
	//�޽��� �����ϴ� ���� ��ü�� �Ҹ�� ������ �������� 1�� ���ҽ�Ų��. 
	//�������� 0�̵Ǹ� �޽��� �Ҹ��Ų��.
	void Release() { m_nReferences--; if (m_nReferences <= 0) delete this; }

	void ReleaseUploadBuffers();

protected:
	//�޽��� �����ϴ� �ٰ���(��)���� ����Ʈ�̴�. 
	int							m_nPolygons = 0;
	CPolygon					**m_ppPolygons = NULL;

	ID3D12Resource* m_pd3dVertexBuffer = NULL;
	ID3D12Resource* m_pd3dVertexUploadBuffer = NULL;
	D3D12_VERTEX_BUFFER_VIEW m_d3dVertexBufferView;
	D3D12_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT m_nSlot = 0;
	UINT m_nVertices = 0;
	UINT m_nStride = 0;
	UINT m_nOffset = 0;

public:
	//��� �ٿ�� �ڽ��� �⺻������ Mesh�� ������ �ִ�. �޽��� ������ �ִ� �ٿ�� �ڽ��� �� ��ǥ���̴�.
	BoundingOrientedBox			m_xmOOBB = BoundingOrientedBox(); //�⺻ ������ ȣ���Ͽ� �ʱ�ȭ, OOBB�ٿ�� �ڽ�

public:
	void SetPolygon(int nIndex, CPolygon *pPolygon);

	//�޽��� �������Ѵ�. 
	virtual void Render(HDC hDCFrameBuffer);

	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList);

	BOOL RayIntersectionByTriangle(XMVECTOR& xmRayOrigin, XMVECTOR& xmRayDirection, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* pfNearHitDistance);
	int CheckRayIntersection(XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection, float* pfNearHitDistance);
};

class CTriangleMesh : public CMesh
{
public:
	CTriangleMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual ~CTriangleMesh() {}
};



class CCubeMesh : public CMesh
{
public:
	CCubeMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f);
	virtual ~CCubeMesh() { }
};
class CMissileMesh : public CMesh
{
public:
	CMissileMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f);
	virtual ~CMissileMesh() {}
};
class CWallMesh : public CMesh
{
public:
	CWallMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f, int nSubRects = 20);
	virtual ~CWallMesh() { }
};
//-------------------------------------------------------------------------------------
//�ٴ�
//-------------------------------------------------------------------------------------
class CFloorMesh : public CMesh {
public:
	CFloorMesh(float fWidth = 4.0f,  float fDepth = 4.0f, int nSubRects = 20);
	virtual ~CFloorMesh() {}
};
class CAirplaneMesh : public CMesh
{
public:
	CAirplaneMesh(float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f);
	virtual ~CAirplaneMesh() { }
};

class CAxisMesh : public CMesh
{
public:
	CAxisMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f);
	virtual ~CAxisMesh() { }

	virtual void Render(HDC hDCFrameBuffer);
};
class CTankMesh : public CMesh
{
public:
	CTankMesh(float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f);
	virtual ~CTankMesh() {}
};
class CCartMesh : public CMesh
{
public:
	CCartMesh(float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f);
	virtual ~CCartMesh() {}
};
class CRollerCoasterMesh_Up : public CMesh {
public:
	CRollerCoasterMesh_Up(float fWidth, float fHeight, float fDepth);
	virtual ~CRollerCoasterMesh_Up() {}

};
class CRollerCoasterMesh_Right : public CMesh {
public:
	CRollerCoasterMesh_Right(float fWidth, float fHeight, float fDepth);
	virtual ~CRollerCoasterMesh_Right() {}

};