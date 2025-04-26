#include "stdafx.h"
#include "Mesh.h"
#include "GraphicsPipeline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPolygon::CPolygon(int nVertices)
{
	m_nVertices = nVertices;
	m_pVertices = new CVertex[nVertices];
}

CPolygon::~CPolygon()
{
	if (m_pVertices) delete[] m_pVertices;
}

void CPolygon::SetVertex(int nIndex, CVertex& vertex)
{
	if ((0 <= nIndex) && (nIndex < m_nVertices) && m_pVertices)
	{
		m_pVertices[nIndex] = vertex;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CMesh::CMesh(int nPolygons)
{
	m_nPolygons = nPolygons;
	m_ppPolygons = new CPolygon*[nPolygons];
}

CMesh::~CMesh()
{
	if (m_ppPolygons)
	{
		for (int i = 0; i < m_nPolygons; i++) if (m_ppPolygons[i]) delete m_ppPolygons[i];
		delete[] m_ppPolygons;
	}
}

void CMesh::SetPolygon(int nIndex, CPolygon *pPolygon)
{
	//메쉬의 다각형을 설정한다
	if ((0 <= nIndex) && (nIndex < m_nPolygons)) m_ppPolygons[nIndex] = pPolygon;
}

void Draw2DLine(HDC hDCFrameBuffer, XMFLOAT3& f3PreviousProject, XMFLOAT3& f3CurrentProject)
{
	//투영 좌표계의 2점을 화면 좌표계로 변환하고 변환된 두 점(픽셀)을 선분으로 그린다.  
	XMFLOAT3 f3Previous = CGraphicsPipeline::ScreenTransform(f3PreviousProject);
	XMFLOAT3 f3Current = CGraphicsPipeline::ScreenTransform(f3CurrentProject);
	::MoveToEx(hDCFrameBuffer, (long)f3Previous.x, (long)f3Previous.y, NULL);
	::LineTo(hDCFrameBuffer, (long)f3Current.x, (long)f3Current.y);
}

void CMesh::Render(HDC hDCFrameBuffer)
{
	XMFLOAT3 f3InitialProject, f3PreviousProject;
	bool bPreviousInside = false, bInitialInside = false, bCurrentInside = false, bIntersectInside = false;

	for (int j = 0; j < m_nPolygons; j++)  //메쉬를 구성하고 있는 모든 폴리곤들에 대해
	{
		int nVertices = m_ppPolygons[j]->m_nVertices;
		CVertex* pVertices = m_ppPolygons[j]->m_pVertices;

		//다각형의 첫 번째 정점을 원근 투영 변환한다. 
		f3PreviousProject = f3InitialProject = CGraphicsPipeline::Project(pVertices[0].m_xmf3Position); //투영변환

		//변환된 점이 투영 사각형에 포함되는 가를 계산한다.
		bPreviousInside = bInitialInside = (-1.0f <= f3InitialProject.x) && (f3InitialProject.x <= 1.0f) && (-1.0f <= f3InitialProject.y) && (f3InitialProject.y <= 1.0f);

		//다각형을 구성하는 모든 정점들을 원근 투영 변환하고 선분으로 렌더링한다.
		for (int i = 1; i < nVertices; i++)
		{
			XMFLOAT3 f3CurrentProject = CGraphicsPipeline::Project(pVertices[i].m_xmf3Position);
			bCurrentInside = (-1.0f <= f3CurrentProject.x) && (f3CurrentProject.x <= 1.0f) && (-1.0f <= f3CurrentProject.y) && (f3CurrentProject.y <= 1.0f);

			//변환된 점이 투영 사각형에 포함되면 이전 점과 현재 점을 선분으로 그린다.
			if (((0.0f <= f3CurrentProject.z) && (f3CurrentProject.z <= 1.0f)) && ((bCurrentInside || bPreviousInside))) ::Draw2DLine(hDCFrameBuffer, f3PreviousProject, f3CurrentProject); //:: 전역에 있는 함수 사용
			f3PreviousProject = f3CurrentProject;
			bPreviousInside = bCurrentInside;
		}
		if (((0.0f <= f3InitialProject.z) && (f3InitialProject.z <= 1.0f)) && ((bInitialInside || bPreviousInside))) ::Draw2DLine(hDCFrameBuffer, f3PreviousProject, f3InitialProject);
	}
}

BOOL CMesh::RayIntersectionByTriangle(XMVECTOR& xmRayOrigin, XMVECTOR& xmRayDirection, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* pfNearHitDistance)
{
	float fHitDistance;
	BOOL bIntersected = TriangleTests::Intersects(xmRayOrigin, xmRayDirection, v0, v1, v2, fHitDistance);
	if (bIntersected && (fHitDistance < *pfNearHitDistance)) *pfNearHitDistance = fHitDistance;

	return(bIntersected);
}

int CMesh::CheckRayIntersection(XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection, float* pfNearHitDistance)
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CCubeMesh::CCubeMesh(float fWidth, float fHeight, float fDepth) : CMesh(6)
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;
	float fHalfDepth = fDepth * 0.5f;

	CPolygon *pFrontFace = new CPolygon(4);
	pFrontFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	SetPolygon(0, pFrontFace);

	CPolygon *pTopFace = new CPolygon(4);
	pTopFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight, +fHalfDepth));
	pTopFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight, +fHalfDepth));
	pTopFace->SetVertex(2, CVertex(+fHalfWidth, +fHalfHeight, -fHalfDepth));
	pTopFace->SetVertex(3, CVertex(-fHalfWidth, +fHalfHeight, -fHalfDepth));
	SetPolygon(1, pTopFace);

	CPolygon *pBackFace = new CPolygon(4);
	pBackFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(2, CVertex(+fHalfWidth, +fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(3, CVertex(-fHalfWidth, +fHalfHeight, +fHalfDepth));
	SetPolygon(2, pBackFace);

	CPolygon *pBottomFace = new CPolygon(4);
	pBottomFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	pBottomFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	pBottomFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBottomFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	SetPolygon(3, pBottomFace);

	CPolygon *pLeftFace = new CPolygon(4);
	pLeftFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight, +fHalfDepth));
	pLeftFace->SetVertex(1, CVertex(-fHalfWidth, +fHalfHeight, -fHalfDepth));
	pLeftFace->SetVertex(2, CVertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	pLeftFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	SetPolygon(4, pLeftFace);

	CPolygon *pRightFace = new CPolygon(4);
	pRightFace->SetVertex(0, CVertex(+fHalfWidth, +fHalfHeight, -fHalfDepth));
	pRightFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight, +fHalfDepth));
	pRightFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pRightFace->SetVertex(3, CVertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	SetPolygon(5, pRightFace);

	//중심 , 크기 , 0,0,0,1은 회전이 전혀 없는 쿼터니언을 의미함
	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)); 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CWallMesh::CWallMesh(float fWidth, float fHeight, float fDepth, int nSubRects) : CMesh((4 * nSubRects * nSubRects) + 2)
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;
	float fHalfDepth = fDepth * 0.5f;
	float fCellWidth = fWidth * (1.0f / nSubRects);
	float fCellHeight = fHeight * (1.0f / nSubRects);
	float fCellDepth = fDepth * (1.0f / nSubRects);

	int k = 0;
	CPolygon* pLeftFace;
	for (int i = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			pLeftFace = new CPolygon(4);
			pLeftFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight + (i * fCellHeight), -fHalfDepth + (j * fCellDepth)));
			pLeftFace->SetVertex(1, CVertex(-fHalfWidth, -fHalfHeight + ((i + 1) * fCellHeight), -fHalfDepth + (j * fCellDepth)));
			pLeftFace->SetVertex(2, CVertex(-fHalfWidth, -fHalfHeight + ((i + 1) * fCellHeight), -fHalfDepth + ((j + 1) * fCellDepth)));
			pLeftFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight + (i * fCellHeight), -fHalfDepth + ((j + 1) * fCellDepth)));
			SetPolygon(k++, pLeftFace);
		}
	}

	CPolygon* pRightFace;
	for (int i = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			pRightFace = new CPolygon(4);
			pRightFace->SetVertex(0, CVertex(+fHalfWidth, -fHalfHeight + (i * fCellHeight), -fHalfDepth + (j * fCellDepth)));
			pRightFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight + ((i + 1) * fCellHeight), -fHalfDepth + (j * fCellDepth)));
			pRightFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight + ((i + 1) * fCellHeight), -fHalfDepth + ((j + 1) * fCellDepth)));
			pRightFace->SetVertex(3, CVertex(+fHalfWidth, -fHalfHeight + (i * fCellHeight), -fHalfDepth + ((j + 1) * fCellDepth)));
			SetPolygon(k++, pRightFace);
		}
	}

	CPolygon* pTopFace;
	for (int i = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			pTopFace = new CPolygon(4);
			pTopFace->SetVertex(0, CVertex(-fHalfWidth + (i * fCellWidth), +fHalfHeight, -fHalfDepth + (j * fCellDepth)));
			pTopFace->SetVertex(1, CVertex(-fHalfWidth + ((i + 1) * fCellWidth), +fHalfHeight, -fHalfDepth + (j * fCellDepth)));
			pTopFace->SetVertex(2, CVertex(-fHalfWidth + ((i + 1) * fCellWidth), +fHalfHeight, -fHalfDepth + ((j + 1) * fCellDepth)));
			pTopFace->SetVertex(3, CVertex(-fHalfWidth + (i * fCellWidth), +fHalfHeight, -fHalfDepth + ((j + 1) * fCellDepth)));
			SetPolygon(k++, pTopFace);
		}
	}

	CPolygon* pBottomFace;
	for (int i = 0; i < nSubRects; i++)
	{
		for (int j = 0; j < nSubRects; j++)
		{
			pBottomFace = new CPolygon(4);
			pBottomFace->SetVertex(0, CVertex(-fHalfWidth + (i * fCellWidth), -fHalfHeight, -fHalfDepth + (j * fCellDepth)));
			pBottomFace->SetVertex(1, CVertex(-fHalfWidth + ((i + 1) * fCellWidth), -fHalfHeight, -fHalfDepth + (j * fCellDepth)));
			pBottomFace->SetVertex(2, CVertex(-fHalfWidth + ((i + 1) * fCellWidth), -fHalfHeight, -fHalfDepth + ((j + 1) * fCellDepth)));
			pBottomFace->SetVertex(3, CVertex(-fHalfWidth + (i * fCellWidth), -fHalfHeight, -fHalfDepth + ((j + 1) * fCellDepth)));
			SetPolygon(k++, pBottomFace);
		}
	}

	CPolygon* pFrontFace = new CPolygon(4);
	pFrontFace->SetVertex(0, CVertex(-fHalfWidth, +fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(1, CVertex(+fHalfWidth, +fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(2, CVertex(+fHalfWidth, -fHalfHeight, -fHalfDepth));
	pFrontFace->SetVertex(3, CVertex(-fHalfWidth, -fHalfHeight, -fHalfDepth));
	SetPolygon(k++, pFrontFace);

	CPolygon* pBackFace = new CPolygon(4);
	pBackFace->SetVertex(0, CVertex(-fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(1, CVertex(+fHalfWidth, -fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(2, CVertex(+fHalfWidth, +fHalfHeight, +fHalfDepth));
	pBackFace->SetVertex(3, CVertex(-fHalfWidth, +fHalfHeight, +fHalfDepth));
	SetPolygon(k++, pBackFace);

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CAirplaneMesh::CAirplaneMesh(float fWidth, float fHeight, float fDepth) : CMesh(24)
{
	float fx = fWidth*0.5f, fy = fHeight*0.5f, fz = fDepth*0.5f; // 너비 , 높이 , 깊이 2분의로 나눔

	float x1 = fx * 0.2f, y1 = fy * 0.2f, x2 = fx * 0.1f, y3 = fy * 0.3f, y2 = ((y1 - (fy - y3)) / x1)*x2 + (fy - y3);
	int i = 0;

	//Upper Plane
	CPolygon *pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), -fz));
	pFace->SetVertex(1, CVertex(+x1, -y1, -fz));
	pFace->SetVertex(2, CVertex(0.0f, 0.0f, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), -fz));
	pFace->SetVertex(1, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(2, CVertex(-x1, -y1, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x2, +y2, -fz));
	pFace->SetVertex(1, CVertex(+fx, -y3, -fz));
	pFace->SetVertex(2, CVertex(+x1, -y1, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x2, +y2, -fz));
	pFace->SetVertex(1, CVertex(-x1, -y1, -fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, -fz));
	SetPolygon(i++, pFace);

	//Lower Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(1, CVertex(0.0f, 0.0f, +fz));
	pFace->SetVertex(2, CVertex(+x1, -y1, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(1, CVertex(-x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(0.0f, 0.0f, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x2, +y2, +fz));
	pFace->SetVertex(1, CVertex(+x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(+fx, -y3, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x2, +y2, +fz));
	pFace->SetVertex(1, CVertex(-fx, -y3, +fz));
	pFace->SetVertex(2, CVertex(-x1, -y1, +fz));
	SetPolygon(i++, pFace);

	//Right Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), -fz));
	pFace->SetVertex(1, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(2, CVertex(+x2, +y2, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x2, +y2, -fz));
	pFace->SetVertex(1, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(2, CVertex(+x2, +y2, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x2, +y2, -fz));
	pFace->SetVertex(1, CVertex(+x2, +y2, +fz));
	pFace->SetVertex(2, CVertex(+fx, -y3, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+fx, -y3, -fz));
	pFace->SetVertex(1, CVertex(+x2, +y2, +fz));
	pFace->SetVertex(2, CVertex(+fx, -y3, +fz));
	SetPolygon(i++, pFace);

	//Back/Right Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x1, -y1, -fz));
	pFace->SetVertex(1, CVertex(+fx, -y3, -fz));
	pFace->SetVertex(2, CVertex(+fx, -y3, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(+x1, -y1, -fz));
	pFace->SetVertex(1, CVertex(+fx, -y3, +fz));
	pFace->SetVertex(2, CVertex(+x1, -y1, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(1, CVertex(+x1, -y1, -fz));
	pFace->SetVertex(2, CVertex(+x1, -y1, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(1, CVertex(+x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(0.0f, 0.0f, +fz));
	SetPolygon(i++, pFace);

	//Left Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(1, CVertex(0.0f, +(fy + y3), -fz));
	pFace->SetVertex(2, CVertex(-x2, +y2, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, +(fy + y3), +fz));
	pFace->SetVertex(1, CVertex(-x2, +y2, -fz));
	pFace->SetVertex(2, CVertex(-x2, +y2, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x2, +y2, +fz));
	pFace->SetVertex(1, CVertex(-x2, +y2, -fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x2, +y2, +fz));
	pFace->SetVertex(1, CVertex(-fx, -y3, -fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, +fz));
	SetPolygon(i++, pFace);

	//Back/Left Plane
	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(1, CVertex(0.0f, 0.0f, +fz));
	pFace->SetVertex(2, CVertex(-x1, -y1, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(0.0f, 0.0f, -fz));
	pFace->SetVertex(1, CVertex(-x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(-x1, -y1, -fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x1, -y1, -fz));
	pFace->SetVertex(1, CVertex(-x1, -y1, +fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, +fz));
	SetPolygon(i++, pFace);

	pFace = new CPolygon(3);
	pFace->SetVertex(0, CVertex(-x1, -y1, -fz));
	pFace->SetVertex(1, CVertex(-fx, -y3, +fz));
	pFace->SetVertex(2, CVertex(-fx, -y3, -fz));
	SetPolygon(i++, pFace);

	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fx, fy, fz), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}
//-----------------------------------------------------------------------------------------------------
//   탱크
//-----------------------------------------------------------------------------------------------------
CTankMesh::CTankMesh(float fWidth, float fHeight, float fDepth) : CMesh(14) {
	float fx = fWidth * 0.5f, fy = fHeight * 0.5f, fz = fDepth * 0.5f;

	int i = 0;
	CPolygon* pFace;

	// ▒▒ Body (Main box of tank) ▒▒
	float bodyHeight = fy * 0.6f;
	float topY = bodyHeight;
	float bottomY = -bodyHeight;

	// Front
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, bottomY, -fz));
	pFace->SetVertex(1, CVertex(+fx, bottomY, -fz));
	pFace->SetVertex(2, CVertex(+fx, topY, -fz));
	pFace->SetVertex(3, CVertex(-fx, topY, -fz));
	SetPolygon(i++, pFace);

	// Back
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, bottomY, +fz));
	pFace->SetVertex(1, CVertex(+fx, bottomY, +fz));
	pFace->SetVertex(2, CVertex(+fx, topY, +fz));
	pFace->SetVertex(3, CVertex(-fx, topY, +fz));
	SetPolygon(i++, pFace);

	// Left
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, bottomY, -fz));
	pFace->SetVertex(1, CVertex(-fx, bottomY, +fz));
	pFace->SetVertex(2, CVertex(-fx, topY, +fz));
	pFace->SetVertex(3, CVertex(-fx, topY, -fz));
	SetPolygon(i++, pFace);

	// Right
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(+fx, bottomY, -fz));
	pFace->SetVertex(1, CVertex(+fx, bottomY, +fz));
	pFace->SetVertex(2, CVertex(+fx, topY, +fz));
	pFace->SetVertex(3, CVertex(+fx, topY, -fz));
	SetPolygon(i++, pFace);

	// Top
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, topY, -fz));
	pFace->SetVertex(1, CVertex(+fx, topY, -fz));
	pFace->SetVertex(2, CVertex(+fx, topY, +fz));
	pFace->SetVertex(3, CVertex(-fx, topY, +fz));
	SetPolygon(i++, pFace);

	// Bottom
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, bottomY, -fz));
	pFace->SetVertex(1, CVertex(+fx, bottomY, -fz));
	pFace->SetVertex(2, CVertex(+fx, bottomY, +fz));
	pFace->SetVertex(3, CVertex(-fx, bottomY, +fz));
	SetPolygon(i++, pFace);

	// ▒▒ Turret ▒▒
	float turretWidth = fx * 0.6f;
	float turretHeight = fy * 0.3f;
	float turretTop = topY + turretHeight;

	// Front
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-turretWidth, topY, -fz * 0.5f));
	pFace->SetVertex(1, CVertex(+turretWidth, topY, -fz * 0.5f));
	pFace->SetVertex(2, CVertex(+turretWidth, turretTop, -fz * 0.5f));
	pFace->SetVertex(3, CVertex(-turretWidth, turretTop, -fz * 0.5f));
	SetPolygon(i++, pFace);

	// Other turret faces (Back, Sides, Top) 생략 가능, 필요 시 추가 가능

	// ▒▒ Cannon ▒▒
	float cannonLength = fz * 1.2f;
	float cannonWidth = fx * 0.1f;
	float cannonTopY = topY + turretHeight * 0.5f;

	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-cannonWidth, cannonTopY, -fz * 0.5f));
	pFace->SetVertex(1, CVertex(+cannonWidth, cannonTopY, -fz * 0.5f));
	pFace->SetVertex(2, CVertex(+cannonWidth, cannonTopY, -fz * 0.5f - cannonLength));
	pFace->SetVertex(3, CVertex(-cannonWidth, cannonTopY, -fz * 0.5f - cannonLength));
	SetPolygon(i++, pFace);

	// ▒▒ Wheels ▒▒ (좌우 3개씩 예시)
	float wheelRadius = fy * 0.2f;

	for (int j = 0; j < 3; ++j) {
        float offsetZ = -fz + (j + 1) * (fDepth / 4.0f);
		// 왼  
		pFace = new CPolygon(4);
		pFace->SetVertex(0, CVertex(-fx, -fy, offsetZ - wheelRadius));
		pFace->SetVertex(1, CVertex(-fx, -fy, offsetZ + wheelRadius));
		pFace->SetVertex(2, CVertex(-fx, -fy + wheelRadius * 2, offsetZ + wheelRadius));
		pFace->SetVertex(3, CVertex(-fx, -fy + wheelRadius * 2, offsetZ - wheelRadius));
		SetPolygon(i++, pFace);

		//오른 
		pFace = new CPolygon(4);
		pFace->SetVertex(0, CVertex(+fx, -fy, offsetZ - wheelRadius));
		pFace->SetVertex(1, CVertex(+fx, -fy, offsetZ + wheelRadius));
		pFace->SetVertex(2, CVertex(+fx, -fy + wheelRadius * 2, offsetZ + wheelRadius));
		pFace->SetVertex(3, CVertex(+fx, -fy + wheelRadius * 2, offsetZ - wheelRadius));
		SetPolygon(i++, pFace);
	}


	// ▒▒ Bounding Box ▒▒
	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fx, fy, fz), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}
//-----------------------------------------------------------------------------------------------------
//   카트
//-----------------------------------------------------------------------------------------------------
CCartMesh::CCartMesh(float fWidth, float fHeight, float fDepth) : CMesh(10) {
	float fx = fWidth * 0.5f, fy = fHeight * 0.5f, fz = fDepth * 0.5f;

	int i = 0;
	CPolygon* pFace;

	// ▒▒ Body (Main box of cart) ▒▒  
	float bodyHeight = fy * 0.6f;
	float topY = bodyHeight;
	float bottomY = -bodyHeight;

	// Front  
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, bottomY, -fz));
	pFace->SetVertex(1, CVertex(+fx, bottomY, -fz));
	pFace->SetVertex(2, CVertex(+fx, topY, -fz));
	pFace->SetVertex(3, CVertex(-fx, topY, -fz));
	SetPolygon(i++, pFace);

	// Back  
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, bottomY, +fz));
	pFace->SetVertex(1, CVertex(+fx, bottomY, +fz));
	pFace->SetVertex(2, CVertex(+fx, topY, +fz));
	pFace->SetVertex(3, CVertex(-fx, topY, +fz));
	SetPolygon(i++, pFace);

	// Left  
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, bottomY, -fz));
	pFace->SetVertex(1, CVertex(-fx, bottomY, +fz));
	pFace->SetVertex(2, CVertex(-fx, topY, +fz));
	pFace->SetVertex(3, CVertex(-fx, topY, -fz));
	SetPolygon(i++, pFace);

	// Right  
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(+fx, bottomY, -fz));
	pFace->SetVertex(1, CVertex(+fx, bottomY, +fz));
	pFace->SetVertex(2, CVertex(+fx, topY, +fz));
	pFace->SetVertex(3, CVertex(+fx, topY, -fz));
	SetPolygon(i++, pFace);

	// Top  
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, topY, -fz));
	pFace->SetVertex(1, CVertex(+fx, topY, -fz));
	pFace->SetVertex(2, CVertex(+fx, topY, +fz));
	pFace->SetVertex(3, CVertex(-fx, topY, +fz));
	SetPolygon(i++, pFace);

	// Bottom  
	pFace = new CPolygon(4);
	pFace->SetVertex(0, CVertex(-fx, bottomY, -fz));
	pFace->SetVertex(1, CVertex(+fx, bottomY, -fz));
	pFace->SetVertex(2, CVertex(+fx, bottomY, +fz));
	pFace->SetVertex(3, CVertex(-fx, bottomY, +fz));
	SetPolygon(i++, pFace);

	// ▒▒ Wheels ▒▒ (좌우 2개씩 예시)  
	float wheelRadius = fy * 0.2f;

	for (int j = 0; j < 2; ++j) {
		float offsetZ = -fz + (j + 1) * (fDepth / 3.0f);
		// 왼쪽  
		pFace = new CPolygon(4);
		pFace->SetVertex(0, CVertex(-fx, -fy, offsetZ - wheelRadius));
		pFace->SetVertex(1, CVertex(-fx, -fy, offsetZ + wheelRadius));
		pFace->SetVertex(2, CVertex(-fx, -fy + wheelRadius * 2, offsetZ + wheelRadius));
		pFace->SetVertex(3, CVertex(-fx, -fy + wheelRadius * 2, offsetZ - wheelRadius));
		SetPolygon(i++, pFace);

		// 오른쪽  
		pFace = new CPolygon(4);
		pFace->SetVertex(0, CVertex(+fx, -fy, offsetZ - wheelRadius));
		pFace->SetVertex(1, CVertex(+fx, -fy, offsetZ + wheelRadius));
		pFace->SetVertex(2, CVertex(+fx, -fy + wheelRadius * 2, offsetZ + wheelRadius));
		pFace->SetVertex(3, CVertex(+fx, -fy + wheelRadius * 2, offsetZ - wheelRadius));
		SetPolygon(i++, pFace);
	}

	// ▒▒ Bounding Box ▒▒  
	m_xmOOBB = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fx, fy, fz), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}


