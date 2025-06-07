#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList) {

}

Mesh::~Mesh() {
	// 버텍스 버퍼 & 업로드 버퍼
	if (m_pd3dVertexBuffer) 		m_pd3dVertexBuffer->Release();
	if (m_pd3dVertexUploadBuffer) 	m_pd3dVertexUploadBuffer->Release();
	
	// 인덱스 버퍼 & 업로드 버퍼
	if (m_pd3dIndexBuffer)			m_pd3dIndexBuffer->Release();
	if (m_pd3dIndexUploadBuffer)	m_pd3dIndexUploadBuffer->Release();

	//피킹을 위해
	if (m_pVertices) delete[] m_pVertices;
	if (m_pnIndices) delete[] m_pnIndices;
}

void Mesh::ReleaseUploadBuffers() {
	// 정점 버퍼를 위한 업로드 버퍼를 소멸시킨다.
	if (m_pd3dVertexUploadBuffer) m_pd3dVertexUploadBuffer->Release();
	m_pd3dVertexUploadBuffer = NULL;

	// 인덱스 버퍼를 위한 업로드 버퍼를 소멸시킨다.
	if (m_pd3dIndexUploadBuffer) m_pd3dIndexUploadBuffer->Release();
	m_pd3dIndexUploadBuffer = NULL;
};

void Mesh::Render(ID3D12GraphicsCommandList *pd3dCommandList) {
	//메쉬의 프리미티브 유형을 설정한다.
	pd3dCommandList->IASetPrimitiveTopology(m_d3dPrimitiveTopology);

	//메쉬의 정점 버퍼 뷰를 설정한다.
	// 정점버퍼의 시작 입력 슬롯(디바이스), 정점 버퍼의 개수, 정점버퍼 뷰 주소
	pd3dCommandList->IASetVertexBuffers(m_nSlot, 1, &m_d3dVertexBufferView);
	
	//인덱스 버퍼가 있으면 인덱스 버퍼를 파이프라인(IA: 입력 조립기)에 연결하고 인덱스를 사용하여 렌더링
	if (m_pd3dIndexBuffer) {
		// 파이프라인에 하나의 인덱스 버퍼 연결 가능
		// 인덱스 버퍼 주소
		pd3dCommandList->IASetIndexBuffer(&m_d3dIndexBufferView);

		// 인덱스 개수, 객체 수, 시작 인덱스 위치, 각 정점 인덱스에 더해질 값, 객체 인덱스에 더해질 값
		pd3dCommandList->DrawIndexedInstanced(m_nIndices, 1, 0, 0, 0);
	} 

	//메쉬의 정점 버퍼 뷰를 렌더링 (파이프라인(입력 조립기)을 작동하게 한다).
	// 정점 개수, 객체 수, 시작 정점 위치, 객체 인덱스에 더해질 값
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
//	//하나의 메쉬에서 광선은 여러 개의 삼각형과 교차할 수 있다. 교차하는 삼각형들 중 가장 가까운 삼각형을 찾는다.
//	int nIntersections = 0;
//	BYTE* pbPositions = (BYTE*)m_pVertices;
//	int nOffset = (m_d3dPrimitiveTopology == D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST) ? 3 : 1;
//	/*메쉬의 프리미티브(삼각형)들의 개수이다. 삼각형 리스트인 경우 (정점의 개수 / 3) 또는 (인덱스의 개수 / 3), 삼각
//   형 스트립의 경우 (정점의 개수 - 2) 또는 (인덱스의 개수 ? 2)이다.*/
//	int nPrimitives = (m_d3dPrimitiveTopology == D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST) ?
//		(m_nVertices / 3) : (m_nVertices - 2);
//	if (m_nIndices > 0) nPrimitives = (m_d3dPrimitiveTopology ==
//		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST) ? (m_nIndices / 3) : (m_nIndices - 2);
//	//광선은 모델 좌표계로 표현된다.
//	XMVECTOR xmRayOrigin = XMLoadFloat3(&xmf3RayOrigin);
//	XMVECTOR xmRayDirection = XMLoadFloat3(&xmf3RayDirection);
//	//모델 좌표계의 광선과 메쉬의 바운딩 박스(모델 좌표계)와의 교차를 검사한다.
//	bool bIntersected = m_xmBoundingBox.Intersects(xmRayOrigin, xmRayDirection,
//		*pfNearHitDistance);
//	//모델 좌표계의 광선이 메쉬의 바운딩 박스와 교차하면 메쉬와의 교차를 검사한다.
//	if (bIntersected)
//	{
//		float fNearHitDistance = FLT_MAX;
//		/*메쉬의 모든 프리미티브(삼각형)들에 대하여 픽킹 광선과의 충돌을 검사한다. 충돌하는 모든 삼각형을 찾아 광선의
//	   시작점(실제로는 카메라 좌표계의 원점)에 가장 가까운 삼각형을 찾는다.*/
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
	//월드 좌표게에서 Intersects를 먼저 호출하고 
	bool bIntersected = m_xmOOBB.Intersects(xmvPickRayOrigin, xmvPickRayDirection, *pfNearHitDistance); //모델좌표게에서 인터섹션 검사
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
				//삼각형이면 삼각형 하나를 가져다가 가장 가까운 삼각형의 거리를 가져온다
				BOOL bIntersected = RayIntersectionByTriangle(xmvPickRayOrigin, xmvPickRayDirection, v0, v1, v2, pfNearHitDistance);
				if (bIntersected) nIntersections++;
				break;
			}
			case 4:
			{
				//사각형인 경우 삼각형이 2개니까 2번을 해준다.
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
	// 삼각형 메쉬를 정의한다.
	// 메쉬의 정점의 개수
	m_nVertices = 3;
	// 메쉬의 색상, 위치를 가진 정점을 표현하는 class의 크기 - 정점 버퍼 원소 하나의 크기
	m_nStride = sizeof(DiffusedVertex);
	// Primitive Topology
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	//정점(삼각형의 꼭지점)의 색상은 시계방향 순서대로 빨간색, 녹색, 파란색으로 지정한다.
	//RGBA(Red, Green, Blue, Alpha) 4개의 파라메터를 사용하여 색상을 표현한다.
	//각 파라메터는 0.0~1.0 사이의 실수값을 가진다.

	// 색, 위치 정보를 가진 정점 3개 생성
	DiffusedVertex pVertices[3];
	pVertices[0] = DiffusedVertex(XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	pVertices[1] = DiffusedVertex(XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	pVertices[2] = DiffusedVertex(XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::Blue));

	// 삼각형 메쉬를 리소스(정점 버퍼)로 생성한다.
	// 리소스와 내부적 힙을 동시에 생성
	// 디바이스, 커맨드 리스트, 정점데이터 주소, 정점 버퍼 전체의 크기, 힙의 유형, 리소스 버퍼의 상태, 업로드 버퍼의 주소
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);

	// 정점 버퍼 뷰를 생성한다.
	// 정점 버퍼 주소
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	// 정점 버퍼 전체의 크기
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;
	// 정점 버퍼 각 원소의 크기, 하나의 정점 크기
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
}

