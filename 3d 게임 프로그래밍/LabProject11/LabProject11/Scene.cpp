#include "stdafx.h"
#include "Scene.h"
#include <d3d9.h>
#include <tchar.h>


CGameState::GameState CGameState::CurrentState = CGameState::TITLE; // 정적 멤버 초
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
                // y축 반전
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
                // y축 반전
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

    // 7x7 픽셀 맵
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

    int map게[7][7] = {
        {0,0,0,0,0,0,1},
        {0,0,0,0,1,0,1},
        {1,1,1,0,1,0,1},
        {0,0,1,1,1,0,1},
        {0,0,1,0,1,0,1},
        {0,0,0,0,1,0,1},
        {0,0,0,0,0,0,1}
    };
    int map임[7][7] = {
        {0,0,1,0,0,1,0},
        {0,1,0,1,0,1,0},
        {0,0,1,0,0,1,0},
        {0,0,0,0,0,1,0},
        {0,1,1,1,0,0,0},
        {0,1,0,1,0,0,0},
        {0,1,1,1,0,0,0}
    };
    int map프[letterH][letterW] = {
    {0,0,0,0,0,0,0},
    {0,1,1,1,1,1,0},
    {0,0,1,0,1,0,0},
    {0,0,1,0,1,0,0},
    {0,1,1,1,1,1,0},
    {0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1}
    };
    int map로[letterH][letterW] = {
    {0,1,1,1,1,1,0},
    {0,0,0,0,0,1,0},
    {0,1,1,1,1,1,0},
    {0,1,0,0,0,0,0},
    {0,1,1,1,1,1,0},
    {0,0,0,1,0,0,0},
    {1,1,1,1,1,1,1}
    };
    int map그[letterH][letterW] = {
    {0,1,1,1,1,1,0},
    {0,0,0,0,0,1,0},
    {0,0,0,0,0,1,0},
    {0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1}
    };
    int map래[letterH][letterW] = {
    {0,0,0,0,1,0,1},
    {1,1,1,0,1,0,1},
    {0,0,1,0,1,0,1},
    {1,1,1,0,1,1,1},
    {1,0,0,0,1,0,1},
    {1,1,1,0,1,0,1},
    {0,0,0,0,1,0,1}
    };
    int map밍[letterH][letterW] = {
    {0,1,1,1,0,1,0},
    {0,1,0,1,0,1,0},
    {0,1,1,1,0,1,0},
    {0,0,0,0,0,1,0},
    {0,0,1,0,0,1,0},
    {0,1,0,1,0,0,0},
    {0,0,1,0,0,0,0}
    };
    int map박[7][7] = {
    {1,0,1,0,1,0,0},
    {1,1,1,0,1,0,0},
    {1,1,1,0,1,1,1},
    {0,0,0,0,1,0,0},
    {1,1,1,0,1,0,0},
    {0,0,1,0,0,0,0},
    {0,0,1,0,0,0,0}
    }; 
    int map신[7][7] = {
    {0,0,1,0,0,0,1},
    {0,1,0,1,0,0,1},
    {1,0,0,0,1,0,1},
    {0,0,0,0,0,0,1},
    {0,1,0,0,0,0,0},
    {0,1,0,0,0,0,0},
    {0,1,1,1,0,0,0}
    };
    int map우[7][7] = {
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

    // 왼쪽으로 이동할 오프셋 값
    float leftOffset = -50.0f;

    // 객체 개수 계산
    int objCnt = 0;
    objCnt += countObjNum(map3);
    objCnt += countObjNum(mapD);
    objCnt += countObjNum(map게);
    objCnt += countObjNum(map임);
    objCnt += countObjNum(map프);
    objCnt += countObjNum(map로);
    objCnt += countObjNum(map그);
    objCnt += countObjNum(map래);
    objCnt += countObjNum(map밍);
    objCnt += countObjNum(map박);
    objCnt += countObjNum(map신);
    objCnt += countObjNum(map우);


    m_nStartObjects = objCnt;
    m_ppStartObjects = new GameObject * [m_nStartObjects];

    int objIdx = 0;
    // "3"
    makeTextByCube(pd3dDevice, pd3dCommandList, map3, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset,2.0f, objIdx);

    // "D"
    float letterSpacing = letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, mapD, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing,2.0f, objIdx);

    // "게"
    float letterSpacing2 = letterSpacing + letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map게, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing2,2.0f, objIdx);

    // "임"
    float letterSpacing3 = letterSpacing2 + letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map임, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3,2.0f, objIdx);
   
    // "프"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map프, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "로"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map로, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "그"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map그, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "래"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map래, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "밍"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map밍, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "박"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map박, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "신"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map신, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);
    // "우"
    letterSpacing3 += letterW * spacing + 3.0f;
    makeTextByCube(pd3dDevice, pd3dCommandList, map우, nullptr, &m_pStartSceneShader[0], m_ppStartObjects, leftOffset + letterSpacing3, 2.0f, objIdx);
    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);


    isExploding = false;
    explosionTime = 0.0f;
}
//void StartScene::AnimateObjects(float fTimeElapsed) {
//    // 전체 큐브 회전
//    for (int i = 0; i < m_nStartObjects; ++i) {
//        if (m_ppStartObjects[i]) {
//            m_ppStartObjects[i]->Rotate(0.0f, XM_PI * 0.2f * fTimeElapsed, 0.0f);
//        }
//    }
//
//    // 이름 큐브 폭발 애니메이션
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
//        // 폭발 후 일정 시간 뒤 메뉴 화면으로 전환
//        if (explosionTime > 1.0f) {
//            CGameState::ChangeGameState(CGameState::MENU);
//        }
//    }
//}
    // 공전 중심점
