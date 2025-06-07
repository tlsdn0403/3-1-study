#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) {

}

Mesh::~Mesh() {
	// ���ؽ� ���� & ���ε� ����
	if (m_pd3dVertexBuffer) 		m_pd3dVertexBuffer->Release();
	if (m_pd3dVertexUploadBuffer) 	m_pd3dVertexUploadBuffer->Release();
	
	// �ε��� ���� & ���ε� ����
	if (m_pd3dIndexBuffer)			m_pd3dIndexBuffer->Release();
	if (m_pd3dIndexUploadBuffer)	m_pd3dIndexUploadBuffer->Release();

	//��ŷ�� ����
	if (m_pVertices) delete[] m_pVertices;
	if (m_pnIndices) delete[] m_pnIndices;
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
BOOL Mesh::RayIntersectionByTriangle(XMVECTOR& xmRayOrigin, XMVECTOR& xmRayDirection, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* pfNearHitDistance)
{
	float fHitDistance;
	BOOL bIntersected = TriangleTests::Intersects(xmRayOrigin, xmRayDirection, v0, v1, v2, fHitDistance);
	if (bIntersected && (fHitDistance < *pfNearHitDistance)) *pfNearHitDistance = fHitDistance;

	return(bIntersected);
}
//int Mesh::CheckRayIntersection(XMFLOAT3& xmf3RayOrigin, XMFLOAT3& xmf3RayDirection, float* pfNearHitDistance)
//{
//	//�ϳ��� �޽����� ������ ���� ���� �ﰢ���� ������ �� �ִ�. �����ϴ� �ﰢ���� �� ���� ����� �ﰢ���� ã�´�.
//	int nIntersections = 0;
//	BYTE* pbPositions = (BYTE*)m_pVertices;
//	int nOffset = (m_d3dPrimitiveTopology == D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST) ? 3 : 1;
//	/*�޽��� ������Ƽ��(�ﰢ��)���� �����̴�. �ﰢ�� ����Ʈ�� ��� (������ ���� / 3) �Ǵ� (�ε����� ���� / 3), �ﰢ
//   �� ��Ʈ���� ��� (������ ���� - 2) �Ǵ� (�ε����� ���� ? 2)�̴�.*/
//	int nPrimitives = (m_d3dPrimitiveTopology == D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST) ?
//		(m_nVertices / 3) : (m_nVertices - 2);
//	if (m_nIndices > 0) nPrimitives = (m_d3dPrimitiveTopology ==
//		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST) ? (m_nIndices / 3) : (m_nIndices - 2);
//	//������ �� ��ǥ��� ǥ���ȴ�.
//	XMVECTOR xmRayOrigin = XMLoadFloat3(&xmf3RayOrigin);
//	XMVECTOR xmRayDirection = XMLoadFloat3(&xmf3RayDirection);
//	//�� ��ǥ���� ������ �޽��� �ٿ�� �ڽ�(�� ��ǥ��)���� ������ �˻��Ѵ�.
//	bool bIntersected = m_xmBoundingBox.Intersects(xmRayOrigin, xmRayDirection,
//		*pfNearHitDistance);
//	//�� ��ǥ���� ������ �޽��� �ٿ�� �ڽ��� �����ϸ� �޽����� ������ �˻��Ѵ�.
//	if (bIntersected)
//	{
//		float fNearHitDistance = FLT_MAX;
//		/*�޽��� ��� ������Ƽ��(�ﰢ��)�鿡 ���Ͽ� ��ŷ �������� �浹�� �˻��Ѵ�. �浹�ϴ� ��� �ﰢ���� ã�� ������
//	   ������(�����δ� ī�޶� ��ǥ���� ����)�� ���� ����� �ﰢ���� ã�´�.*/
//		for (int i = 0; i < nPrimitives; i++)
//		{
//			XMVECTOR v0 = XMLoadFloat3((XMFLOAT3*)(pbPositions + ((m_pnIndices) ?
//				(m_pnIndices[(i * nOffset) + 0]) : ((i * nOffset) + 0)) * m_nStride));
//			XMVECTOR v1 = XMLoadFloat3((XMFLOAT3*)(pbPositions + ((m_pnIndices) ?
//				(m_pnIndices[(i * nOffset) + 1]) : ((i * nOffset) + 1)) * m_nStride));
//			XMVECTOR v2 = XMLoadFloat3((XMFLOAT3*)(pbPositions + ((m_pnIndices) ?
//				(m_pnIndices[(i * nOffset) + 2]) : ((i * nOffset) + 2)) * m_nStride));
//			float fHitDistance;
//			BOOL bIntersected = TriangleTests::Intersects(xmRayOrigin, xmRayDirection, v0,
//				v1, v2, fHitDistance);
//			if (bIntersected)
//			{
//				if (fHitDistance < fNearHitDistance)
//				{
//					*pfNearHitDistance = fNearHitDistance = fHitDistance;
//				}
//				nIntersections++;
//			}
//		}
//	}
//	return(nIntersections);
//}

int Mesh::CheckRayIntersection(XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection, float* pfNearHitDistance)
{
	int nIntersections = 0;
	//���� ��ǥ�Կ��� Intersects�� ���� ȣ���ϰ� 
	bool bIntersected = m_xmOOBB.Intersects(xmvPickRayOrigin, xmvPickRayDirection, *pfNearHitDistance); //����ǥ�Կ��� ���ͼ��� �˻�
	if (bIntersected)
	{
		for (int i = 0; i < m_nPolygons; i++)
		{
			switch (m_ppPolygons[i]->m_nVertices)
			{
			case 3:
			{
				XMVECTOR v0 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[0].m_xmf3Position));
				XMVECTOR v1 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[1].m_xmf3Position));
				XMVECTOR v2 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[2].m_xmf3Position));
				//�ﰢ���̸� �ﰢ�� �ϳ��� �����ٰ� ���� ����� �ﰢ���� �Ÿ��� �����´�
				BOOL bIntersected = RayIntersectionByTriangle(xmvPickRayOrigin, xmvPickRayDirection, v0, v1, v2, pfNearHitDistance);
				if (bIntersected) nIntersections++;
				break;
			}
			case 4:
			{
				//�簢���� ��� �ﰢ���� 2���ϱ� 2���� ���ش�.
				XMVECTOR v0 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[0].m_xmf3Position));
				XMVECTOR v1 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[1].m_xmf3Position));
				XMVECTOR v2 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[2].m_xmf3Position));
				BOOL bIntersected = RayIntersectionByTriangle(xmvPickRayOrigin, xmvPickRayDirection, v0, v1, v2, pfNearHitDistance);
				if (bIntersected) nIntersections++;
				v0 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[0].m_xmf3Position));
				v1 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[2].m_xmf3Position));
				v2 = XMLoadFloat3(&(m_ppPolygons[i]->m_pVertices[3].m_xmf3Position));
				bIntersected = RayIntersectionByTriangle(xmvPickRayOrigin, xmvPickRayDirection, v0, v1, v2, pfNearHitDistance);
				if (bIntersected) nIntersections++;
				break;
			}
			}
		}
	}
	return(nIntersections);
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
	//�߽� , ũ�� , 0,0,0,1�� ȸ���� ���� ���� ���ʹϾ��� �ǹ���
	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fx, fy, fz), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
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

