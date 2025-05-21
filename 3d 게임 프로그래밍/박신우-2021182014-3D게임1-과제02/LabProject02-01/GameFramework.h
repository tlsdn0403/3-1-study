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

	IDXGIFactory4* m_pdxgiFactory; //DXGI 팩토리 인터페이스에 대한 포인터이다. 
	IDXGISwapChain3* m_pdxgiSwapChain; //스왑 체인 인터페이스에 대한 포인터이다. 주로 디스플레이를 제어하기 위하여 필요하다.
	ID3D12Device* m_pd3dDevice; //Direct3D 디바이스 인터페이스에 대한 포인터이다. 주로 리소스를 생성하기 위하여 필요하다.

	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0; //MSAA 다중 샘플링을 활성화하고 다중 샘플링 레벨을 설정한다

	static const UINT m_nSwapChainBuffers = 2;  //스왑 체인의 후면 버퍼의 개수이다.
	UINT m_nSwapChainBufferIndex;  //현재 스왑 체인의 후면 버퍼 인덱스이다.

	//RTV
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];  //렌더 타겟 버퍼
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;  //서술자 힙 인터페이스 포인터
	UINT m_nRtvDescriptorIncrementSize;  //렌더 타겟 서술자 원소의 크기

	//DSV
	ID3D12Resource* m_pd3dDepthStencilBuffer;//깊이-스텐실 버퍼
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap; //서술자 힙 인터페이스 포인터
	UINT m_nDsvDescriptorIncrementSize; //깊이-스텐실 서술자 원소의 크기이다

	// Command List
	ID3D12CommandQueue* m_pd3dCommandQueue; //명령 큐
	ID3D12CommandAllocator* m_pd3dCommandAllocator; //명령 할당자
	ID3D12GraphicsCommandList* m_pd3dCommandList; //명령 리스트 인터페이스 포인터이다

	ID3D12PipelineState* m_pd3dPipelineState; //그래픽스 파이프라인 상태 객체에 대한 인터페이스 포인터이다.


	ID3D12Fence* m_pd3dFence;//펜스 인터페이스 포인터
	UINT64 m_nFenceValues[m_nSwapChainBuffers];//펜스의 값
	HANDLE m_hFenceEvent; //이벤트 핸들이다


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

	void CreateSwapChain();//스왑 체인 생성
	void CreateRtvAndDsvDescriptorHeaps(); //서술자 생성
	void CreateDirect3DDevice(); // 디바이스 생성
	void CreateCommandQueueAndList(); // 명령 큐 / 할당자 / 리스트 힙 생성

	void CreateRenderTargetViews(); //랜더 타겟 뷰 생성
	void CreateDepthStencilView();  //깊이 스텐실 뷰
	

	void BuildFrameBuffer();
	void ClearFrameBuffer(DWORD dwColor);
	void PresentFrameBuffer();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput(); //사용자 입력을 받아드림
	void AnimateObjects();
	void FrameAdvance();

	void WaitForGpuComplete();	//CPU와 GPU를 동기화하는 함수이다.


	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void SetActive(bool bActive) { m_bActive = bActive; }


	void ChoiceGameMode();


	void MoveToNextFrame();

};

