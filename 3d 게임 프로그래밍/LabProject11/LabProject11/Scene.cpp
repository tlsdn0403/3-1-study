#include "stdafx.h"
#include "Scene.h"
#include "TextMesh.h" // ��ܿ� �߰�
#include <d3d9.h>
#include <tchar.h>

CGameState::GameState CGameState::CurrentState = CGameState::GAME; // ���� ��� ��
void CGameState::ChangeGameState(GameState state)
{
	CurrentState = state;
}




void StartScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignature) {
    m_pd3dGraphicsRootSignature = rootSignature;
    m_nShaders = 1;
    m_pStartSceneShader = new ObjectsShader[m_nShaders];
    m_pStartSceneShader[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);

    // 7x7 �ȼ� ��
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

    int map��[letterH][letterW] = {
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

    // �������� �̵��� ������ ��
    float leftOffset = -14.0f;

    // ��ü ���� ���
    int objCnt = 0;
    for (int y = 0; y < letterH; ++y)
        for (int x = 0; x < letterW; ++x)
            if (map3[y][x]) ++objCnt;
    for (int y = 0; y < letterH; ++y)
        for (int x = 0; x < letterW; ++x)
            if (mapD[y][x]) ++objCnt;
    for (int y = 0; y < letterH; ++y)
        for (int x = 0; x < letterW; ++x)
            if (map��[y][x]) ++objCnt;

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
    // "��"
    float letterSpacing2 = letterSpacing + letterW * spacing + 3.0f;
    for (int y = 0; y < letterH; ++y) {
        for (int x = 0; x < letterW; ++x) {
            if (map��[y][x]) {
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
    // ��ü ť�� ȸ��
    for (int i = 0; i < m_nStartObjects; ++i) {
        if (m_ppStartObjects[i]) {
            m_ppStartObjects[i]->Rotate(0.0f, XM_PI * 0.2f * fTimeElapsed, 0.0f);
        }
    }

    // �̸� ť�� ���� �ִϸ��̼�
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
        // ���� �� ���� �ð� �� �޴� ȭ������ ��ȯ
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



