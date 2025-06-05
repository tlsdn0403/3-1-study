#include "stdafx.h"
#include "Scene.h"
#include <d3d9.h>
#include <tchar.h>


CGameState::GameState CGameState::CurrentState = CGameState::TITLE; // ���� ��� ��
void CGameState::ChangeGameState(GameState state)
{
	CurrentState = state;
}

void makeTextByCube(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, int map[7][7], CubeMeshDiffused* pMesh,
    ObjectsShader* pShader,
    GameObject** ppObjects,
    float leftOffset,
    float baseY,
    int& objIdx)
{
    float cubeSize = 1.0f;
    float spacing = 1.0f;
    float zPos = 60.0f;

    for (int y = 0; y < 7; ++y) {
        for (int x = 0; x < 7; ++x) {
            if (map[y][x]) {
                GameObject* obj = new GameObject();
                obj->SetMesh(pMesh ? pMesh : new CubeMeshDiffused(pd3dDevice, pd3dCommandList, spacing, spacing, spacing));
                obj->SetShader(pShader);
                // y�� ����
                obj->SetPosition(leftOffset + x * spacing, baseY + (6 - y) * spacing, zPos);
                ppObjects[objIdx++] = obj;
            }
        }
    }
}

void makeTextByCube_1(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, int map[7][7], CubeMeshDiffused* pMesh,
    ObjectsShader* pShader,
    GameObject** ppObjects,
    float leftOffset,
    float baseY,
    int& objIdx)
{
    float cubeSize = 1.0f;
    float spacing = 0.5f;
    float zPos = 60.0f;

    for (int y = 0; y < 7; ++y) {
        for (int x = 0; x < 7; ++x) {
            if (map[y][x]) {
                GameObject* obj = new GameObject();
                obj->SetMesh(pMesh ? pMesh : new CubeMeshDiffused(pd3dDevice, pd3dCommandList, spacing, spacing, spacing));
                obj->SetShader(pShader);
                // y�� ����
                obj->SetPosition(leftOffset + x * spacing, baseY + (6 - y) * spacing, zPos);
                ppObjects[objIdx++] = obj;
            }
        }
    }
}

int countObjNum( int map[7][7]) {
    int objCnt = 0;
    for (int y = 0; y < 7; ++y)
        for (int x = 0; x < 7; ++x)
            if (map[y][x]) ++objCnt;

    return objCnt;
}

void StartScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignature) {
    m_pd3dGraphicsRootSignature = rootSignature;
    m_nShaders = 1;
    m_pStartSceneShader = new ObjectsShader[m_nShaders];
    m_pStartSceneShader[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);

    // 7x7 �ȼ� ��
    const int letterH = 7, letterW = 7;
    int map3[7][7] = {
        {1,1,1,1,1,1,1},
        {0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1},
        {0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1}
    };
    int mapD[7][7] = {
        {1,1,1,1,1,1,0},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,1,1,1,1,1,0}
    };

    int map��[7][7] = {
        {0,0,0,0,0,0,1},
        {0,0,0,0,1,0,1},
        {1,1,1,0,1,0,1},
        {0,0,1,1,1,0,1},
        {0,0,1,0,1,0,1},
        {0,0,0,0,1,0,1},
        {0,0,0,0,0,0,1}
    };
    int map��[7][7] = {
        {0,0,1,0,0,1,0},
        {0,1,0,1,0,1,0},
        {0,0,1,0,0,1,0},
        {0,0,0,0,0,1,0},
        {0,1,1,1,0,0,0},
        {0,1,0,1,0,0,0},
        {0,1,1,1,0,0,0}
    };
    int map��[letterH][letterW] = {
    {0,0,0,0,0,0,0},
    {0,1,1,1,1,1,0},
    {0,0,1,0,1,0,0},
    {0,0,1,0,1,0,0},
    {0,1,1,1,1,1,0},
    {0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1}
    };
    int map��[letterH][letterW] = {
    {0,1,1,1,1,1,0},
    {0,0,0,0,0,1,0},
    {0,1,1,1,1,1,0},
    {0,1,0,0,0,0,0},
    {0,1,1,1,1,1,0},
    {0,0,0,1,0,0,0},
    {1,1,1,1,1,1,1}
    };
    int map��[letterH][letterW] = {
    {0,1,1,1,1,1,0},
    {0,0,0,0,0,1,0},
    {0,0,0,0,0,1,0},
    {0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1}
    };
    int map��[letterH][letterW] = {
    {0,0,0,0,1,0,1},
    {1,1,1,0,1,0,1},
    {0,0,1,0,1,0,1},
    {1,1,1,0,1,1,1},
    {1,0,0,0,1,0,1},
    {1,1,1,0,1,0,1},
    {0,0,0,0,1,0,1}
    };
    int map��[letterH][letterW] = {
    {0,1,1,1,0,1,0},
    {0,1,0,1,0,1,0},
    {0,1,1,1,0,1,0},
    {0,0,0,0,0,1,0},
    {0,0,1,0,0,1,0},
    {0,1,0,1,0,0,0},
    {0,0,1,0,0,0,0}
    };
    int map��[7][7] = {
    {1,0,1,0,1,0,0},
    {1,1,1,0,1,0,0},
    {1,1,1,0,1,1,1},
    {0,0,0,0,1,0,0},
    {1,1,1,0,1,0,0},
    {0,0,1,0,0,0,0},
    {0,0,1,0,0,0,0}
    }; 
    int map��[7][7] = {
    {0,0,1,0,0,0,1},
    {0,1,0,1,0,0,1},
    {1,0,0,0,1,0,1},
    {0,0,0,0,0,0,1},
    {0,1,0,0,0,0,0},
    {0,1,0,0,0,0,0},
    {0,1,1,1,0,0,0}
    };
    int map��[7][7] = {
    {0,0,0,1,0,0,0},
    {0,0,1,0,1,0,0},
    {0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0},
    {0,1,1,1,1,1,0},
    {0,0,0,1,0,0,0},
    {0,0,0,1,0,0,0}
    };
    float spacing = 1.0f;
    float zPos = 100.0f;
    float baseY = 2.0f;

    // �������� �̵��� ������ ��
    float leftOffset = -50.0f;

    // ��ü ���� ���
    int objCnt = 0;
    objCnt += countObjNum(map3);
    objCnt += countObjNum(mapD);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);
    objCnt += countObjNum(map��);


    m_nStartObjects = objCnt;
    m_ppStartObjects = new GameObject * [m_nStartObjects];

    int objIdx = 0;
    // "3"
    makeTextByCube(pd3dDevice, pd3dCommandList, map3, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset,2.0f, objIdx);

    // "D"
    float letterSpacing = letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, mapD, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing,2.0f, objIdx);

    // "��"
    float letterSpacing2 = letterSpacing + letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing2,2.0f, objIdx);

    // "��"
    float letterSpacing3 = letterSpacing2 + letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3,2.0f, objIdx);
   
    // "��"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "��"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "��"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "��"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "��"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "��"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "��"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "��"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map��, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);


    isExploding = false;
    explosionTime = 0.0f;
}
//void StartScene::AnimateObjects(float fTimeElapsed) {
//    // ��ü ť�� ȸ��
//    for (int i = 0; i < m_nStartObjects; ++i) {
//        if (m_ppStartObjects[i]) {
//            m_ppStartObjects[i]->Rotate(0.0f, XM_PI * 0.2f * fTimeElapsed, 0.0f);
//        }
//    }
//
//    // �̸� ť�� ���� �ִϸ��̼�
//    if (isExploding) {
//        explosionTime += fTimeElapsed;
//        float explosionSpeed = 50.0f;
//        for (int i = 0; i < 3; ++i) {
//            int idx = 10 + i;
//            if (m_ppStartObjects[idx]) {
//                float dir = (float)(i - 1); // -1, 0, 1
//                float offset = explosionSpeed * explosionTime * dir;
//                m_ppStartObjects[idx]->SetPosition(280.0f + i * 2.0f + offset, 2.0f, 1.0f);
//            }
//        }
//        // ���� �� ���� �ð� �� �޴� ȭ������ ��ȯ
//        if (explosionTime > 1.0f) {
//            CGameState::ChangeGameState(CGameState::MENU);
//        }
//    }
//}
    // ���� �߽���
