#include "stdafx.h"
#include "Mesh.h"

//������ ǥ���ϱ� ���� Ŭ������ ����.
 class Vertex { 
 protected: 
	 //������ ��ġ �����̴�(��� ������ �ּ��� ��ġ ���͸� ������ �Ѵ�).
	 XMFLOAT3 m_xmf3Position;

public:
	Vertex() { m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f); }
	Vertex(XMFLOAT3 xmf3Position) { m_xmf3Position = xmf3Position; }
	~Vertex() { } 
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
	~DiffusedVertex() { }
};

Mesh::Mesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) {

}

Mesh::~Mesh() {
	// ���ؽ� ���� & ���ε� ����
	if (m_pd3dVertexBuffer) 		m_pd3dVertexBuffer->Release();
	if (m_pd3dVertexUploadBuffer) 	m_pd3dVertexUploadBuffer->Release();
	
	// �ε��� ���� & ���ε� ����
	if (m_pd3dIndexBuffer)			m_pd3dIndexBuffer->Release();
	if (m_pd3dIndexUploadBuffer)	m_pd3dIndexUploadBuffer->Release();
}

void Mesh::ReleaseUploadBuffers() {
	// ���� ���۸� ���� ���ε� ���۸� �Ҹ��Ų��.
	if (m_pd3dVertexUploadBuffer) m_pd3dVertexUploadBuffer->Release();
	m_pd3dVertexUploadBuffer = NULL;

	// �ε��� ���۸� ���� ���ε� ���۸� �Ҹ��Ų��.
	if (m_pd3dIndexUploadBuffer) m_pd3dIndexUploadBuffer->Release();
	m_pd3dIndexUploadBuffer = NULL;
};

void Mesh::Render(ID3D12GraphicsCommandList *pd3dCommandList) {
	//�޽��� ������Ƽ�� ������ �����Ѵ�.
	pd3dCommandList->IASetPrimitiveTopology(m_d3dPrimitiveTopology);

	//�޽��� ���� ���� �並 �����Ѵ�.
	// ���������� ���� �Է� ����(����̽�), ���� ������ ����, �������� �� �ּ�
	pd3dCommandList->IASetVertexBuffers(m_nSlot, 1, &m_d3dVertexBufferView);
	
	//�ε��� ���۰� ������ �ε��� ���۸� ����������(IA: �Է� ������)�� �����ϰ� �ε����� ����Ͽ� ������
	if (m_pd3dIndexBuffer) {
		// ���������ο� �ϳ��� �ε��� ���� ���� ����
		// �ε��� ���� �ּ�
		pd3dCommandList->IASetIndexBuffer(&m_d3dIndexBufferView);

		// �ε��� ����, ��ü ��, ���� �ε��� ��ġ, �� ���� �ε����� ������ ��, ��ü �ε����� ������ ��
		pd3dCommandList->DrawIndexedInstanced(m_nIndices, 1, 0, 0, 0);
	} 

	//�޽��� ���� ���� �並 ������ (����������(�Է� ������)�� �۵��ϰ� �Ѵ�).
	// ���� ����, ��ü ��, ���� ���� ��ġ, ��ü �ε����� ������ ��
	else	pd3dCommandList->DrawInstanced(m_nVertices, 1, m_nOffset, 0); 
}