CAxisMesh::CAxisMesh(float fWidth, float fHeight, float fDepth) : CMesh(3)
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;
	float fHalfDepth = fDepth * 0.5f;

	CPolygon* pxAxis = new CPolygon(2);
	pxAxis->SetVertex(0, CVertex(-fHalfWidth, 0.0f, 0.0f));
	pxAxis->SetVertex(1, CVertex(+fHalfWidth, 0.0f, 0.0f));
	SetPolygon(0, pxAxis);

	CPolygon* pyAxis = new CPolygon(2);
	pyAxis->SetVertex(0, CVertex(0.0f, -fHalfWidth, 0.0f));
	pyAxis->SetVertex(1, CVertex(0.0f, +fHalfWidth, 0.0f));
	SetPolygon(1, pyAxis);

	CPolygon* pzAxis = new CPolygon(2);
	pzAxis->SetVertex(0, CVertex(0.0f, 0.0f, -fHalfWidth));
	pzAxis->SetVertex(1, CVertex(0.0f, 0.0f, +fHalfWidth));
	SetPolygon(2, pzAxis);
}

void CAxisMesh::Render(HDC hDCFrameBuffer)
{
	XMFLOAT3 f3PreviousProject = CGraphicsPipeline::Project(m_ppPolygons[0]->m_pVertices[0].m_xmf3Position);
	XMFLOAT3 f3CurrentProject = CGraphicsPipeline::Project(m_ppPolygons[0]->m_pVertices[1].m_xmf3Position);
	HPEN hPen = ::CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)::SelectObject(hDCFrameBuffer, hPen);
	::Draw2DLine(hDCFrameBuffer, f3PreviousProject, f3CurrentProject);
	::SelectObject(hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);

	f3PreviousProject = CGraphicsPipeline::Project(m_ppPolygons[1]->m_pVertices[0].m_xmf3Position);
	f3CurrentProject = CGraphicsPipeline::Project(m_ppPolygons[1]->m_pVertices[1].m_xmf3Position);
	hPen = ::CreatePen(PS_SOLID, 0, RGB(0, 0, 255));
	hOldPen = (HPEN)::SelectObject(hDCFrameBuffer, hPen);
	::Draw2DLine(hDCFrameBuffer, f3PreviousProject, f3CurrentProject);
	::SelectObject(hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);

	f3PreviousProject = CGraphicsPipeline::Project(m_ppPolygons[2]->m_pVertices[0].m_xmf3Position);
	f3CurrentProject = CGraphicsPipeline::Project(m_ppPolygons[2]->m_pVertices[1].m_xmf3Position);
	hPen = ::CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
	hOldPen = (HPEN)::SelectObject(hDCFrameBuffer, hPen);
	::Draw2DLine(hDCFrameBuffer, f3PreviousProject, f3CurrentProject);
	::SelectObject(hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);
}