CartMesh::CartMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
	float fWidth, float fHeight, float fDepth, XMFLOAT4 xmf4Color) : Mesh(pd3dDevice, pd3dCommandList)
{
	// �ٵ�(������ü) + ����(4�� ť��)�� ����
	const int nBodyVertices = 8;
	const int nBodyIndices = 36;
	const int nWheelVertices = 8 * 4;
	const int nWheelIndices = 36 * 4;

	const int nVertices = nBodyVertices + nWheelVertices;
	const int nIndices = nBodyIndices + nWheelIndices;

	std::vector<DiffusedVertex> vertices;
	std::vector<UINT> indices;

	// �ٵ�(������ü)
	float fx = fWidth * 0.5f, fy = fHeight * 0.5f, fz = fDepth * 0.5f;
	float bodyHeight = fy * 0.6f;
	float topY = bodyHeight;
	float bottomY = -bodyHeight;

	// �ٵ� ����
	XMFLOAT3 bodyVerts[8] = {
		XMFLOAT3(-fx, bottomY, -fz), // 0
		XMFLOAT3(+fx, bottomY, -fz), // 1
		XMFLOAT3(+fx, topY,   -fz), // 2
		XMFLOAT3(-fx, topY,   -fz), // 3
		XMFLOAT3(-fx, bottomY, +fz), // 4
		XMFLOAT3(+fx, bottomY, +fz), // 5
		XMFLOAT3(+fx, topY,   +fz), // 6
		XMFLOAT3(-fx, topY,   +fz)  // 7
	};
	for (int i = 0; i < 8; ++i)
		vertices.push_back(DiffusedVertex(bodyVerts[i], RANDOM_COLOR));

	// �ٵ� �ε��� (������ü)
	UINT bodyIdx[36] = {
		0,1,2, 0,2,3, // Front
		1,5,6, 1,6,2, // Right
		5,4,7, 5,7,6, // Back
		4,0,3, 4,3,7, // Left
		3,2,6, 3,6,7, // Top
		4,5,1, 4,1,0  // Bottom
	};
	for (int i = 0; i < 36; ++i)
		indices.push_back(bodyIdx[i]);

	// ����(4�� ť��, �� 8���� 36�ε���)
	float wheelRadius = fy * 0.2f;
	float wheelWidth = fWidth * 0.15f;
	float wheelY = -fy + wheelRadius;
	float wheelZ[2] = { -fz + fDepth / 4.0f, -fz + 3 * fDepth / 4.0f };
	float wheelX[2] = { -fx + wheelWidth / 2.0f, +fx - wheelWidth / 2.0f };

	for (int w = 0; w < 4; ++w) {
		float cx = (w < 2) ? wheelX[0] : wheelX[1];
		float cz = (w % 2 == 0) ? wheelZ[0] : wheelZ[1];
		// ���� ť���� 8����
		XMFLOAT3 wheelVerts[8] = {
			XMFLOAT3(cx - wheelWidth / 2, wheelY - wheelRadius, cz - wheelRadius),
			XMFLOAT3(cx + wheelWidth / 2, wheelY - wheelRadius, cz - wheelRadius),
			XMFLOAT3(cx + wheelWidth / 2, wheelY + wheelRadius, cz - wheelRadius),
			XMFLOAT3(cx - wheelWidth / 2, wheelY + wheelRadius, cz - wheelRadius),
			XMFLOAT3(cx - wheelWidth / 2, wheelY - wheelRadius, cz + wheelRadius),
			XMFLOAT3(cx + wheelWidth / 2, wheelY - wheelRadius, cz + wheelRadius),
			XMFLOAT3(cx + wheelWidth / 2, wheelY + wheelRadius, cz + wheelRadius),
			XMFLOAT3(cx - wheelWidth / 2, wheelY + wheelRadius, cz + wheelRadius)
		};
		int baseIdx = (int)vertices.size();
		for (int i = 0; i < 8; ++i)
			vertices.push_back(DiffusedVertex(wheelVerts[i], RANDOM_COLOR));
		// ���� �ε��� (������ü)
		UINT wheelIdx[36] = {
			0,1,2, 0,2,3, // Front
			1,5,6, 1,6,2, // Right
			5,4,7, 5,7,6, // Back
			4,0,3, 4,3,7, // Left
			3,2,6, 3,6,7, // Top
			4,5,1, 4,1,0  // Bottom
		};
		for (int i = 0; i < 36; ++i)
			indices.push_back(baseIdx + wheelIdx[i]);
	}

	m_nVertices = (UINT)vertices.size();
	m_nIndices = (UINT)indices.size();
	m_nStride = sizeof(DiffusedVertex);
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// ���� ���� ����
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	// �ε��� ���� ����
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;
}

