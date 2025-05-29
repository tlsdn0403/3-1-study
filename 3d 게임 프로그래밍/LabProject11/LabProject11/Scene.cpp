#include "stdafx.h"
#include "Scene.h"
#include "TextMesh.h" // 상단에 추가
#include <d3d9.h>
#include <tchar.h>

CGameState::GameState CGameState::CurrentState = CGameState::GAME; // 정적 멤버 초
void CGameState::ChangeGameState(GameState state)
{
	CurrentState = state;
}




void StartScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignature) {
    m_pd3dGraphicsRootSignature = rootSignature;
    m_nShaders = 1;
    m_pStartSceneShader = new ObjectsShader[m_nShaders];
    m_pStartSceneShader[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);

    // 7x7 픽셀 맵
    const int letterH = 7, letterW = 7;
    int map3[letterH][letterW] = {
        {1,1,1,1,1,1,1},
        {0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1},
        {0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1}
    };
    int mapD[letterH][letterW] = {
        {1,1,1,1,1,1,0},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,0,0,1},
        {1,1,1,1,1,1,0}
    };

    int map게[letterH][letterW] = {
    {0,0,0,0,0,0,1},
    {0,0,0,0,1,0,1},
    {0,0,1,0,1,0,1},
    {0,0,1,1,1,0,1},
    {1,1,1,0,1,0,1},
    {0,0,0,0,1,0,1},
    {0,0,0,0,0,0,1}
    };

    float cubeSize = 2.0f;
    float spacing = 2.0f;
    float zPos = 30.0f;
    float baseY = 2.0f;

    // 왼쪽으로 이동할 오프셋 값
    float leftOffset = -14.0f;

    // 객체 개수 계산
    int objCnt = 0;
    for (int y = 0; y < letterH; ++y)
        for (int x = 0; x < letterW; ++x)
            if (map3[y][x]) ++objCnt;
    for (int y = 0; y < letterH; ++y)
        for (int x = 0; x < letterW; ++x)
            if (mapD[y][x]) ++objCnt;
    for (int y = 0; y < letterH; ++y)
        for (int x = 0; x < letterW; ++x)
            if (map게[y][x]) ++objCnt;

    m_nStartObjects = objCnt;
    m_ppStartObjects = new GameObject * [m_nStartObjects];

    int objIdx = 0;
    // "3"
    for (int y = 0; y < letterH; ++y) {
        for (int x = 0; x < letterW; ++x) {
            if (map3[y][x]) {
                GameObject* obj = new GameObject();
                obj->SetMesh(new CubeMeshDiffused(pd3dDevice, pd3dCommandList, cubeSize, cubeSize, cubeSize));
                obj->SetShader(&m_pStartSceneShader[0]);
                obj->SetPosition(leftOffset + x * spacing, baseY + y * spacing, zPos);
                m_ppStartObjects[objIdx++] = obj;
            }
        }
    }
    // "D"
    float letterSpacing = letterW * spacing + 3.0f;
    for (int y = 0; y < letterH; ++y) {
        for (int x = 0; x < letterW; ++x) {
            if (mapD[y][x]) {
                GameObject* obj = new GameObject();
                obj->SetMesh(new CubeMeshDiffused(pd3dDevice, pd3dCommandList, cubeSize, cubeSize, cubeSize));
                obj->SetShader(&m_pStartSceneShader[0]);
                obj->SetPosition(leftOffset + letterSpacing + x * spacing, baseY + y * spacing, zPos);
                m_ppStartObjects[objIdx++] = obj;
            }
        }
    }
    // "게"
    float letterSpacing2 = letterSpacing + letterW * spacing + 3.0f;
    for (int y = 0; y < letterH; ++y) {
        for (int x = 0; x < letterW; ++x) {
            if (map게[y][x]) {
                GameObject* obj = new GameObject();
                obj->SetMesh(new CubeMeshDiffused(pd3dDevice, pd3dCommandList, cubeSize, cubeSize, cubeSize));
                obj->SetShader(&m_pStartSceneShader[0]);
                obj->SetPosition(leftOffset + letterSpacing2 + x * spacing, baseY + y * spacing, zPos);
                m_ppStartObjects[objIdx++] = obj;
            }
        }
    }

    m_pStartSceneShader->CreateShaderVariables(pd3dDevice, pd3dCommandList);

    isExploding = false;
    explosionTime = 0.0f;
}
void StartScene::AnimateObjects(float fTimeElapsed) {
    // 전체 큐브 회전
    for (int i = 0; i < m_nStartObjects; ++i) {
        if (m_ppStartObjects[i]) {
            m_ppStartObjects[i]->Rotate(0.0f, XM_PI * 0.2f * fTimeElapsed, 0.0f);
        }
    }

    // 이름 큐브 폭발 애니메이션
    if (isExploding) {
        explosionTime += fTimeElapsed;
        float explosionSpeed = 50.0f;
        for (int i = 0; i < 3; ++i) {
            int idx = 10 + i;
            if (m_ppStartObjects[idx]) {
                float dir = (float)(i - 1); // -1, 0, 1
                float offset = explosionSpeed * explosionTime * dir;
                m_ppStartObjects[idx]->SetPosition(280.0f + i * 2.0f + offset, 2.0f, 1.0f);
            }
        }
        // 폭발 후 일정 시간 뒤 메뉴 화면으로 전환
        if (explosionTime > 1.0f) {
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