void StartScene::AnimateObjects(float fTimeElapsed) {
    XMFLOAT3 axis(0.0f, 1.0f, 0.0f); // y�� ����
    float orbitSpeed = 30.0f; // 1�ʿ� 30���� ȸ��

    // ���� ������ ���� �ִϸ��̼�
    if (!isExploding) {
        for (int i = 0; i < m_nStartObjects; ++i) {
            if (m_ppStartObjects[i]) {
                XMFLOAT3 center(0.0f, m_ppStartObjects[i]->getY(), 100.0f);
                float angle = orbitSpeed * fTimeElapsed;
                m_ppStartObjects[i]->Revolve(center, axis, angle);
            }
        }
    }
    else {
        // ���� �ִϸ��̼�
        explosionTime += fTimeElapsed;
        float explosionDuration = 1.2f;
        float explosionSpeed = 60.0f; // ť�갡 ���ư��� �ӵ�
        float scatterRadius = 30.0f; // ť�갡 ������ �ݰ�

        for (int i = 0; i < m_nStartObjects; ++i) {
            if (m_ppStartObjects[i]) {
                // �� ť�긶�� ������ ������ �ο�
                float theta = (float)(i) * 6.2831853f / (float)m_nStartObjects; // 0~2pi ����
                float phi = (float)(i % 7) * 3.1415926f / 7.0f; // 0~pi ����
                float dirX = cosf(theta) * sinf(phi);
                float dirY = cosf(phi);
                float dirZ = sinf(theta) * sinf(phi);
                // ���� ���࿡ ���� ť�� ��ġ �̵�
                float t = explosionTime / explosionDuration;
                if (t > 1.0f) t = 1.0f;
                float dist = scatterRadius * t + explosionSpeed * explosionTime;
                XMFLOAT3 origin = m_ppStartObjects[i]->GetPosition();
                // ���� ��ġ���� �������� �̵�
                m_ppStartObjects[i]->SetPosition(
                    origin.x + dirX * dist,
                    origin.y + dirY * dist,
                    origin.z + dirZ * dist
                );
            }
        }
        // ���� �� ���� �ð� �� �޴� ȭ������ ��ȯ
        if (explosionTime > explosionDuration) {
            CGameState::ChangeGameState(CGameState::MENU);
        }
    }


}



void StartScene::Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera) {
    pCamera->SetViewportsAndScissorRects(pd3dCommandList);
    pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
    if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);


    for (int i = 0; i < m_nStartObjects; i++) {
        if (m_ppStartObjects[i]) m_ppStartObjects[i]->Render(pd3dCommandList, pCamera);
    }
}

void StartScene::OnMouseClick(int x, int y) {
    isExploding = true; 
}
void StartScene::ReleaseObjects() {
    if (m_ppStartObjects) {
        for (int i = 0; i < m_nStartObjects; i++) {
            if (m_ppStartObjects[i]) delete m_ppStartObjects[i];
        }
        delete[] m_ppStartObjects;
        m_ppStartObjects = nullptr;
    }
    if (m_pStartSceneShader) {
        for (int i = 0; i < m_nShaders; i++) {
            m_pStartSceneShader[i].ReleaseShaderVariables();
        }
        delete[] m_pStartSceneShader;
        m_pStartSceneShader = nullptr;
    }
}
StartScene::~StartScene() {
	if (m_pStartSceneShader) {
		m_pStartSceneShader->ReleaseObjects();
		delete m_pStartSceneShader;
	}
}





void StartScene::ReleaseUploadBuffers() {
	for (int i = 0; i < m_nShaders; i++)
		m_pStartSceneShader[i].ReleaseUploadBuffers();
}