// CubeMeshDiffusedó�� ����/�ε��� ���� ������� CRollerCoasterMesh_Up ���� (����)

CRollerCoasterMesh_Up::CRollerCoasterMesh_Up(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth, float fHeight, float fDepth) : Mesh(pd3dDevice, pd3dCommandList)
{
	// �β��� ������ ���� �� ���� �ڽ� ���·� ���� (����/�¿� �β� �߰�)
	const int nSegments = 12;
	const int nRails = 2; // ���� 2��
	const float railWidth = fDepth * 0.3f; // ���� �β�(�¿�)
	const float railHeight = fHeight * 0.02f; // ���� �β�(����)

	std::vector<DiffusedVertex> vertices;
	std::vector<UINT> indices;

	// ���� �߽ɼ� ��ǥ ���� (���� faceVerts�� �߽ɼ�)
	XMFLOAT3 centers[nSegments + 1] = {
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(+fWidth * 0.5f, fHeight, 0.0f),
		XMFLOAT3(+fWidth * 0.5f, fHeight, +fDepth * 0.5f),
		XMFLOAT3(+fWidth * 0.5f, fHeight, -fWidth * 0.5f),
		XMFLOAT3(0.0f, 0.0f, -fWidth * 0.5f),
		XMFLOAT3(-fWidth * 0.5f, 0.0f, -fWidth * 0.5f),
		XMFLOAT3(-fWidth, -fHeight * 0.5f, -fWidth),
		XMFLOAT3(-fWidth * 1.5f, -fHeight * 0.5f, -fWidth),
		XMFLOAT3(-fWidth * 2.0f, 0.0f, -fWidth * 0.5f),
		XMFLOAT3(-fWidth * 2.0f, 0.0f, 0.0f),
		XMFLOAT3(-fWidth * 1.5f, 0.0f, 0.0f),
		XMFLOAT3(-fWidth, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f)
	};

	// ���� 2��(��/��) ���� �ڽ� ���·� ����
	for (int rail = 0; rail < nRails; ++rail) {
		float xOffset = (rail == 0) ? -railWidth : +railWidth;
		for (int seg = 0; seg < nSegments; ++seg) {
			XMFLOAT3 p0 = centers[seg];
			XMFLOAT3 p1 = centers[seg + 1];

			// ���� ���� ����
			XMFLOAT3 dir = XMFLOAT3(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z);
			float len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
			if (len < 1e-6f) continue;
			dir.x /= len; dir.y /= len; dir.z /= len;

			// Up ����(���� Y��)
			XMFLOAT3 up(0, 1, 0);
			// ������ �¿� ����(����) ���ϱ�
			XMFLOAT3 right = XMFLOAT3(
				up.y * dir.z - up.z * dir.y,
				up.z * dir.x - up.x * dir.z,
				up.x * dir.y - up.y * dir.x
			);
			// ����ȭ
			float rlen = sqrtf(right.x * right.x + right.y * right.y + right.z * right.z);
			if (rlen < 1e-6f) right = XMFLOAT3(1, 0, 0);
			else { right.x /= rlen; right.y /= rlen; right.z /= rlen; }

			// ���� �ڽ� 8�� ������ ���
			XMFLOAT3 corners[8];
			for (int i = 0; i < 2; ++i) { // p0, p1
				XMFLOAT3 base = (i == 0) ? p0 : p1;
				// ���� �߽ɿ��� �¿� ������
				base.x += right.x * xOffset;
				base.y += right.y * xOffset;
				base.z += right.z * xOffset;
				// ���� ������
				XMFLOAT3 upOffset = XMFLOAT3(up.x * railHeight, up.y * railHeight, up.z * railHeight);
				XMFLOAT3 downOffset = XMFLOAT3(-up.x * railHeight, -up.y * railHeight, -up.z * railHeight);
				// 4�� ������(����, �¿�)
				corners[i * 4 + 0] = XMFLOAT3(base.x + upOffset.x, base.y + upOffset.y, base.z + upOffset.z);
				corners[i * 4 + 1] = XMFLOAT3(base.x - upOffset.x, base.y - upOffset.y, base.z - upOffset.z);
				corners[i * 4 + 2] = XMFLOAT3(base.x + downOffset.x, base.y + downOffset.y, base.z + downOffset.z);
				corners[i * 4 + 3] = XMFLOAT3(base.x - downOffset.x, base.y - downOffset.y, base.z - downOffset.z);
			}
			// ���� �߰� (8��)
			int baseIdx = (int)vertices.size();
			for (int i = 0; i < 8; ++i)
				vertices.push_back(DiffusedVertex(corners[i], RANDOM_COLOR));
			// �ε��� �߰� (�ڽ� 12�ﰢ��)
			UINT boxIdx[36] = {
				0,1,2, 1,3,2, // �ո�
				4,5,6, 5,7,6, // �޸�
				0,2,4, 2,6,4, // ��
				1,5,3, 5,7,3, // �Ʒ�
				0,4,1, 1,4,5, // ����
				2,3,6, 3,7,6  // ������
			};
			for (int i = 0; i < 36; ++i)
				indices.push_back(baseIdx + boxIdx[i]);
		}
	}

	m_nVertices = (UINT)vertices.size();
	m_nIndices = (UINT)indices.size();
	m_nStride = sizeof(DiffusedVertex);
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;
}