TriangleMesh::TriangleMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) : Mesh(pd3dDevice, pd3dCommandList) {
	// �ﰢ�� �޽��� �����Ѵ�.
	// �޽��� ������ ����
	m_nVertices = 3;
	// �޽��� ����, ��ġ�� ���� ������ ǥ���ϴ� class�� ũ�� - ���� ���� ���� �ϳ��� ũ��
	m_nStride = sizeof(DiffusedVertex);
	// Primitive Topology
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	//����(�ﰢ���� ������)�� ������ �ð���� ������� ������, ���, �Ķ������� �����Ѵ�.
	//RGBA(Red, Green, Blue, Alpha) 4���� �Ķ���͸� ����Ͽ� ������ ǥ���Ѵ�.
	//�� �Ķ���ʹ� 0.0~1.0 ������ �Ǽ����� ������.

	// ��, ��ġ ������ ���� ���� 3�� ����
	DiffusedVertex pVertices[3];
	pVertices[0] = DiffusedVertex(XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	pVertices[1] = DiffusedVertex(XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	pVertices[2] = DiffusedVertex(XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::Blue));

	// �ﰢ�� �޽��� ���ҽ�(���� ����)�� �����Ѵ�.
	// ���ҽ��� ������ ���� ���ÿ� ����
	// ����̽�, Ŀ�ǵ� ����Ʈ, ���������� �ּ�, ���� ���� ��ü�� ũ��, ���� ����, ���ҽ� ������ ����, ���ε� ������ �ּ�
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	// ���� ���� �並 �����Ѵ�.
	// ���� ���� �ּ�
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	// ���� ���� ��ü�� ũ��
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
	// ���� ���� �� ������ ũ��, �ϳ��� ���� ũ��
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
}

CubeMeshDiffused::CubeMeshDiffused(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList,
	float fWidth, float fHeight, float fDepth){

	// ��ü�� �ʿ��� ���� �� 8�� (������ü)
	m_nVertices = 8;
	m_nStride = sizeof(DiffusedVertex);
	
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
	//fWidth: ������ü ����(x-��) ����, fHeight: ������ü ����(y-��) ����, fDepth: ������ü ����(z-��) ���� 
	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f;
	
	// [1] ���� ����
	//���� ���۴� ������ü�� ������ 8���� ���� ���� �����͸� ������.
	DiffusedVertex pVertices[8];
	pVertices[0] = DiffusedVertex(XMFLOAT3(-fx, +fy, -fz), RANDOM_COLOR);
	pVertices[1] = DiffusedVertex(XMFLOAT3(+fx, +fy, -fz), RANDOM_COLOR);
	pVertices[2] = DiffusedVertex(XMFLOAT3(+fx, +fy, +fz), RANDOM_COLOR);
	pVertices[3] = DiffusedVertex(XMFLOAT3(-fx, +fy, +fz), RANDOM_COLOR);
	pVertices[4] = DiffusedVertex(XMFLOAT3(-fx, -fy, -fz), RANDOM_COLOR);
	pVertices[5] = DiffusedVertex(XMFLOAT3(+fx, -fy, -fz), RANDOM_COLOR);
	pVertices[6] = DiffusedVertex(XMFLOAT3(+fx, -fy, +fz), RANDOM_COLOR);
	pVertices[7] = DiffusedVertex(XMFLOAT3(-fx, -fy, +fz), RANDOM_COLOR);

	// �ﰢ�� �޽��� ���ҽ�(���� ����)�� �����Ѵ�.
	// ���ҽ��� ������ ���� ���ÿ� ����
	// ����̽�, Ŀ�ǵ� ����Ʈ, ���������� �ּ�, ���� ���� ��ü�� ũ��, ���� ����(�⺻), ���ҽ� ������ ����(�������), ���ε� ������ �ּ�
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	
	//���� ���� �並 �����Ѵ�.
	// ���� ���� �ּ�
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	// ���� ���� �� ������ ũ��, �ϳ��� ���� ũ��
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	// ���� ���� ��ü�� ũ��
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;


	// [2] �ε��� ����
	/*�ε��� ���۴� ������ü�� 6���� ��(�簢��)�� ���� ���� ������ ���´�.
	�ﰢ�� ����Ʈ�� ������ü�� ǥ���� ���� �Ƿ� �� ���� 2���� �ﰢ���� ������ �� �ﰢ���� 3���� ������ �ʿ��ϴ�.
	��, �ε��� ���۴� ��ü 36(=6*2*3)���� �� ������ ������ �Ѵ�.*/
	
	// 8���� �������� 36���� �ﰢ�� ������ ���ϱ�
	// �ε��� ����
	m_nIndices = 36;
	UINT pnIndices[36];

	//�� �ո�(Front) �簢���� ���� �ﰢ��
	pnIndices[0] = 3; pnIndices[1] = 1; pnIndices[2] = 0;
	//�� �ո�(Front) �簢���� �Ʒ��� �ﰢ��
	pnIndices[3] = 2; pnIndices[4] = 1; pnIndices[5] = 3;
	//�� ����(Top) �簢���� ���� �ﰢ��
	pnIndices[6] = 0; pnIndices[7] = 5; pnIndices[8] = 4;
	//�� ����(Top) �簢���� �Ʒ��� �ﰢ��
	pnIndices[9] = 1; pnIndices[10] = 5; pnIndices[11] = 0;
	//�� �޸�(Back) �簢���� ���� �ﰢ��
	pnIndices[12] = 3; pnIndices[13] = 4; pnIndices[14] = 7;
	//�� �޸�(Back) �簢���� �Ʒ��� �ﰢ��
	pnIndices[15] = 0; pnIndices[16] = 4; pnIndices[17] = 3;
	//�� �Ʒ���(Bottom) �簢���� ���� �ﰢ��   
	pnIndices[18] = 1; pnIndices[19] = 6; pnIndices[20] = 5;
	//�� �Ʒ���(Bottom) �簢���� �Ʒ��� �ﰢ��   
	pnIndices[21] = 2; pnIndices[22] = 6; pnIndices[23] = 1;
	//�� ����(Left) �簢���� ���� �ﰢ��   
	pnIndices[24] = 2; pnIndices[25] = 7; pnIndices[26] = 6;
	//�� ����(Left) �簢���� �Ʒ��� �ﰢ�� 
	pnIndices[27] = 3; pnIndices[28] = 7; pnIndices[29] = 2;
	//�� ����(Right) �簢���� ���� �ﰢ��   
	pnIndices[30] = 6; pnIndices[31] = 4; pnIndices[32] = 5;
	//�� ����(Right) �簢���� �Ʒ��� �ﰢ��   
	pnIndices[33] = 7; pnIndices[34] = 4; pnIndices[35] = 6;

	//�ε��� ���۸� ����
	// ����̽�, Ŀ�ǵ� ����Ʈ, ���������� �ּ�, ���� ���� ��ü�� ũ��, ���� ����(�⺻), ���ҽ� ������ ����(�ε��� ����), ���ε� ������ �ּ�
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pnIndices, sizeof(UINT) * m_nIndices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);
	
	//�ε��� ���� �並 ����
	// �ε��� ���� �ּ�
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	// �ε��� ���� ����
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	// �ε��� ���� ��ü ũ�� : UINT * �ε����� ����
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices; 
}

