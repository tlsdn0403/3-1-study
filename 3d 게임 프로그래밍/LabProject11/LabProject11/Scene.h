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

	// ���콺 �Է�ó��
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	// Ű���� �Է�ó��
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput(UCHAR *pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, Camera *pCamera);

	void ReleaseUploadBuffers();

	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�.
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	virtual ID3D12RootSignature *GetGraphicsRootSignature();

protected: 
	//��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�.
	ObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;

	ID3D12RootSignature *m_pd3dGraphicsRootSignature = NULL;
};
class StartScene : public Scene {
public:
	void OnMouseClick(int x, int y);
	bool isExploding = false;
	float angle = 0.0f;

	// �������̵�
	 void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList) ;
	 void Render(ID3D12GraphicsCommandList* pd3dCommandList, Camera* pCamera) ;

	// �Ҹ��� �߰�
	virtual ~StartScene();

private:
	StartSceneObjectsShader* m_pStartSceneShader = nullptr;
};