//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------



void MenuScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignature) {
    m_pd3dGraphicsRootSignature = rootSignature;
    m_nShaders = 1;
    m_pMenuSceneShader = new ObjectsShader[m_nShaders];
    m_pMenuSceneShader[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);

    // 7x7 �ȼ� ��
    const int letterH = 7, letterW = 7;
    int mapT[7][7] = {
    { 1,1,1,1,1,1,1 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 }
    };
    int mapt[7][7] = {
    { 0,0,0,0,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,1,1,1,1,1,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,1,0,0 }
    };
    int mapu[7][7] = {
     { 0,0,0,0,0,0,0 },
     { 0,0,0,0,0,0,0 },
     { 0,1,0,0,0,1,0 },
     { 0,1,0,0,0,1,0 },
     { 0,1,0,0,0,1,0 },
     { 0,0,1,0,1,0,0 },
     { 0,0,0,1,0,0,0 }
    };
    int mapo[7][7] = {
    { 0,0,0,0,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,1,0,1,0,0 },
    { 0,1,0,0,0,1,0 },
    { 0,0,1,0,1,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0 }
    };
    int mapr[7][7] = {
    { 0,1,0,0,0,0,0 },
    { 0,1,0,1,1,1,1 },
    { 0,1,1,0,0,0,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,0,0,0,0,0 }
    };
    int mapi[7][7] = {
    { 0,0,0,1,0,0,0 },
    { 0,0,0,0,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 }
    };
    int mapa[7][7] = {
    { 0,0,1,1,0,0,0 },
    { 0,1,0,0,1,0,0 },
    { 0,0,0,1,0,1,0 },
    { 0,0,1,0,1,1,0 },
    { 0,1,0,0,0,1,0 },
    { 0,0,1,1,1,1,1 },
    { 0,0,0,0,0,0,0 }
    };
    int mapl[7][7] = {
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 }
    };
    int mapL[7][7] = {
    { 1,0,0,0,0,0,0 },
    { 1,0,0,0,0,0,0 },
    { 1,0,0,0,0,0,0 },
    { 1,0,0,0,0,0,0 },
    { 1,0,0,0,0,0,0 },
    { 1,0,0,0,0,0,0 },
    { 1,1,1,1,1,1,1 }
    };
    int mape[7][7] = {
    { 0,0,1,1,1,0,0 },
    { 0,1,0,0,0,1,0 },
    { 1,0,0,0,0,0,1 },
    { 1,1,1,1,1,1,0 },
    { 1,0,0,0,0,0,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,1,1,1,1,0 }
    };
    int map1[7][7] = {
    { 0,0,0,1,0,0,0 },
    { 0,0,1,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,1,1,1,1,1,0 }
    };
    int map2[7][7] = {
    { 0,0,1,1,1,0,0 },
    { 0,1,0,0,0,1,0 },
    { 0,0,0,0,1,0,0 },
    { 0,0,0,1,0,0,0 },
    { 0,0,1,0,0,0,0 },
    { 0,1,0,0,0,0,0 },
    { 1,1,1,1,1,1,1 }
    };
    int maps[7][7] = {
    { 0,0,1,1,1,1,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,0,0,0,0,0 },
    { 0,0,1,1,1,0,0 },
    { 0,0,0,0,0,1,0 },
    { 0,0,0,0,0,1,0 },
    { 0,1,1,1,1,0,0 }
    };
    int mapE[7][7] = {
    { 0,1,1,1,1,1,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,1,1,1,1,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,0,0,0,0,0 },
    { 0,1,1,1,1,1,0 }
    };
    int mapn[7][7] = {
    { 0,0,0,0,0,0,0 },
    { 0,1,1,1,1,1,0 },
    { 1,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1 },
    { 1,0,0,0,0,0,1 }
    };
    int mapd[7][7] = {
    { 0,0,0,0,0,1,0 },
    { 0,0,0,0,0,1,0 },
    { 0,0,0,1,1,1,0 },
    { 0,0,1,0,0,1,0 },
    { 0,1,0,0,0,1,0 },
    { 0,0,1,0,0,1,0 },
    { 0,0,0,1,1,1,0 }
    };
    float spacing = 0.5f;
    float zPos = 100.0f;
    float baseY = 2.0f;




    // ��ü ���� ���
    int objCnt = 0;
    objCnt += countObjNum(mapT);
    objCnt += countObjNum(mapu);
    objCnt += countObjNum(mapt);
    objCnt += countObjNum(mapo);
    objCnt += countObjNum(mapr);
    objCnt += countObjNum(mapi);
    objCnt += countObjNum(mapa);
    objCnt += countObjNum(mapl);


    objCnt += countObjNum(mapL);
    objCnt += countObjNum(mape);
    objCnt += countObjNum(mapu);
    objCnt += countObjNum(mape);
    objCnt += countObjNum(mapl);
    objCnt += countObjNum(map1);


    objCnt += countObjNum(mapL);
    objCnt += countObjNum(mape);
    objCnt += countObjNum(mapu);
    objCnt += countObjNum(mape);
    objCnt += countObjNum(mapl);
    objCnt += countObjNum(map2);


    objCnt += countObjNum(maps);
    objCnt += countObjNum(mapt);
    objCnt += countObjNum(mapa);
    objCnt += countObjNum(mapr);
    objCnt += countObjNum(mapt);


    objCnt += countObjNum(mapE);
    objCnt += countObjNum(mapn);
    objCnt += countObjNum(mapd);


    m_nMenuObjects = objCnt;
    m_ppMenuObjects = new GameObject * [m_nMenuObjects];

    int objIdx = 0;
    float Yspace = 20.0f;
    // �������� �̵��� ������ ��
    float leftOffset = -18.0f;


    // "T"
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapT, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "u"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapu, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "t"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapt, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "o"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapo, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "r"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapr, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "i"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapi, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "a"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapa, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "l"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapl, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);

    
    Yspace = 10.0f;
    leftOffset = -15.0f;
    // "L"
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapL, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "e"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mape, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "v"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapu, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "e"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mape, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "l"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapl, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "1"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, map1, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);

    Yspace = 0.0f;
    leftOffset = -15.0f;
    // "L"
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapL, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "e"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mape, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "v"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapu, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "e"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mape, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "l"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapl, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "2"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, map2, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);

    Yspace = -10.0f;
    leftOffset = -12.5f;
    // "S"
    makeTextByCube_1(pd3dDevice, pd3dCommandList, maps, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "t"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapt, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "a"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapa, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "r"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapr, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "t"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapt, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);


    Yspace = -20.0f;
    leftOffset = -9.0f;
    // "E"
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapE, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "n"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapn, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);
    // "d"
    leftOffset += letterW * spacing + 1.0f;
    makeTextByCube_1(pd3dDevice, pd3dCommandList, mapd, nullptr, &m_pMenuSceneShader[0], m_ppMenuObjects, leftOffset, Yspace, objIdx);


}
void MenuScene::Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera) {
    pCamera->SetViewportsAndScissorRects(pd3dCommandList);
    pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
    if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);


    for (int i = 0; i < m_nMenuObjects; i++) {
        if (m_ppMenuObjects[i]) m_ppMenuObjects[i]->Render(pd3dCommandList, pCamera);
    }
}