CubeMeshDiffused::CubeMeshDiffused(ID3D12Device * pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList,
	float fWidth, float fHeight, float fDepth){

	// 객체에 필요한 정점 수 8개 (직육면체)
	m_nVertices = 8;
	m_nStride = sizeof(DiffusedVertex);
	
	m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	
	//fWidth: 직육면체 가로(x-축) 길이, fHeight: 직육면체 세로(y-축) 길이, fDepth: 직육면체 깊이(z-축) 길이 
	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f;
	
	// [1] 정점 버퍼
	//정점 버퍼는 직육면체의 꼭지점 8개에 대한 정점 데이터를 가진다.
	DiffusedVertex pVertices[8];
	pVertices[0] = DiffusedVertex(XMFLOAT3(-fx, +fy, -fz), RANDOM_COLOR);
	pVertices[1] = DiffusedVertex(XMFLOAT3(+fx, +fy, -fz), RANDOM_COLOR);
	pVertices[2] = DiffusedVertex(XMFLOAT3(+fx, +fy, +fz), RANDOM_COLOR);
	pVertices[3] = DiffusedVertex(XMFLOAT3(-fx, +fy, +fz), RANDOM_COLOR);
	pVertices[4] = DiffusedVertex(XMFLOAT3(-fx, -fy, -fz), RANDOM_COLOR);
	pVertices[5] = DiffusedVertex(XMFLOAT3(+fx, -fy, -fz), RANDOM_COLOR);
	pVertices[6] = DiffusedVertex(XMFLOAT3(+fx, -fy, +fz), RANDOM_COLOR);
	pVertices[7] = DiffusedVertex(XMFLOAT3(-fx, -fy, +fz), RANDOM_COLOR);

	// 삼각형 메쉬를 리소스(정점 버퍼)로 생성한다.
	// 리소스와 내부적 힙을 동시에 생성
	// 디바이스, 커맨드 리스트, 정점데이터 주소, 정점 버퍼 전체의 크기, 힙의 유형(기본), 리소스 버퍼의 상태(상수버퍼), 업로드 버퍼의 주소
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pVertices, m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	
	//정점 버퍼 뷰를 생성한다.
	// 정점 버퍼 주소
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	// 정점 버퍼 각 원소의 크기, 하나의 정점 크기
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	// 정점 버퍼 전체의 크기
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;


	// [2] 인덱스 버퍼
	/*인덱스 버퍼는 직육면체의 6개의 면(사각형)에 대한 기하 정보를 갖는다.
	삼각형 리스트로 직육면체를 표현할 것이 므로 각 면은 2개의 삼각형을 가지고 각 삼각형은 3개의 정점이 필요하다.
	즉, 인덱스 버퍼는 전체 36(=6*2*3)개의 인 덱스를 가져야 한다.*/
	
	// 8개의 정점으로 36개의 삼각형 꼭지점 정하기
	// 인덱스 개수
	m_nIndices = 36;
	UINT pnIndices[36];

	//ⓐ 앞면(Front) 사각형의 위쪽 삼각형
	pnIndices[0] = 3; pnIndices[1] = 1; pnIndices[2] = 0;
	//ⓑ 앞면(Front) 사각형의 아래쪽 삼각형
	pnIndices[3] = 2; pnIndices[4] = 1; pnIndices[5] = 3;
	//ⓒ 윗면(Top) 사각형의 위쪽 삼각형
	pnIndices[6] = 0; pnIndices[7] = 5; pnIndices[8] = 4;
	//ⓓ 윗면(Top) 사각형의 아래쪽 삼각형
	pnIndices[9] = 1; pnIndices[10] = 5; pnIndices[11] = 0;
	//ⓔ 뒷면(Back) 사각형의 위쪽 삼각형
	pnIndices[12] = 3; pnIndices[13] = 4; pnIndices[14] = 7;
	//ⓕ 뒷면(Back) 사각형의 아래쪽 삼각형
	pnIndices[15] = 0; pnIndices[16] = 4; pnIndices[17] = 3;
	//ⓖ 아래면(Bottom) 사각형의 위쪽 삼각형   
	pnIndices[18] = 1; pnIndices[19] = 6; pnIndices[20] = 5;
	//ⓗ 아래면(Bottom) 사각형의 아래쪽 삼각형   
	pnIndices[21] = 2; pnIndices[22] = 6; pnIndices[23] = 1;
	//ⓘ 옆면(Left) 사각형의 위쪽 삼각형   
	pnIndices[24] = 2; pnIndices[25] = 7; pnIndices[26] = 6;
	//ⓙ 옆면(Left) 사각형의 아래쪽 삼각형 
	pnIndices[27] = 3; pnIndices[28] = 7; pnIndices[29] = 2;
	//ⓚ 옆면(Right) 사각형의 위쪽 삼각형   
	pnIndices[30] = 6; pnIndices[31] = 4; pnIndices[32] = 5;
	//ⓛ 옆면(Right) 사각형의 아래쪽 삼각형   
	pnIndices[33] = 7; pnIndices[34] = 4; pnIndices[35] = 6;

	//인덱스 버퍼를 생성
	// 디바이스, 커맨드 리스트, 정점데이터 주소, 정점 버퍼 전체의 크기, 힙의 유형(기본), 리소스 버퍼의 상태(인덱스 버퍼), 업로드 버퍼의 주소
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, pnIndices, sizeof(UINT) * m_nIndices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);
	
	//인덱스 버퍼 뷰를 생성
	// 인덱스 버퍼 주소
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	// 인덱스 버퍼 포멧
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	// 인덱스 버퍼 전체 크기 : UINT * 인덱스의 개수
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices; 
	//중심 , 크기 , 0,0,0,1은 회전이 전혀 없는 쿼터니언을 의미함
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

	//위의 그림과 같은 비행기 메쉬를 표현하기 위한 정점 데이터이다.
	DiffusedVertex pVertices[24 * 3];
	float x1 = fx * 0.2f, y1 = fy * 0.2f, x2 = fx * 0.1f, y3 = fy * 0.3f, y2 = ((y1 - (fy - y3)) / x1) * x2 + (fy - y3);
	int i = 0;

	XMFLOAT4 randomcol = RANDOM_COLOR;

	//비행기 메쉬의 위쪽 면
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
	
	//비행기 메쉬의 아래쪽 면
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
	
	//비행기 메쉬의 오른쪽 면
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
	
	//비행기 메쉬의 뒤쪽/오른쪽 면
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
	
	//비행기 메쉬의 왼쪽 면
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
	
	//비행기 메쉬의 뒤쪽/왼쪽 면
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
	// 바디(직육면체) + 바퀴(4개 큐브)로 구성
	const int nBodyVertices = 8;
	const int nBodyIndices = 36;
	const int nWheelVertices = 8 * 4;
	const int nWheelIndices = 36 * 4;

	const int nVertices = nBodyVertices + nWheelVertices;
	const int nIndices = nBodyIndices + nWheelIndices;

	std::vector<DiffusedVertex> vertices;
	std::vector<UINT> indices;

	// 바디(직육면체)
	float fx = fWidth * 0.5f, fy = fHeight * 0.5f, fz = fDepth * 0.5f;
	float bodyHeight = fy * 0.6f;
	float topY = bodyHeight;
	float bottomY = -bodyHeight;

	// 바디 정점
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

	// 바디 인덱스 (직육면체)
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

	// 바퀴(4개 큐브, 각 8정점 36인덱스)
	float wheelRadius = fy * 0.2f;
	float wheelWidth = fWidth * 0.15f;
	float wheelY = -fy + wheelRadius;
	float wheelZ[2] = { -fz + fDepth / 4.0f, -fz + 3 * fDepth / 4.0f };
	float wheelX[2] = { -fx + wheelWidth / 2.0f, +fx - wheelWidth / 2.0f };

	for (int w = 0; w < 4; ++w) {
		float cx = (w < 2) ? wheelX[0] : wheelX[1];
		float cz = (w % 2 == 0) ? wheelZ[0] : wheelZ[1];
		// 바퀴 큐브의 8정점
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
		// 바퀴 인덱스 (직육면체)
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

	// 정점 버퍼 생성
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	// 인덱스 버퍼 생성
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;
}

