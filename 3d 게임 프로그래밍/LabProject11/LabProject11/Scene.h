#pragma once

#include "Shader.h"
#include "Player.h"
#include <d2d1.h>
#include <dwrite.h>
#include <d2d1_1.h>
#include <wrl/client.h>


class CGameState {
public:
	static enum GameState { TITLE, MENU, GAME, GAME_1, WIN, LOSS };
	GameState GetCurrentState() const { return CurrentState; }
	static GameState CurrentState;
	static void ChangeGameState(GameState state);

public:

	CGameState() = default;

	CGameState(const GameState& CurrentState)
	{
	}
};








class Scene{
public:
	Scene();
	~Scene();

	// 마우스 입력처리
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	// 키보드 입력처리
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList , ID3D12RootSignature* rootSignatue);
	void ReleaseObjects();

	bool ProcessInput(UCHAR *pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, Camera *pCamera);

	void ReleaseUploadBuffers();
	
	GameObject* PickObjectPointedByCursor(int xClient, int yClient, Camera* pCamera);

	//그래픽 루트 시그너쳐를 생성한다.
	virtual ID3D12RootSignature *GetGraphicsRootSignature();
	void FireBulletFromPlayer(Player* pPlayer, ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, GameObject* pLockedObject = nullptr);
protected: 
	//배치(Batch) 처리를 하기 위하여 씬을 셰이더들의 리스트로 표현한다.
	ObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;

	ID3D12RootSignature *m_pd3dGraphicsRootSignature = NULL;

	CBulletObject* m_ppBullets[BULLETS] = { nullptr }; // BULLETS는 기존과 동일하게 사용
	int m_nBullets = BULLETS;

protected:
	GameObject** m_ppObjects = NULL;
	CFloorObject* m_pFloorObject = NULL;
	CBulletObject* pBulletObjects;
	int m_nObjects = 0;
};



class StartScene : public Scene {
public:
	void OnMouseClick(int x, int y);
	bool isExploding = false;
	float angle = 0.0f;

	// 오버라이드
	 void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList , ID3D12RootSignature* rootSignatue) ;
	 void Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera) ;
	 void ReleaseUploadBuffers();
	 void AnimateObjects(float fTimeElapsed);
	// 소멸자 추가
	virtual ~StartScene();
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
	void ReleaseObjects();


	float explosionTime = 0.0f;
private:
	ObjectsShader* m_pStartSceneShader = nullptr;

protected:
	GameObject** m_ppStartObjects = NULL;
	int m_nStartObjects = 0;
};

class MenuScene : public Scene {
public:

	void OnMouseClick(int x, int y);
	// 오버라이드
	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* rootSignatue);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera);
	void ReleaseUploadBuffers();
	// 소멸자 추가
	virtual ~MenuScene();
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
	void ReleaseObjects();


	float explosionTime = 0.0f;
	ObjectsShader* m_pMenuSceneShader = nullptr;

protected:
	GameObject** m_ppMenuObjects = NULL;
	int m_nMenuObjects = 0;

};