//-----------------------------------------------------------------------------------------------------
//   롤러코스터
//-----------------------------------------------------------------------------------------------------

CRollerCoasterMesh_Up::CRollerCoasterMesh_Up(float fWidth, float fHeight, float fDepth) : CMesh(6)  
{	

   // 대각선으로 올라가는 사각형을 정의합니다.  
   CPolygon* pFace = new CPolygon(4);
   int i = 0;
   float 길이 = fWidth * 0.5f;
   float 넓이 = fDepth * 0.5f;
   // 사각형의 네 꼭짓점을 설정합니다.
   
   // 오르막
   pFace->SetVertex(0, CVertex(0.0, 0.0f, 0.0f));  // Bottom-left  
   pFace->SetVertex(1, CVertex(+길이, fHeight, 0.0f));  // Top-right  
   pFace->SetVertex(2, CVertex(+길이, fHeight, +fDepth * 0.5f));  // Top-left  
   pFace->SetVertex(3, CVertex(0.0f, 0.0f, +fDepth * 0.5f));  // Bottom-right    
   SetPolygon(i++, pFace);  

  
   pFace = new CPolygon(4);
   pFace->SetVertex(0, CVertex(길이, fHeight, +넓이));  // Bottom-left  
   pFace->SetVertex(1, CVertex(길이+넓이 , fHeight, +넓이));  // Top-right  
   pFace->SetVertex(2, CVertex(길이+넓이 , fHeight, -길이));  // Top-left  
   pFace->SetVertex(3, CVertex(길이, fHeight, -길이));  // Bottom-right  
   SetPolygon(i++, pFace);

   //내리막
   pFace = new CPolygon(4);  
   pFace->SetVertex(0, CVertex(0.0, 0.0f, -길이));  // Bottom-left  
   pFace->SetVertex(1, CVertex(+fWidth * 0.5f, fHeight, -길이 ));  // Top-right  
   pFace->SetVertex(2, CVertex(+fWidth * 0.5f, fHeight, -길이 +fDepth * 0.5f));  // Top-left  
   pFace->SetVertex(3, CVertex(0.0f, 0.0f, -길이 +fDepth * 0.5f));  // Bottom-right  
   SetPolygon(i++, pFace);


   //카메라쪽 평지
   pFace = new CPolygon(4);
   pFace->SetVertex(0, CVertex(0.0, 0.0f, -길이));  // Bottom-left  
   pFace->SetVertex(1, CVertex(-fWidth * 0.5f, 0.0f, -길이));  // Top-right  
   pFace->SetVertex(2, CVertex(-fWidth * 0.5f, 0.0f, -길이 + fDepth * 0.5f));  // Top-left  
   pFace->SetVertex(3, CVertex(0.0f, 0.0f, -길이 + fDepth * 0.5f));  // Bottom-right  
   SetPolygon(i++, pFace);

   pFace = new CPolygon(4);
   pFace->SetVertex(0, CVertex(-길이, 0.0f, -길이));  // Bottom-left  
   pFace->SetVertex(1, CVertex(-길이*2, fHeight, -길이));  // Top-right  
   pFace->SetVertex(2, CVertex(-길이*2 , fHeight, -길이 + fDepth * 0.5f));  // Top-left  
   pFace->SetVertex(3, CVertex(-길이, 0.0f, -길이 + fDepth * 0.5f));  // Bottom-right    
   SetPolygon(i++, pFace);


   //반대쪽 평지
   pFace = new CPolygon(4);
   pFace->SetVertex(0, CVertex(0.0, 0.0f, 0));  // Bottom-left  
   pFace->SetVertex(1, CVertex(-길이, 0.0f, 0));  // Top-right  
   pFace->SetVertex(2, CVertex(-길이, 0.0f, 넓이));  // Top-left  
   pFace->SetVertex(3, CVertex(0.0f, 0.0f, 넓이));  // Bottom-right  
   SetPolygon(i++, pFace);
}


