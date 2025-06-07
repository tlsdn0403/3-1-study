#pragma once
//정점을 표현하기 위한 클래스를 선언.
class Vertex {
public:
	//정점의 위치 벡터이다(모든 정점은 최소한 위치 벡터를 가져야 한다).
	XMFLOAT3 m_xmf3Position;

public:
	Vertex() { m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	Vertex(XMFLOAT3 xmf3Position) { m_xmf3Position = xmf3Position; }
	~Vertex() {}
};

class DiffusedVertex : public Vertex {
protected:
	//정점의 색상이다.
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

	//모든 바운딩 박스는 기본적으로 Mesh가 가지고 있다. 메쉬가 가지고 있는 바운딩 박스는 모델 좌표계이다.
	BoundingOrientedBox			m_xmOOBB = BoundingOrientedBox(); //기본 생성자 호출하여 초기화, OOBB바운딩 박스

	BOOL RayIntersectionByTriangle(XMVECTOR& xmRayOrigin, XMVECTOR& xmRayDirection, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* pfNearHitDistance);
	int CheckRayIntersection(XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection, float* pfNearHitDistance);
public:
	//모델 좌표계의 OOBB 바운딩 박스이다.
	BoundingOrientedBox m_xmBoundingBox;
private: 
	int m_nReferences = 0;
protected:
	DiffusedVertex * m_pVertices = NULL;
	//메쉬의 인덱스를 저장한다(인덱스 버퍼를 Map()하여 읽지 않아도 되도록).
		UINT * m_pnIndices = NULL;

public: 
	void AddRef() { m_nReferences++; }
	void Release() {
		if (--m_nReferences <= 0)
			delete this;
	}
	void ReleaseUploadBuffers();
protected:
	//메쉬를 구성하는 다각형(면)들의 리스트이다. 
	int							m_nPolygons = 0;
	CPolygon** m_ppPolygons = NULL;

protected: 
	// 리소스 버퍼
	ID3D12Resource *m_pd3dVertexBuffer = NULL;
	// 업로드 리소스 버퍼
	ID3D12Resource *m_pd3dVertexUploadBuffer = NULL;
	// 정점버퍼 뷰
	D3D12_VERTEX_BUFFER_VIEW m_d3dVertexBufferView;
	// Primitive Topology
	D3D12_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
	UINT m_nSlot = 0;
	UINT m_nVertices = 0;
	UINT m_nStride = 0;
	UINT m_nOffset = 0;

protected:
	// 인덱스 버퍼 인터페이스 포인터
	ID3D12Resource *m_pd3dIndexBuffer = NULL;
	// 인덱스 버퍼 업로드 버퍼 인터페이스 포인터
	ID3D12Resource *m_pd3dIndexUploadBuffer = NULL;

	// 인덱스 버퍼 뷰
	D3D12_INDEX_BUFFER_VIEW m_d3dIndexBufferView;

	// 인덱스 버퍼에 포함되는 인덱스의 개수이다.
	UINT m_nIndices = 0;
	// 인덱스 버퍼에서 메쉬를 그리기 위해 사용되는 시작 인덱스이다.
	UINT m_nStartIndex = 0;
	// 인덱스 버퍼의 인덱스에 더해질 인덱스이다. 
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
	//직육면체의 가로, 세로, 깊이의 길이를 지정하여 직육면체 메쉬를 생성한다.
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

