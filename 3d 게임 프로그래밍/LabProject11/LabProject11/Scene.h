#pragma once

#include "Shader.h"
#include "Player.h"
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

	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput(UCHAR *pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, Camera *pCamera);

	void ReleaseUploadBuffers();

	//그래픽 루트 시그너쳐를 생성한다.
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	virtual ID3D12RootSignature *GetGraphicsRootSignature();

protected: 
	//배치(Batch) 처리를 하기 위하여 씬을 셰이더들의 리스트로 표현한다.
	ObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;

	ID3D12RootSignature *m_pd3dGraphicsRootSignature = NULL;
};
class StartScene : public Scene {
public:
	void OnMouseClick(int x, int y);
	bool isExploding = false;
	float angle = 0.0f;

	// 오버라이드
	 void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList) ;
	 void Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera) ;

	// 소멸자 추가
	virtual ~StartScene();

private:
	StartSceneObjectsShader* m_pStartSceneShader = nullptr;
};