// CubeMeshDiffused처럼 정점/인덱스 버퍼 기반으로 CRollerCoasterMesh_Up 구현 (예시)

CRollerCoasterMesh_Up::CRollerCoasterMesh_Up(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, float fWidth, float fHeight, float fDepth) : Mesh(pd3dDevice, pd3dCommandList)
{
	// 두꺼운 레일을 위해 각 면을 박스 형태로 구성 (상하/좌우 두께 추가)
	const int nSegments = 12;
	const int nRails = 2; // 레일 2줄
	const float railWidth = fDepth * 0.3f; // 레일 두께(좌우)
	const float railHeight = fHeight * 0.02f; // 레일 두께(상하)

	std::vector<DiffusedVertex> vertices;
	std::vector<UINT> indices;

	// 레일 중심선 좌표 정의 (기존 faceVerts의 중심선)
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

	// 레일 2줄(좌/우) 각각 박스 형태로 생성
	for (int rail = 0; rail < nRails; ++rail) {
		float xOffset = (rail == 0) ? -railWidth : +railWidth;
		for (int seg = 0; seg < nSegments; ++seg) {
			XMFLOAT3 p0 = centers[seg];
			XMFLOAT3 p1 = centers[seg + 1];

			// 레일 방향 벡터
			XMFLOAT3 dir = XMFLOAT3(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z);
			float len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
			if (len < 1e-6f) continue;
			dir.x /= len; dir.y /= len; dir.z /= len;

			// Up 벡터(월드 Y축)
			XMFLOAT3 up(0, 1, 0);
			// 레일의 좌우 방향(법선) 구하기
			XMFLOAT3 right = XMFLOAT3(
				up.y * dir.z - up.z * dir.y,
				up.z * dir.x - up.x * dir.z,
				up.x * dir.y - up.y * dir.x
			);
			// 정규화
			float rlen = sqrtf(right.x * right.x + right.y * right.y + right.z * right.z);
			if (rlen < 1e-6f) right = XMFLOAT3(1, 0, 0);
			else { right.x /= rlen; right.y /= rlen; right.z /= rlen; }

			// 레일 박스 8개 꼭짓점 계산
			XMFLOAT3 corners[8];
			for (int i = 0; i < 2; ++i) { // p0, p1
				XMFLOAT3 base = (i == 0) ? p0 : p1;
				// 레일 중심에서 좌우 오프셋
				base.x += right.x * xOffset;
				base.y += right.y * xOffset;
				base.z += right.z * xOffset;
				// 상하 오프셋
				XMFLOAT3 upOffset = XMFLOAT3(up.x * railHeight, up.y * railHeight, up.z * railHeight);
				XMFLOAT3 downOffset = XMFLOAT3(-up.x * railHeight, -up.y * railHeight, -up.z * railHeight);
				// 4개 꼭짓점(상하, 좌우)
				corners[i * 4 + 0] = XMFLOAT3(base.x + upOffset.x, base.y + upOffset.y, base.z + upOffset.z);
				corners[i * 4 + 1] = XMFLOAT3(base.x - upOffset.x, base.y - upOffset.y, base.z - upOffset.z);
				corners[i * 4 + 2] = XMFLOAT3(base.x + downOffset.x, base.y + downOffset.y, base.z + downOffset.z);
				corners[i * 4 + 3] = XMFLOAT3(base.x - downOffset.x, base.y - downOffset.y, base.z - downOffset.z);
			}
			// 정점 추가 (8개)
			int baseIdx = (int)vertices.size();
			for (int i = 0; i < 8; ++i)
				vertices.push_back(DiffusedVertex(corners[i], RANDOM_COLOR));
			// 인덱스 추가 (박스 12삼각형)
			UINT boxIdx[36] = {
				0,1,2, 1,3,2, // 앞면
				4,5,6, 5,7,6, // 뒷면
				0,2,4, 2,6,4, // 위
				1,5,3, 5,7,3, // 아래
				0,4,1, 1,4,5, // 왼쪽
				2,3,6, 3,7,6  // 오른쪽
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
    // 1. 변수 계산
    float fHalfWidth = fWidth * 0.5f;
    float fHalfDepth = fDepth * 0.5f;
    float fCellWidth = fWidth / nSubRects;
    float fCellDepth = fDepth / nSubRects;

    // 2. 정점/인덱스 버퍼 생성
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

            // 두 개의 삼각형 인덱스
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

    // 3. 정점 버퍼 생성
    m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
        D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
    m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
    m_d3dVertexBufferView.StrideInBytes = m_nStride;
    m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

    // 4. 인덱스 버퍼 생성
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

	// ▒▒ Body (Main box of tank) ▒▒
	float bodyHeight = fy * 0.6f;
	float topY = bodyHeight;
	float bottomY = -bodyHeight;

	XMFLOAT4 randomcol = RANDOM_COLOR;

	// 8개 꼭짓점
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
	// 인덱스(직육면체)
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

	// ▒▒ Turret (상단 박스) ▒▒
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

	// ▒▒ Cannon (포신) ▒▒
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

	// ▒▒ Wheels (좌우 4개씩) ▒▒
	float wheelRadius = fy * 0.2f;
	float wheelWidth = fx * 0.15f;
	for (int j = 0; j < 4; ++j) {
		float offsetZ = -fz + (j + 1) * (fDepth / 5.0f);
		// 왼쪽
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

		// 오른쪽
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

	// 정점 버퍼 생성
	m_pd3dVertexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, vertices.data(), m_nStride * m_nVertices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3dVertexUploadBuffer);
	m_d3dVertexBufferView.BufferLocation = m_pd3dVertexBuffer->GetGPUVirtualAddress();
	m_d3dVertexBufferView.StrideInBytes = m_nStride;
	m_d3dVertexBufferView.SizeInBytes = m_nStride * m_nVertices;

	// 인덱스 버퍼 생성
	m_pd3dIndexBuffer = ::CreateBufferResource(pd3dDevice, pd3dCommandList, indices.data(), sizeof(UINT) * m_nIndices,
		D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3dIndexUploadBuffer);
	m_d3dIndexBufferView.BufferLocation = m_pd3dIndexBuffer->GetGPUVirtualAddress();
	m_d3dIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	m_d3dIndexBufferView.SizeInBytes = sizeof(UINT) * m_nIndices;

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fx, fy, fz), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}