void MenuScene::OnMouseClick(int x, int y) {

    float level1_left = 300;
    float level1_right = 900;
    float level1_top = 200;
    float level1_bottom = 400;


    if (x >= level1_left && x <= level1_right &&
        y >= level1_top && y <= level1_bottom) {
        CGameState::ChangeGameState(CGameState::GAME_1);
    }
}
void MenuScene::ReleaseObjects() {
    if (m_ppMenuObjects) {
        for (int i = 0; i < m_nMenuObjects; i++) {
            if (m_ppMenuObjects[i]) delete m_ppMenuObjects[i];
        }
        delete[] m_ppMenuObjects;
        m_ppMenuObjects = nullptr;
    }
    if (m_pMenuSceneShader) {
        for (int i = 0; i < m_nShaders; i++) {
            m_pMenuSceneShader[i].ReleaseShaderVariables();
        }
        delete[] m_pMenuSceneShader;
        m_pMenuSceneShader = nullptr;
    }
}
void MenuScene::ReleaseUploadBuffers() {
    for (int i = 0; i < m_nShaders; i++)
        m_pMenuSceneShader[i].ReleaseUploadBuffers();
}
MenuScene::~MenuScene() {
    if (m_pMenuSceneShader) {
        m_pMenuSceneShader->ReleaseObjects();
        delete m_pMenuSceneShader;
    }
}