void StartScene::AnimateObjects(float fTimeElapsed) {
    XMFLOAT3 axis(0.0f, 1.0f, 0.0f); // y축 기준
    float orbitSpeed = 30.0f; // 1초에 30도씩 회전

    // 폭발 전에는 공전 애니메이션
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
        // 폭발 애니메이션
        explosionTime += fTimeElapsed;
        float explosionDuration = 1.2f;
        float explosionSpeed = 60.0f; // 큐브가 날아가는 속도
        float scatterRadius = 30.0f; // 큐브가 퍼지는 반경

        for (int i = 0; i < m_nStartObjects; ++i) {
            if (m_ppStartObjects[i]) {
                // 각 큐브마다 고유한 방향을 부여
                float theta = (float)(i) * 6.2831853f / (float)m_nStartObjects; // 0~2pi 분포
                float phi = (float)(i % 7) * 3.1415926f / 7.0f; // 0~pi 분포
                float dirX = cosf(theta) * sinf(phi);
                float dirY = cosf(phi);
                float dirZ = sinf(theta) * sinf(phi);
                // 폭발 진행에 따라 큐브 위치 이동
                float t = explosionTime / explosionDuration;
                if (t > 1.0f) t = 1.0f;
                float dist = scatterRadius * t + explosionSpeed * explosionTime;
                XMFLOAT3 origin = m_ppStartObjects[i]->GetPosition();
                // 최초 위치에서 방향으로 이동
                m_ppStartObjects[i]->SetPosition(
                    origin.x + dirX * dist,
                    origin.y + dirY * dist,
                    origin.z + dirZ * dist
                );
            }
        }
        // 폭발 후 일정 시간 뒤 메뉴 화면으로 전환
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

    // 7x7 픽셀 맵
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




    // 객체 개수 계산
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
    // 왼쪽으로 이동할 오프셋 값
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

	// 1. 셰이더 생성
	m_nShaders = 1;
	m_pShaders = new ObjectsShader[m_nShaders];
	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);


	// 2. 오브젝트 생성 및 셰이더 할당
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



