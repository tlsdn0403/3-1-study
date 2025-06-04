#pragma once
#include "Timer.h"
#include "Player.h"
#include "Scene.h"
#include <memory>
#include <wrl.h>
#include <d3d11on12.h>
#include <d2d1_3.h>
#include <dwrite.h>

class GameFramework{
private:

	//���� �����ӿ�ũ���� ����� Ÿ�̸�
	GameTimer m_GameTimer;
	//������ ����Ʈ�� �� �������� ĸ�ǿ� ����ϱ� ���� ���ڿ�
	_TCHAR m_pszFrameRate[50]; 

	// Scene
	Scene* m_pScene;
	StartScene *m_pStartScene;
	MenuScene* m_pMenuScene;
	// Camera
	Camera *m_pCamera = NULL;
	// Player
	std::unique_ptr<Player> m_pPlayer = nullptr;

	// ���������� ���콺 ��ư�� Ŭ���� ���� ���콺 Ŀ���� ��ġ
	POINT m_ptOldCursorPos;    

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	int m_nWndClientWidth;
	int m_nWndClientHeight;

	


	IDXGIFactory4* m_pdxgiFactory;
	// ���÷��� ��� ����
	IDXGISwapChain3* m_pdxgiSwapChain;
	// ���ҽ� ������ ����
	ID3D12Device* m_pd3dDevice;

	// ���� ���ø��� Ȱ��ȭ
	bool m_bMsaa4xEnable = false;
	// ���� ���ø� ������ ����
	UINT m_nMsaa4xQualityLevels = 0;

	static const UINT m_nSwapChainBuffers = 2; //����ü�� ����� ��
	//����ü�� ����� ���� �ε���
	UINT m_nSwapChainBufferIndex; 

	// ���� Ÿ�� ����
	ID3D12Resource *m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	// ���� Ÿ�� ������ �� �ּ�
	ID3D12DescriptorHeap *m_pd3dRtvDescriptorHeap;
	// ���� Ÿ�� ������ ������ ũ��
	UINT m_nRtvDescriptorIncrementSize;

	// ����-���ٽ� ����
	ID3D12Resource *m_pd3dDepthStencilBuffer;
	// �������ٽ� ������ �� �ּ�
	ID3D12DescriptorHeap *m_pd3dDsvDescriptorHeap;
	// �������ٽ� ������ ������ ũ��
	UINT m_nDsvDescriptorIncrementSize;





	//��� ť, ��� �Ҵ���, ��� ����Ʈ �������̽�
	ID3D12CommandQueue *m_pd3dCommandQueue;
	ID3D12CommandAllocator *m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList *m_pd3dCommandList;

	//�׷��� ���������� ����
	ID3D12PipelineState *m_pd3dPipelineState;

	//�潺 �������̽�
	ID3D12Fence *m_pd3dFence;
	UINT64 m_nFenceValues[m_nSwapChainBuffers];
	HANDLE m_hFenceEvent;

	//if~endif: if�� ������ ���̸� endif���� �������� ����ȴ�.
#if defined(_DEBUG) 
	ID3D12Debug *m_pd3dDebugController;
#endif

	CGameState* pGameState = new CGameState();

	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;

public:
	GameFramework();
	~GameFramework();

	// �� �����찡 �����Ǹ� ȣ��ȴ�.
	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);

	void OnDestory();

	// ����ü�� ����
	void CreateSwapChain();
	// ����̽� ����
	void CreateDirect3DDevice();
	// ������ �� ����
	void CreateRtvAndDsvDescriptorHeaps();
	// ��� ť, �Ҵ���, ����Ʈ ����
	void CreateCommandQueueAndList();
	// ���� Ÿ�� �� ����
	void CreateRenderTargetViews();
	// ���� - ���ٽ� �� ����
	void CreateDepthStencilViews();

	// �������� �޽��� ���� ��ü�� ����
	void BuildObjects();
	// �������� �޽��� ���� ��ü�� �Ҹ�
	void ReleaseObjects();

	// ��������ũ�� �ٽ�(����� �Է�, �ִϸ��̼�, ������)�� �����ϴ� �Լ�
	void ProcessInput();
	void AnimateObject();
	void FrameAdvance();

	// CPU�� GPU�� ����ȭ�ϴ� �Լ��̴�. 
	void WaitForGpuComplete(); 

	//[�����ϱ�5 fullscreenmode]
	void ChangeSwapChainState();
	
	void MoveToNextFrame();

	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�.
	virtual ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);

	

	// �������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ�
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void ChoiceGameMode();
};
