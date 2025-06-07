#pragma once
//������ ǥ���ϱ� ���� Ŭ������ ����.
class Vertex {
public:
	//������ ��ġ �����̴�(��� ������ �ּ��� ��ġ ���͸� ������ �Ѵ�).
	XMFLOAT3 m_xmf3Position;

public:
	Vertex() { m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	Vertex(XMFLOAT3 xmf3Position) { m_xmf3Position = xmf3Position; }
	~Vertex() {}
};

class DiffusedVertex : public Vertex {
protected:
	//������ �����̴�.
	XMFLOAT4 m_xmf4Diffuse;
public:
	DiffusedVertex() {
		m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	DiffusedVertex(float x, float y, float z, XMFLOAT4 xmf4Diffuse) {
		m_xmf3Position = XMFLOAT3(x, y, z);
		m_xmf4Diffuse = xmf4Diffuse;
	}

	DiffusedVertex(XMFLOAT3 xmf3Position, XMFLOAT4 xmf4Diffuse) {
		m_xmf3Position = xmf3Position;
		m_xmf4Diffuse = xmf4Diffuse;
	}
	~DiffusedVertex() {}
};

\

class CPolygon
{
public:
	CPolygon() {}
	CPolygon(int nVertices);
	~CPolygon();
	int							m_nVertices = 0;
	Vertex* m_pVertices = NULL;
	void SetVertex(int nIndex, Vertex& vertex);
};

class Mesh {
public:  
	Mesh() {}
	Mesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual ~Mesh();

	//��� �ٿ�� �ڽ��� �⺻������ Mesh�� ������ �ִ�. �޽��� ������ �ִ� �ٿ�� �ڽ��� �� ��ǥ���̴�.
	BoundingOrientedBox			m_xmOOBB = BoundingOrientedBox(); //�⺻ ������ ȣ���Ͽ� �ʱ�ȭ, OOBB�ٿ�� �ڽ�

	BOOL RayIntersectionByTriangle(XMVECTOR& xmRayOrigin, XMVECTOR& xmRayDirection, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* pfNearHitDistance);
	int CheckRayIntersection(XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection, float* pfNearHitDistance);
public:
	//�� ��ǥ���� OOBB �ٿ�� �ڽ��̴�.
	BoundingOrientedBox m_xmBoundingBox;
private: 
	int m_nReferences = 0;
protected:
	DiffusedVertex * m_pVertices = NULL;
	//�޽��� �ε����� �����Ѵ�(�ε��� ���۸� Map()�Ͽ� ���� �ʾƵ� �ǵ���).
		UINT * m_pnIndices = NULL;

public: 
	void AddRef() { m_nReferences++; }
	void Release() {
		if (--m_nReferences <= 0)
			delete this;
	}
	void ReleaseUploadBuffers();
protected:
	//�޽��� �����ϴ� �ٰ���(��)���� ����Ʈ�̴�. 
	int							m_nPolygons = 0;
	CPolygon** m_ppPolygons = NULL;

protected: 
	// ���ҽ� ����
	ID3D12Resource *m_pd3dVertexBuffer = NULL;
	// ���ε� ���ҽ� ����
	ID3D12Resource *m_pd3dVertexUploadBuffer = NULL;
	// �������� ��
	D3D12_VERTEX_BUFFER_VIEW m_d3dVertexBufferView;
	// Primitive Topology
	D3D12_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
	UINT m_nSlot = 0;
	UINT m_nVertices = 0;
	UINT m_nStride = 0;
	UINT m_nOffset = 0;

protected:
	// �ε��� ���� �������̽� ������
	ID3D12Resource *m_pd3dIndexBuffer = NULL;
	// �ε��� ���� ���ε� ���� �������̽� ������
	ID3D12Resource *m_pd3dIndexUploadBuffer = NULL;

	// �ε��� ���� ��
	D3D12_INDEX_BUFFER_VIEW m_d3dIndexBufferView;

	// �ε��� ���ۿ� ���ԵǴ� �ε����� �����̴�.
	UINT m_nIndices = 0;
	// �ε��� ���ۿ��� �޽��� �׸��� ���� ���Ǵ� ���� �ε����̴�.
	UINT m_nStartIndex = 0;
	// �ε��� ������ �ε����� ������ �ε����̴�. 
	int m_nBaseVertex = 0;

public:
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList);
};

class CSphereMeshDiffused : public Mesh
{
public:
	CSphereMeshDiffused(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
		* pd3dCommandList, float fRadius = 2.0f, int nSlices = 20, int nStacks = 20);
	virtual ~CSphereMeshDiffused();
};

class TriangleMesh : public Mesh {
public:    
	TriangleMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList); 
	virtual ~TriangleMesh() { } 
};

class CubeMeshDiffused : public Mesh {
public: 
	//������ü�� ����, ����, ������ ���̸� �����Ͽ� ������ü �޽��� �����Ѵ�.
	CubeMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList,
		float fWidth , float fHeight , float fDepth );
	virtual ~CubeMeshDiffused();
};
class CFloorMesh : public Mesh {
public:
	CFloorMesh (ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,float fWidth = 4.0f, float fDepth = 4.0f, int nSubRects = 20);
	virtual ~CFloorMesh() {}
};
class AirplaneMeshDiffused : public Mesh {
public:
	AirplaneMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList,
		float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f,
		XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f));
	virtual ~AirplaneMeshDiffused();
};
class CTankMesh : public Mesh
{
public:
	CTankMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f,
		XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f));
	virtual ~CTankMesh() {}
};


class CartMesh : public Mesh {
public:
    CartMesh (ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 20.0f,
		XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f));
};

class CRollerCoasterMesh_Up : public Mesh {
public:
	CRollerCoasterMesh_Up(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth, float fHeight, float fDepth);
};