CFloorMesh::CFloorMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth, float fDepth, int nSubRects)
{
    // 1. ���� ���
    float fHalfWidth = fWidth * 0.5f;
    float fHalfDepth = fDepth * 0.5f;
    float fCellWidth = fWidth / nSubRects;
    float fCellDepth = fDepth / nSubRects;

    // 2. ����/�ε��� ���� ����
    std::vector<DiffusedVertex> vertices;
    std::vector<UINT> indices;

    for (int i = 0; i < nSubRects; ++i) {
        for (int j = 0; j < nSubRects; ++j) {
            float x0 = -fHalfWidth + i * fCellWidth;
            float x1 = -fHalfWidth + (i + 1) * fCellWidth;
            float z0 = -fHalfDepth + j * fCellDepth;
            float z1 = -fHalfDepth + (j + 1) * fCellDepth;

            UINT baseIdx = (UINT)vertices.size();
            vertices.push_back(DiffusedVertex(XMFLOAT3(x0, 0.0f, z0), RANDOM_COLOR));
            vertices.push_back(DiffusedVertex(XMFLOAT3(x1, 0.0f, z0), RANDOM_COLOR));
            vertices.push_back(DiffusedVertex(XMFLOAT3(x1, 0.0f, z1), RANDOM_COLOR));
            vertices.push_back(DiffusedVertex(XMFLOAT3(x0, 0.0f, z1), RANDOM_COLOR));

            // �� ���� �ﰢ�� �ε���
            indices.push_back(baseIdx + 0);
            indices.push_back(baseIdx + 1);
            indices.push_back(baseIdx + 2);
            indices.push_back(baseIdx + 0);
            indices.push_back(baseIdx + 2);
            indices.push_back(baseIdx + 3);
        }
    }

    m_nVertices = (UINT)vertices.size();
    m_nIndices = (UINT)indices.size();
    m_nStride = sizeof(DiffusedVertex);
    m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    // 3. ���� ���� ����
    m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
    m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
    m_d3dVertexBufferView.StrideInBytes = m_nStride;
    m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

    // 4. �ε��� ���� ����
    m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);
    m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
    m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
    m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, 0.0f, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

