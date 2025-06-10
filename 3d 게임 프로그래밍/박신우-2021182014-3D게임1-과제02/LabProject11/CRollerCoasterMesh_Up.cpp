#pragma once
#include "stdafx.h"
#include "Mesh.h"

CRollerCoasterMesh_Up::CRollerCoasterMesh_Up(float fWidth, float fHeight, float fDepth) : Mesh() {
    m_nPolygons = 12;
    m_ppPolygons = new CPolygon * [m_nPolygons];

    int i = 0;
    float ���� = fWidth * 0.5f;
    float ���� = fHeight * 0.5f;
    float ���� = fDepth * 0.5f;

    // ������
    CPolygon* pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(0.0f, 0.0f, 0.0f)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(+����, fHeight, 0.0f)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(+����, fHeight, +����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(0.0f, 0.0f, +����)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(����, fHeight, +����)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(���� + ����, fHeight, +����)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(���� + ����, fHeight, -����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(����, fHeight, -����)));
    m_ppPolygons[i++] = pFace;

    // ������
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(0.0f, 0.0f, -����)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(+����, fHeight, -����)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(+����, fHeight, -���� + ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(0.0f, 0.0f, -���� + ����)));
    m_ppPolygons[i++] = pFace;

    // ī�޶��� ����
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(0.0f, 0.0f, -����)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-����, 0.0f, -����)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-����, 0.0f, -���� + ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(0.0f, 0.0f, -���� + ����)));
    m_ppPolygons[i++] = pFace;

    // ȸ�� ������
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-����, 0.0f, -����)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-���� * 2, -����, -���� * 2)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-���� * 2, -����, -���� * 2 + ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-����, 0.0f, -���� + ����)));
    m_ppPolygons[i++] = pFace;

    // ��¦ ����
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-���� * 3, -����, -���� * 2)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-���� * 2, -����, -���� * 2)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-���� * 2, -����, -���� * 2 + ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-���� * 3, -����, -���� * 2 + ����)));
    m_ppPolygons[i++] = pFace;

    // ȸ�� �ö�
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-���� * 4, 0.0f, -����)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-���� * 3, -����, -���� * 2)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-���� * 3, -����, -���� * 2 + ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-���� * 4, 0.0f, -���� + ����)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-���� * 4, 0.0f, +����)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-���� * 4 - ����, 0.0f, +����)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-���� * 4 - ����, 0.0f, -����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-���� * 4, 0.0f, -����)));
    m_ppPolygons[i++] = pFace;

    // �ݴ��� ����
    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(0.0f, 0.0f, 0)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-����, 0.0f, 0)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-����, 0.0f, ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(0.0f, 0.0f, ����)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-����, 0.0f, 0)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-���� * 2, 0.0f, 0)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-���� * 2, 0.0f, ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-����, 0.0f, ����)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-���� * 3, 0.0f, 0)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-���� * 4, 0.0f, 0)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-���� * 4, 0.0f, ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-���� * 3, 0.0f, ����)));
    m_ppPolygons[i++] = pFace;

    pFace = new CPolygon(4);
    pFace->SetVertex(0, Vertex(XMFLOAT3(-���� * 3, 0.0f, 0)));
    pFace->SetVertex(1, Vertex(XMFLOAT3(-���� * 2, 0.0f, 0)));
    pFace->SetVertex(2, Vertex(XMFLOAT3(-���� * 2, 0.0f, ����)));
    pFace->SetVertex(3, Vertex(XMFLOAT3(-���� * 3, 0.0f, ����)));
    m_ppPolygons[i++] = pFace;
}