#pragma once

class Mesh {
public:  
	Mesh() {}
	Mesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual ~Mesh();

private: 
	int m_nReferences = 0;

public: 
	void AddRef() { m_nReferences++; }
	void Release() {
		if (--m_nReferences <= 0)
			delete this;
	}
	void ReleaseUploadBuffers();

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

class TriangleMesh : public Mesh {
public:    
	TriangleMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList); 
	virtual ~TriangleMesh() { } 
};

class CubeMeshDiffused : public Mesh {
public: 
	//������ü�� ����, ����, ������ ���̸� �����Ͽ� ������ü �޽��� �����Ѵ�.
	CubeMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList,
		float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CubeMeshDiffused();
};

class AirplaneMeshDiffused : public Mesh {
public:
	AirplaneMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList,
		float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f,
		XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f));
	virtual ~AirplaneMeshDiffused();
};