//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
Scene::Scene() {
}


Scene::~Scene() {

}

void Scene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignature) {
	m_pd3dGraphicsRootSignature = rootSignature;

	// 1. ���̴� ����
	m_nShaders = 1;
	m_pShaders = new ObjectsShader[m_nShaders];
	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);


	// 2. ������Ʈ ���� �� ���̴� �Ҵ�
	int xObjects = 1, yObjects = 1, zObjects = 1;
	float rectSize = 12.0f;
	float fxPitch = rectSize * 2.5f;
	float fyPitch = rectSize * 2.5f;
	float fzPitch = rectSize * 2.5f;
	int nObjects = (xObjects * 2 + 1) * (yObjects * 2 + 1) * (zObjects * 2 + 1);
	m_nObjects = nObjects + 1 ;
	m_ppObjects = new GameObject * [m_nObjects];

    CRollerCoasterMesh_Up* pRailMesh = new CRollerCoasterMesh_Up(pd3dDevice, pd3dCommandList,20.0f, 10.0f, 6.0f);

	CubeMeshDiffused* pCubeMesh = new CubeMeshDiffused(pd3dDevice, pd3dCommandList, rectSize, rectSize, rectSize);

	int i = 0;
	for (int x = -xObjects; x <= xObjects; x++) {
		for (int y = -yObjects; y <= yObjects; y++) {
			for (int z = -zObjects; z <= zObjects; z++) {
				GameObject* obj = new GameObject();
				obj->SetMesh(pCubeMesh);
				obj->SetShader(&m_pShaders[0]);
				obj->SetPosition(fxPitch * x, fyPitch * y, fzPitch * z);
				m_ppObjects[i++] = obj;
			}
		}
	}
    GameObject* obj = new GameObject();

    obj->SetMesh(pRailMesh);
    obj->SetShader(&m_pShaders[0]);
    obj->SetPosition(0,0,0);
    m_ppObjects[i++] = obj;
}
void Scene::ReleaseObjects() {
	if (m_ppObjects) {
		for (int i = 0; i < m_nObjects; i++) {
			if (m_ppObjects[i]) delete m_ppObjects[i];
		}
		delete[] m_ppObjects;
		m_ppObjects = nullptr;
	}
	if (m_pShaders) {
		for (int i = 0; i < m_nShaders; i++) {
			m_pShaders[i].ReleaseShaderVariables();
		}
		delete[] m_pShaders;
		m_pShaders = nullptr;
	}
}
void Scene::AnimateObjects(float fTimeElapsed) {
	for (int i = 0; i < m_nObjects; i++) {
		if (m_ppObjects[i]) m_ppObjects[i]->Animate(fTimeElapsed);
	}
}
void Scene::Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera) {
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
	if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);

	for (int i = 0; i < m_nObjects; i++) {
		if (m_ppObjects[i]) m_ppObjects[i]->Render(pd3dCommandList, pCamera);
	}
}


bool Scene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	return false;
}

bool Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	return false;
}

bool Scene::ProcessInput(UCHAR *pKeysBuffer) {
	return false;
}


void Scene::ReleaseUploadBuffers() {
	for (int i = 0; i < m_nShaders; i++)
		m_pShaders[i].ReleaseUploadBuffers();
}

ID3D12RootSignature *Scene::GetGraphicsRootSignature() {
	return(m_pd3dGraphicsRootSignature);
}



