#include "stdafx.h"
#include "Scene.h"
#include "TextMesh.h" // 상단에 추가
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
                // y축 반전: y 좌표를 6-y로 변경
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

    float spacing = 1.0f;
    float zPos = 30.0f;
    float baseY = 2.0f;

    // 왼쪽으로 이동할 오프셋 값
    float leftOffset = -70.0f;

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
void StartScene::AnimateObjects(float fTimeElapsed) {
    // 공전 중심점
    float centerX = 0.0f;
    float centerY = 2.0f;
    float centerZ = 30.0f;

    float orbitRadius = 20.0f; // 공전 반지름
    float orbitSpeed = 0.5f;   // 공전 속도 (라디안/초)

    for (int i = 0; i < m_nStartObjects; ++i) {
        if (m_ppStartObjects[i]) {
            // 각 큐브마다 각도를 다르게 해서 분산
            float angle = orbitSpeed * fTimeElapsed + (XM_2PI * i / m_nStartObjects);
            float x = centerX + orbitRadius * cos(angle);
            float z = centerZ + orbitRadius * sin(angle);
            float y = centerY;


            // 큐브 자체도 회전
            m_ppStartObjects[i]->Rotate(0.0f, XM_PI * 0.2f * fTimeElapsed, 0.0f);
        }
    }

    // (폭발 애니메이션 등 기존 코드 유지)
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
    // 이름 큐브의 중심 좌표와 반지름 정의
    const int nameCenterX = 310;
    const int nameCenterY = 250;
    const int radius = 40;

    int dx = x - nameCenterX;
    int dy = y - nameCenterY;
    int distSq = dx * dx + dy * dy;
    if (!isExploding && distSq < radius * radius) {
        isExploding = true;
        explosionTime = 0.0f;
    }
}
StartScene::~StartScene() {
	if (m_pStartSceneShader) {
		m_pStartSceneShader->ReleaseObjects();
		delete m_pStartSceneShader;
	}
}

//void StartScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList , ID3D12RootSignature* rootSignatue) {
//	// StartScene만의 오브젝트/셰이더 생성
//	m_pd3dGraphicsRootSignature = rootSignatue;
//
//	m_pStartSceneShader = new ObjectsShader();
//	m_pStartSceneShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
//	m_pStartSceneShader->BuildObjects(pd3dDevice, pd3dCommandList);
//}






void StartScene::ReleaseUploadBuffers() {
	for (int i = 0; i < m_nShaders; i++)
		m_pStartSceneShader[i].ReleaseUploadBuffers();
}













MenuScene::MenuScene(ID2D1RenderTarget* pRT, IDWriteFactory* pDWriteFactory)
    : m_pRT(pRT), m_pTextFormat(nullptr), m_pBrush(nullptr)
{
    m_MenuItems = { L"Start", L"Level-1", L"Level-2", L"End" };

    // 텍스트 포맷 생성
    pDWriteFactory->CreateTextFormat(
        L"Segoe UI", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, 28.0f, L"ko-KR", &m_pTextFormat);

    // 브러시 생성
    m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pBrush);

    // 메뉴 사각형 계산
    float x = 400.0f, y = 150.0f, width = 200.0f, height = 40.0f, spacing = 50.0f;
    for (size_t i = 0; i < m_MenuItems.size(); ++i) {
        MenuItemRect rect = { x - width, y + i * spacing, x + width, y + height + i * spacing };
        m_MenuItemRects.push_back(rect);
    }
}

void MenuScene::Render() {
    for (size_t i = 0; i < m_MenuItems.size(); ++i) {
        D2D1_RECT_F rect = { m_MenuItemRects[i].left, m_MenuItemRects[i].top,
                             m_MenuItemRects[i].right, m_MenuItemRects[i].bottom };

        // 사각형 테두리 그리기
        m_pRT->DrawRectangle(rect, m_pBrush, 2.0f);

        // 텍스트 중앙 정렬 출력
        m_pRT->DrawTextW(
            m_MenuItems[i].c_str(), (UINT32)m_MenuItems[i].length(),
            m_pTextFormat, rect, m_pBrush,
            D2D1_DRAW_TEXT_OPTIONS_CLIP, DWRITE_MEASURING_MODE_NATURAL
        );
    }
}

