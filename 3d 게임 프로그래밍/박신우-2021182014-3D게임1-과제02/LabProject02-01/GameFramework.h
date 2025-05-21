#pragma once

#include "Player.h"
#include "Scene.h"
#include "Timer.h"
#include"CGameScene_1.h"

class CGameFramework
{
public:
	CGameFramework();
	~CGameFramework();

private:
	HINSTANCE					m_hInstance = NULL;
	HWND						m_hWnd = NULL;

	
	int m_nWndClientWidth;
	int m_nWndClientHeight;

	IDXGIFactory4* m_pdxgiFactory; //DXGI ���丮 �������̽��� ���� �������̴�. 
	IDXGISwapChain3* m_pdxgiSwapChain; //���� ü�� �������̽��� ���� �������̴�. �ַ� ���÷��̸� �����ϱ� ���Ͽ� �ʿ��ϴ�.
	ID3D12Device* m_pd3dDevice; //Direct3D ����̽� �������̽��� ���� �������̴�. �ַ� ���ҽ��� �����ϱ� ���Ͽ� �ʿ��ϴ�.

	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0; //MSAA ���� ���ø��� Ȱ��ȭ�ϰ� ���� ���ø� ������ �����Ѵ�

	static const UINT m_nSwapChainBuffers = 2;  //���� ü���� �ĸ� ������ �����̴�.
	UINT m_nSwapChainBufferIndex;  //���� ���� ü���� �ĸ� ���� �ε����̴�.

	//RTV
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];  //���� Ÿ�� ����
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;  //������ �� �������̽� ������
	UINT m_nRtvDescriptorIncrementSize;  //���� Ÿ�� ������ ������ ũ��

	//DSV
	ID3D12Resource* m_pd3dDepthStencilBuffer;//����-���ٽ� ����
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap; //������ �� �������̽� ������
	UINT m_nDsvDescriptorIncrementSize; //����-���ٽ� ������ ������ ũ���̴�

	// Command List
	ID3D12CommandQueue* m_pd3dCommandQueue; //��� ť
	ID3D12CommandAllocator* m_pd3dCommandAllocator; //��� �Ҵ���
	ID3D12GraphicsCommandList* m_pd3dCommandList; //��� ����Ʈ �������̽� �������̴�

	ID3D12PipelineState* m_pd3dPipelineState; //�׷��Ƚ� ���������� ���� ��ü�� ���� �������̽� �������̴�.


	ID3D12Fence* m_pd3dFence;//�潺 �������̽� ������
	UINT64 m_nFenceValues[m_nSwapChainBuffers];//�潺�� ��
	HANDLE m_hFenceEvent; //�̺�Ʈ �ڵ��̴�


	CCamera* m_pCamera = NULL;


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

	CScene* m_pScene = NULL;
	CGameScene_2*						m_pScene_2 = NULL;
	CGameScene_1*					m_pScene_1 = nullptr;


	CGameObject_1*				m_pLockedObject = NULL;

	CGameTimer					m_GameTimer;

	POINT						m_ptOldCursorPos;

	_TCHAR						m_pszFrameRate[50];


public:


	void OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void CreateSwapChain();//���� ü�� ����
	void CreateRtvAndDsvDescriptorHeaps(); //������ ����
	void CreateDirect3DDevice(); // ����̽� ����
	void CreateCommandQueueAndList(); // ��� ť / �Ҵ��� / ����Ʈ �� ����

	void CreateRenderTargetViews(); //���� Ÿ�� �� ����
	void CreateDepthStencilView();  //���� ���ٽ� ��
	

	void BuildFrameBuffer();
	void ClearFrameBuffer(DWORD dwColor);
	void PresentFrameBuffer();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput(); //����� �Է��� �޾Ƶ帲
	void AnimateObjects();
	void FrameAdvance();

	void WaitForGpuComplete();	//CPU�� GPU�� ����ȭ�ϴ� �Լ��̴�.


	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void SetActive(bool bActive) { m_bActive = bActive; }


	void ChoiceGameMode();


	void MoveToNextFrame();

};