CTankMesh::CTankMesh(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth, float fHeight, float fDepth, XMFLOAT4 xmf4Color)
	: Mesh(pd3dDevice, pd3dCommandList)
{
	float fx = fWidth * 0.5f, fy = fHeight * 0.5f, fz = fDepth * 0.5f;
	m_nStride = sizeof(DiffusedVertex);
	m_nOffset = 0;
	m_nSlot = 0;
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	std::vector<DiffusedVertex> vertices;
	std::vector<UINT> indices;

	// �Ƣ� Body (Main box of tank) �Ƣ�
	float bodyHeight = fy * 0.6f;
	float topY = bodyHeight;
	float bottomY = -bodyHeight;

	XMFLOAT4 randomcol = RANDOM_COLOR;

	// 8�� ������
	XMFLOAT3 bodyVerts[8] = {
		XMFLOAT3(-fx, bottomY, -fz), // 0
		XMFLOAT3(+fx, bottomY, -fz), // 1
		XMFLOAT3(+fx, topY,   -fz),  // 2
		XMFLOAT3(-fx, topY,   -fz),  // 3
		XMFLOAT3(-fx, bottomY, +fz), // 4
		XMFLOAT3(+fx, bottomY, +fz), // 5
		XMFLOAT3(+fx, topY,   +fz),  // 6
		XMFLOAT3(-fx, topY,   +fz)   // 7
	};
	int baseIdx = (int)vertices.size();
	for (int i = 0; i < 8; ++i)
		vertices.push_back(DiffusedVertex(bodyVerts[i], Vector4::Add(xmf4Color, RANDOM_COLOR)));
	// �ε���(������ü)
	UINT bodyIdx[36] = {
		4,5,6, 4,6,7, // Front (+z)
		1,0,3, 1,3,2, // Back (-z)
		0,4,7, 0,7,3, // Left (-x)
		5,1,2, 5,2,6, // Right (+x)
		3,7,6, 3,6,2, // Top (+y)
		0,1,5, 0,5,4  // Bottom (-y)
	};
	for (int i = 0; i < 36; ++i)
		indices.push_back(baseIdx + bodyIdx[i]);

	// �Ƣ� Turret (��� �ڽ�) �Ƣ�
	float turretWidth = fx * 0.6f;
	float turretHeight = fy * 0.3f;
	float turretTop = topY + turretHeight;
	float turretZFront = +fz * 0.5f;
	float turretZBack = -fz * 0.2f;
	baseIdx = (int)vertices.size();
	XMFLOAT3 turretVerts[8] = {
		XMFLOAT3(-turretWidth, topY, turretZBack), // 0
		XMFLOAT3(+turretWidth, topY, turretZBack), // 1
		XMFLOAT3(+turretWidth, turretTop, turretZBack), // 2
		XMFLOAT3(-turretWidth, turretTop, turretZBack), // 3
		XMFLOAT3(-turretWidth, topY, turretZFront), // 4
		XMFLOAT3(+turretWidth, topY, turretZFront), // 5
		XMFLOAT3(+turretWidth, turretTop, turretZFront), // 6
		XMFLOAT3(-turretWidth, turretTop, turretZFront)  // 7
	};
	for (int i = 0; i < 8; ++i)
		vertices.push_back(DiffusedVertex(turretVerts[i], Vector4::Add(xmf4Color, RANDOM_COLOR)));
	UINT turretIdx[36] = {
		4,5,6, 4,6,7, // Front
		1,0,3, 1,3,2, // Back
		0,4,7, 0,7,3, // Left
		5,1,2, 5,2,6, // Right
		3,7,6, 3,6,2, // Top
		0,1,5, 0,5,4  // Bottom
	};
	for (int i = 0; i < 36; ++i)
		indices.push_back(baseIdx + turretIdx[i]);

	// �Ƣ� Cannon (����) �Ƣ�
	float cannonLength = fz * 1.0f;
	float cannonWidth = fx * 0.2f;
	float cannonTopY = topY + turretHeight * 0.5f;
	baseIdx = (int)vertices.size();
	XMFLOAT3 cannonVerts[8] = {
		XMFLOAT3(-cannonWidth, cannonTopY - cannonWidth, +fz/2), // 0
		XMFLOAT3(+cannonWidth, cannonTopY - cannonWidth, +fz/2), // 1
		XMFLOAT3(+cannonWidth, cannonTopY + cannonWidth, +fz/2), // 2
		XMFLOAT3(-cannonWidth, cannonTopY + cannonWidth, +fz/2), // 3
		XMFLOAT3(-cannonWidth, cannonTopY - cannonWidth, +fz + cannonLength), // 4
		XMFLOAT3(+cannonWidth, cannonTopY - cannonWidth, +fz + cannonLength), // 5
		XMFLOAT3(+cannonWidth, cannonTopY + cannonWidth, +fz + cannonLength), // 6
		XMFLOAT3(-cannonWidth, cannonTopY + cannonWidth, +fz + cannonLength)  // 7
	};
	for (int i = 0; i < 8; ++i)
		vertices.push_back(DiffusedVertex(cannonVerts[i], Vector4::Add(xmf4Color, RANDOM_COLOR)));
	UINT cannonIdx[36] = {
		4,5,6, 4,6,7, // Front
		1,0,3, 1,3,2, // Back
		0,4,7, 0,7,3, // Left
		5,1,2, 5,2,6, // Right
		3,7,6, 3,6,2, // Top
		0,1,5, 0,5,4  // Bottom
	};
	for (int i = 0; i < 36; ++i)
		indices.push_back(baseIdx + cannonIdx[i]);

	// �Ƣ� Wheels (�¿� 4����) �Ƣ�
	float wheelRadius = fy * 0.2f;
	float wheelWidth = fx * 0.15f;
	for (int j = 0; j < 4; ++j) {
		float offsetZ = -fz + (j + 1) * (fDepth / 5.0f);
		// ����
		baseIdx = (int)vertices.size();
		XMFLOAT3 wheelVertsL[8] = {
			XMFLOAT3(-fx - wheelWidth, -fy, offsetZ - wheelRadius),
			XMFLOAT3(-fx, -fy, offsetZ - wheelRadius),
			XMFLOAT3(-fx, -fy + wheelRadius * 2, offsetZ - wheelRadius),
			XMFLOAT3(-fx - wheelWidth, -fy + wheelRadius * 2, offsetZ - wheelRadius),
			XMFLOAT3(-fx - wheelWidth, -fy, offsetZ + wheelRadius),
			XMFLOAT3(-fx, -fy, offsetZ + wheelRadius),
			XMFLOAT3(-fx, -fy + wheelRadius * 2, offsetZ + wheelRadius),
			XMFLOAT3(-fx - wheelWidth, -fy + wheelRadius * 2, offsetZ + wheelRadius)
		};
		for (int i = 0; i < 8; ++i)
			vertices.push_back(DiffusedVertex(wheelVertsL[i], Vector4::Add(xmf4Color, RANDOM_COLOR)));
		UINT wheelIdx[36] = {
			4,5,6, 4,6,7, // Front
			1,0,3, 1,3,2, // Back
			0,4,7, 0,7,3, // Left
			5,1,2, 5,2,6, // Right
			3,7,6, 3,6,2, // Top
			0,1,5, 0,5,4  // Bottom
		};
		for (int i = 0; i < 36; ++i)
			indices.push_back(baseIdx + wheelIdx[i]);

		// ������
		baseIdx = (int)vertices.size();
		XMFLOAT3 wheelVertsR[8] = {
			XMFLOAT3(+fx, -fy, offsetZ - wheelRadius),
			XMFLOAT3(+fx + wheelWidth, -fy, offsetZ - wheelRadius),
			XMFLOAT3(+fx + wheelWidth, -fy + wheelRadius * 2, offsetZ - wheelRadius),
			XMFLOAT3(+fx, -fy + wheelRadius * 2, offsetZ - wheelRadius),
			XMFLOAT3(+fx, -fy, offsetZ + wheelRadius),
			XMFLOAT3(+fx + wheelWidth, -fy, offsetZ + wheelRadius),
			XMFLOAT3(+fx + wheelWidth, -fy + wheelRadius * 2, offsetZ + wheelRadius),
			XMFLOAT3(+fx, -fy + wheelRadius * 2, offsetZ + wheelRadius)
		};
		for (int i = 0; i < 8; ++i)
			vertices.push_back(DiffusedVertex(wheelVertsR[i], Vector4::Add(xmf4Color, RANDOM_COLOR)));
		for (int i = 0; i < 36; ++i)
			indices.push_back(baseIdx + wheelIdx[i]);
	}

	m_nVertices = (UINT)vertices.size();
	m_nIndices = (UINT)indices.size();

	// ���� ���� ����
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	// �ε��� ���� ����
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fx, fy, fz), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}