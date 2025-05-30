#include "stdafx.h"
#include "Scene.h"
#include "TextMesh.h" // ��ܿ� �߰�
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
                // y�� ����: y ��ǥ�� 6-y�� ����
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

    float spacing = 1.0f;
    float zPos = 30.0f;
    float baseY = 2.0f;

    // �������� �̵��� ������ ��
    float leftOffset = -70.0f;

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
void StartScene::AnimateObjects(float fTimeElapsed) {
    // ���� �߽���
    float centerX = 0.0f;
    float centerY = 2.0f;
    float centerZ = 30.0f;

    float orbitRadius = 20.0f; // ���� ������
    float orbitSpeed = 0.5f;   // ���� �ӵ� (����/��)

    for (int i = 0; i < m_nStartObjects; ++i) {
        if (m_ppStartObjects[i]) {
            // �� ť�긶�� ������ �ٸ��� �ؼ� �л�
            float angle = orbitSpeed * fTimeElapsed + (XM_2PI * i / m_nStartObjects);
            float x = centerX + orbitRadius * cos(angle);
            float z = centerZ + orbitRadius * sin(angle);
            float y = centerY;


            // ť�� ��ü�� ȸ��
            m_ppStartObjects[i]->Rotate(0.0f, XM_PI * 0.2f * fTimeElapsed, 0.0f);
        }
    }

    // (���� �ִϸ��̼� �� ���� �ڵ� ����)
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
    // �̸� ť���� �߽� ��ǥ�� ������ ����
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
//	// StartScene���� ������Ʈ/���̴� ����
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

    // �ؽ�Ʈ ���� ����
    pDWriteFactory->CreateTextFormat(
        L"Segoe UI", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, 28.0f, L"ko-KR", &m_pTextFormat);

    // �귯�� ����
    m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pBrush);

    // �޴� �簢�� ���
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

        // �簢�� �׵θ� �׸���
        m_pRT->DrawRectangle(rect, m_pBrush, 2.0f);

        // �ؽ�Ʈ �߾� ���� ���
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
                // ���� ���� ���� ȣ��
            }
            else if (m_MenuItems[i] == L"Level-1") {
                // Level-1 ����
            }
            else if (m_MenuItems[i] == L"Level-2") {
                // Level-2 ����
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
//	// ���������ο��� ���� ��Ʈ�ñ״�ó�� ���
//	m_pd3dGraphicsRootSignature = rootSignatue;
//
//	CubeMeshDiffused *pCubeMesh = new CubeMeshDiffused(pd3dDevice, pd3dCommandList, 12.0f, 12.0f, 12.0f);
//
//	// 1������ ��ü�� ����Ű�� 1���� ���̴�
//	m_nShaders = 1;
//	// 1���� ���̴� �ּ� ���� �޸� �Ҵ� - m_pShaders�� m_nShaders��ŭ�� ��ü�� �ּ� �迭�� ����
//	m_pShaders = new ObjectsShader[m_nShaders];
//
//	// Shader ����
//	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
//	// ������ Shader�� ��ü ����
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
//	// �׷��� ��Ʈ �ñ׳��ĸ� ���������ο� ����
//	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
//
//	if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);
//
//	// ���� �����ϴ� ���̴�(���̴��� ���Ե� ��ü)���� ������
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



