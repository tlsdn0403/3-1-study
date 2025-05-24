#pragma once

#include "Player.h"
#include "Scene.h"
#include "Timer.h"
#include"CGameScene_1.h"

class CGameFramework
{
public:
	CGameFramework() { }
	~CGameFramework() { }

private:
	HINSTANCE					m_hInstance = NULL;
	HWND						m_hWnd = NULL;

	bool						m_bActive = true;

	RECT						m_rcClient;

    HDC							m_hDCFrameBuffer = NULL;
    HBITMAP						m_hBitmapFrameBuffer = NULL;
    HBITMAP						m_hBitmapSelect = NULL;

	CPlayer*					m_pPlayer = NULL;
	
	CGameState* pGameState = new CGameState();;
	StartScene*					pStartScene = NULL;
	MenuScene* pMenuScene = NULL;
	WinScene* pWinScene = nullptr;
	LossScene* pLossScene =nullptr;
	CGameScene*						m_pScene = NULL;
	CGameScene_1*					m_pScene_1 = nullptr;


	CGameObject*				m_pLockedObject = NULL;

	CGameTimer					m_GameTimer;

	POINT						m_ptOldCursorPos;

	_TCHAR						m_pszFrameRate[50];


public:
	void OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void BuildFrameBuffer();
	void ClearFrameBuffer(DWORD dwColor);
	void PresentFrameBuffer();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput(); //����� �Է��� �޾Ƶ帲
	void AnimateObjects();
	void FrameAdvance();

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void SetActive(bool bActive) { m_bActive = bActive; }


	void ChoiceGameMode();

};

class GameFramework {
private:

	//���� �����ӿ�ũ���� ����� Ÿ�̸�
	CGameTimer m_GameTimer;
	//������ ����Ʈ�� �� �������� ĸ�ǿ� ����ϱ� ���� ���ڿ�
	_TCHAR m_pszFrameRate[50];

	// Scene
	CGameState* pGameState = new CGameState();;
	StartScene* pStartScene = NULL;
	MenuScene* pMenuScene = NULL;
	WinScene* pWinScene = nullptr;
	LossScene* pLossScene = nullptr;
	CGameScene* m_pScene = NULL;
	CGameScene_1* m_pScene_1 = nullptr;
	// Camera
	CCamera* m_pCamera = NULL;
	// Player
	CPlayer* m_pPlayer = NULL;

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
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	// ���� Ÿ�� ������ �� �ּ�
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	// ���� Ÿ�� ������ ������ ũ��
	UINT m_nRtvDescriptorIncrementSize;

	// ����-���ٽ� ����
	ID3D12Resource* m_pd3dDepthStencilBuffer;
	// �������ٽ� ������ �� �ּ�
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	// �������ٽ� ������ ������ ũ��
	UINT m_nDsvDescriptorIncrementSize;

	//��� ť, ��� �Ҵ���, ��� ����Ʈ �������̽�
	ID3D12CommandQueue* m_pd3dCommandQueue;
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList* m_pd3dCommandList;

	//�׷��� ���������� ����
	ID3D12PipelineState* m_pd3dPipelineState;

	//�潺 �������̽�
	ID3D12Fence* m_pd3dFence;
	UINT64 m_nFenceValues[m_nSwapChainBuffers];
	HANDLE m_hFenceEvent;

	//if~endif: if�� ������ ���̸� endif���� �������� ����ȴ�.
#if defined(_DEBUG) 
	ID3D12Debug* m_pd3dDebugController;
#endif

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

	// �������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ�
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);



	void ChoiceGameMode();
};