void MenuScene::OnMouseClick(float x, float y) {
    for (size_t i = 0; i < m_MenuItemRects.size(); ++i) {
        const auto& r = m_MenuItemRects[i];
        if (r.left <= x && x <= r.right && r.top <= y && y <= r.bottom) {
            if (m_MenuItems[i] == L"End") {
                PostQuitMessage(0);
            }
            else if (m_MenuItems[i] == L"Start") {
                // 게임 시작 로직 호출
            }
            else if (m_MenuItems[i] == L"Level-1") {
                // Level-1 시작
            }
            else if (m_MenuItems[i] == L"Level-2") {
                // Level-2 시작
            }
        }
    }
}




//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
Scene::Scene() {
	//[Lab05]
	//m_pd3dPipelineState = NULL;
	//m_pd3dGraphicsRootSignature = NULL;
}


Scene::~Scene() {

}

//[Lab06]
//void Scene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList , ID3D12RootSignature *rootSignatue) {
//	
//	// 파이프라인에서 만든 루트시그니처를 사용
//	m_pd3dGraphicsRootSignature = rootSignatue;
//
//	CubeMeshDiffused *pCubeMesh = new CubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);
//
//	// 1종류의 객체를 가리키는 1개의 쉐이더
//	m_nShaders = 1;
//	// 1개의 쉐이더 주소 저장 메모리 할당 - m_pShaders는 m_nShaders만큼의 객체를 주소 배열로 관리
//	m_pShaders = new ObjectsShader[m_nShaders];
//
//	// Shader 생성
//	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
//	// 생성된 Shader의 객체 생성
//	m_pShaders[0].BuildObjects(pd3dDevice, pd3dCommandList);
//
//
//	//GameObject* object;
//	//Mesh* mesh = new Mesh();
//	//Shader* shader = new ObjectsShader();
//	///*shader->CreateShader();*/
//
//
//	//object->SetMesh(mesh);
//	//object->SetShader(shader);
//
//
//}
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
	m_nObjects = nObjects;
	m_ppObjects = new GameObject * [nObjects];

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
//void Scene::ReleaseObjects() {
//	
//	for (int i = 0; i < m_nShaders; i++) {
//		m_pShaders[i].ReleaseShaderVariables();
//		m_pShaders[i].ReleaseObjects();
//	}
//	
//	if (m_pShaders)
//		delete[] m_pShaders;
//}


bool Scene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	return false;
}

bool Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) {
	return false;
}

bool Scene::ProcessInput(UCHAR *pKeysBuffer) {
	return false;
}

//void Scene::AnimateObjects(float fTimeElapsed) {
//	for (int i = 0; i < m_nShaders; i++) 
//		m_pShaders[i].AnimateObjects(fTimeElapsed);
//}
//
//void Scene::Render(ID3D12GraphicsCommandList *pd3dCommandList, Camera *pCamera){
//
//	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
//
//	// 그래픽 루트 시그너쳐를 파이프라인에 연결
//	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
//
//	if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);
//
//	// 씬을 구성하는 쉐이더(쉐이더에 포함된 객체)들을 렌더링
//	for (int i = 0; i < m_nShaders; i++) 
//		m_pShaders[i].Render(pd3dCommandList, pCamera); 
//
//	/*for (int i = 0; i < m_nGameObjects; i++)
//	{
//		m_nGameObjects[i].Render();
//	}*/
//}

void Scene::ReleaseUploadBuffers() {
	for (int i = 0; i < m_nShaders; i++)
		m_pShaders[i].ReleaseUploadBuffers();
}

ID3D12RootSignature *Scene::GetGraphicsRootSignature() {
	return(m_pd3dGraphicsRootSignature);
}



