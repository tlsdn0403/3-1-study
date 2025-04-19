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
	virtual ~CMesh();

private:
	//인스턴싱(Instancing)을 위하여 메쉬는 게임 객체들에 공유될 수 있다. 
	//다음 참조값(Reference Count)은 메쉬가 공유되는 게임 객체의 개수를 나타낸다
	int							m_nReferences = 1;

public:
	//메쉬가 게임 객체에 공유될 때마다 참조값을 1씩 증가시킨다. 
	void AddRef() { m_nReferences++; }
	//메쉬를 공유하는 게임 객체가 소멸될 때마다 참조값을 1씩 감소시킨다. 
	//참조값이 0이되면 메쉬를 소멸시킨다.
	void Release() { m_nReferences--; if (m_nReferences <= 0) delete this; }

protected:
	//메쉬를 구성하는 다각형(면)들의 리스트이다. 
	int							m_nPolygons = 0;
	CPolygon					**m_ppPolygons = NULL;

public:
	//모든 바운딩 박스는 기본적으로 Mesh가 가지고 있다. 메쉬가 가지고 있는 바운딩 박스는 모델 좌표계이다.
	BoundingOrientedBox			m_xmOOBB = BoundingOrientedBox(); //기본 생성자 호출하여 초기화, OOBB바운딩 박스

public:
	void SetPolygon(int nIndex, CPolygon *pPolygon);

	//메쉬를 렌더링한다. 
	virtual void Render(HDC hDCFrameBuffer);

	BOOL RayIntersectionByTriangle(XMVECTOR& xmRayOrigin, XMVECTOR& xmRayDirection, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* pfNearHitDistance);
	int CheckRayIntersection(XMVECTOR& xmvPickRayOrigin, XMVECTOR& xmvPickRayDirection, float* pfNearHitDistance);
};

class CCubeMesh : public CMesh
{
public:
	CCubeMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f);
	virtual ~CCubeMesh() { }
};

class CWallMesh : public CMesh
{
public:
	CWallMesh(float fWidth = 4.0f, float fHeight = 4.0f, float fDepth = 4.0f, int nSubRects = 20);
	virtual ~CWallMesh() { }
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
class CRollerCoasterMesh : public CMesh {
public:
	CRollerCoasterMesh(float fWidth = 1.0f, float fHeight = 1.0f, float fDepth = 1.0f, int nSegments = 100);
	virtual ~CRollerCoasterMesh();
};