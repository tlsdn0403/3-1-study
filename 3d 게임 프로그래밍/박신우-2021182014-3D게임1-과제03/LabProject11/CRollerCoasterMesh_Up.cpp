#pragma once
#include "stdafx.h"
#include "Mesh.h"

CRollerCoasterMesh_Up::CRollerCoasterMesh_Up(float fWidth, float fHeight, float fDepth) : Mesh() {
    m_nPolygons = 12;
    m_ppPolygons = new CPolygon * [m_nPolygons];

    int i = 0;
    float 길이 = fWidth * 0.5f;
    float 높이 = fHeight * 0.5f;
    float 넓이 = fDepth * 0.5f;

    // 오르막
    CPolygon* pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(0.0f, 0.0f, 0.0f)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(+길이, fHeight, 0.0f)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(+길이, fHeight, +넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(0.0f, 0.0f, +넓이)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(길이, fHeight, +넓이)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(길이 + 넓이, fHeight, +넓이)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(길이 + 넓이, fHeight, -길이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(길이, fHeight, -길이)));
    m_ppPolygons[i++] = pFace;

    // 내리막
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(0.0f, 0.0f, -길이)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(+길이, fHeight, -길이)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(+길이, fHeight, -길이 + 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(0.0f, 0.0f, -길이 + 넓이)));
    m_ppPolygons[i++] = pFace;

    // 카메라쪽 평지
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(0.0f, 0.0f, -길이)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이, 0.0f, -길이)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이, 0.0f, -길이 + 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(0.0f, 0.0f, -길이 + 넓이)));
    m_ppPolygons[i++] = pFace;

    // 회전 내려감
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-길이, 0.0f, -길이)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이 * 2, -높이, -길이 * 2)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이 * 2, -높이, -길이 * 2 + 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-길이, 0.0f, -길이 + 넓이)));
    m_ppPolygons[i++] = pFace;

    // 살짝 직선
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-길이 * 3, -높이, -길이 * 2)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이 * 2, -높이, -길이 * 2)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이 * 2, -높이, -길이 * 2 + 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-길이 * 3, -높이, -길이 * 2 + 넓이)));
    m_ppPolygons[i++] = pFace;

    // 회전 올라감
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-길이 * 4, 0.0f, -길이)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이 * 3, -높이, -길이 * 2)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이 * 3, -높이, -길이 * 2 + 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-길이 * 4, 0.0f, -길이 + 넓이)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-길이 * 4, 0.0f, +넓이)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이 * 4 - 넓이, 0.0f, +넓이)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이 * 4 - 넓이, 0.0f, -길이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-길이 * 4, 0.0f, -길이)));
    m_ppPolygons[i++] = pFace;

    // 반대쪽 평지
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(0.0f, 0.0f, 0)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이, 0.0f, 0)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이, 0.0f, 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(0.0f, 0.0f, 넓이)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-길이, 0.0f, 0)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이 * 2, 0.0f, 0)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이 * 2, 0.0f, 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-길이, 0.0f, 넓이)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-길이 * 3, 0.0f, 0)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이 * 4, 0.0f, 0)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이 * 4, 0.0f, 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-길이 * 3, 0.0f, 넓이)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-길이 * 3, 0.0f, 0)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-길이 * 2, 0.0f, 0)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-길이 * 2, 0.0f, 넓이)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-길이 * 3, 0.0f, 넓이)));
    m_ppPolygons[i++] = pFace;
}