CubeMeshDiffused::~CubeMeshDiffused(){

}

AirplaneMeshDiffused::AirplaneMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList,
	float fWidth, float fHeight, float fDepth, XMFLOAT4 xmf4Color) : Mesh(pd3dDevice, pd3dCommandList) {

	
	m_nVertices = 24 * 3; m_nStride = sizeof(DiffusedVertex);
	m_nOffset = 0;
	m_nSlot = 0;
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	float fx = fWidth * 0.5f, fy = fHeight * 0.5f, fz = fDepth * 0.5f;

	//���� �׸��� ���� ����� �޽��� ǥ���ϱ� ���� ���� �������̴�.
	DiffusedVertex pVertices[24 * 3];
	float x1 = fx * 0.2f, y1 = fy * 0.2f, x2 = fx * 0.1f, y3 = fy * 0.3f, y2 = ((y1 - (fy - y3)) / x1) * x2 + (fy - y3);
	int i = 0;

	XMFLOAT4 randomcol = RANDOM_COLOR;

	//����� �޽��� ���� ��
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color,randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	
	//����� �޽��� �Ʒ��� ��
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	
	//����� �޽��� ������ ��
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	
	//����� �޽��� ����/������ ��
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	
	//����� �޽��� ���� ��
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	
	//����� �޽��� ����/���� ��
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4Color, randomcol)); randomcol = RANDOM_COLOR;
	pVertices[i++] = DiffusedVertex(XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4Color, randomcol));
	
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
}

AirplaneMeshDiffused::~AirplaneMeshDiffused() {
}
